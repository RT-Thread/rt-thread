#!/usr/bin/env python3
#
# Copyright (c) 2026, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#

"""Suggest potentially related GitHub issues using conservative local scoring."""

import json
import os
import re
import sys
import time
import unicodedata
from dataclasses import dataclass
from urllib.error import HTTPError, URLError
from urllib.parse import quote, urlencode
from urllib.request import Request, urlopen

import issue_labeler


API_VERSION = "2022-11-28"
COMMENT_MARKER = "<!-- rt-thread-similar-issues -->"
CLAIM_HINT_MARKER = "<!-- rt-thread-issue-claim-hint -->"
MAX_CANDIDATES = 3
SEARCH_RESULT_LIMIT = 30
MAX_BACKFILL_ISSUES = 50

FORM_SECTION = re.compile(r"^###\s+(.+?)\s*$", re.MULTILINE)
TITLE_PREFIX = re.compile(r"^\s*\[(?:bug|feature)\]\s*", re.IGNORECASE)
CJK_RUN = re.compile(r"[\u3400-\u9fff]+")
LATIN_TOKEN = re.compile(r"[a-z][a-z0-9_.-]{2,}")

IGNORED_SECTIONS = {
    "rt-thread version",
    "affected area",
    "hardware/bsp vendor",
    "architecture",
    "board and hardware details",
    "hardware type/architectures",
    "develop toolchain",
    "other additional context",
}

GENERIC_TOKENS = {
    "about",
    "after",
    "before",
    "board",
    "build",
    "component",
    "could",
    "error",
    "feature",
    "issue",
    "problem",
    "request",
    "rt-thread",
    "should",
    "thread",
    "using",
    "with",
}

CLASSIFICATION_LABELS = {
    "kernel",
    "rt-smart",
    "libcpu",
    "doc",
    "tools",
    "testcase",
    "action",
    "bsp",
    "component",
}


@dataclass(frozen=True)
class EventContext:
    repository: str
    issue: dict


class GitHubAPIError(RuntimeError):
    def __init__(self, status, message):
        super().__init__(message)
        self.status = status

    def __str__(self):
        return "GitHub API request failed with status {}: {}".format(
            self.status, super().__str__()
        )


class GitHubClient:
    def __init__(self, token, api_url="https://api.github.com"):
        if not token:
            raise ValueError("GITHUB_TOKEN is required")
        self.token = token
        self.api_url = api_url.rstrip("/")

    def request(self, method, path, payload=None, expected=(200,)):
        headers = {
            "Accept": "application/vnd.github+json",
            "Authorization": "Bearer {}".format(self.token),
            "User-Agent": "rt-thread-similar-issues",
            "X-GitHub-Api-Version": API_VERSION,
        }
        body = None
        if payload is not None:
            body = json.dumps(payload).encode("utf-8")
            headers["Content-Type"] = "application/json"
        request = Request(
            self.api_url + path, data=body, headers=headers, method=method
        )
        try:
            with urlopen(request, timeout=30) as response:
                status = response.getcode()
                response_body = response.read()
        except HTTPError as error:
            try:
                response_body = json.loads(error.read().decode("utf-8"))
                message = response_body.get("message", error.reason)
            except (ValueError, UnicodeDecodeError):
                message = error.reason
            raise GitHubAPIError(error.code, str(message)) from error
        except URLError as error:
            raise GitHubAPIError("network", str(error.reason)) from error

        if status not in expected:
            raise GitHubAPIError(status, "unexpected response status")
        return json.loads(response_body.decode("utf-8")) if response_body else None

    @staticmethod
    def repository_path(repository):
        owner, name = repository.split("/", 1)
        return "/repos/{}/{}".format(quote(owner, safe=""), quote(name, safe=""))

    def search_issues(self, repository, query):
        parameters = urlencode(
            {
                "q": "repo:{} is:issue {}".format(repository, query),
                "per_page": SEARCH_RESULT_LIMIT,
            }
        )
        return self.request("GET", "/search/issues?{}".format(parameters))

    def list_comments(self, repository, issue_number):
        comments = []
        repository_path = self.repository_path(repository)
        page = 1
        while True:
            parameters = urlencode({"per_page": 100, "page": page})
            batch = self.request(
                "GET",
                "{}/issues/{}/comments?{}".format(
                    repository_path, issue_number, parameters
                ),
            )
            comments.extend(batch)
            if len(batch) < 100:
                break
            page += 1
        return comments

    def create_comment(self, repository, issue_number, body):
        return self.request(
            "POST",
            "{}/issues/{}/comments".format(
                self.repository_path(repository), issue_number
            ),
            {"body": body},
            expected=(201,),
        )

    def list_open_issues(self, repository, limit):
        issues = []
        repository_path = self.repository_path(repository)
        for page in range(1, 11):
            parameters = urlencode(
                {
                    "state": "open",
                    "sort": "updated",
                    "direction": "desc",
                    "per_page": 100,
                    "page": page,
                }
            )
            batch = self.request(
                "GET", "{}/issues?{}".format(repository_path, parameters)
            )
            issues.extend(
                issue
                for issue in batch
                if "pull_request" not in issue and not (issue.get("assignees") or [])
            )
            if len(issues) >= limit or len(batch) < 100:
                break
        return sorted(issues, key=lambda issue: issue.get("number", 0), reverse=True)[
            :limit
        ]


def normalize(value):
    text = unicodedata.normalize("NFKC", str(value or "")).casefold()
    return " ".join(text.split())


def strip_title_prefix(title):
    return TITLE_PREFIX.sub("", str(title or ""), count=1).strip()


def parse_form_sections(body):
    text = str(body or "")
    matches = list(FORM_SECTION.finditer(text))
    sections = []
    for index, match in enumerate(matches):
        start = match.end()
        end = matches[index + 1].start() if index + 1 < len(matches) else len(text)
        sections.append((normalize(match.group(1)), text[start:end].strip()))
    return sections


def strip_markdown(value):
    text = re.sub(r"```[\s\S]*?```", " ", str(value or ""))
    text = re.sub(r"!\[[^]]*\]\([^)]*\)", " ", text)
    text = re.sub(r"\[([^]]+)\]\([^)]*\)", r"\1", text)
    text = re.sub(r"<[^>]+>", " ", text)
    text = re.sub(r"[`*~>#]", " ", text)
    return " ".join(text.split())


def relevant_body(body):
    sections = parse_form_sections(body)
    if not sections:
        return strip_markdown(body)
    selected = [
        value
        for heading, value in sections
        if heading not in IGNORED_SECTIONS and value != "_No response_"
    ]
    return strip_markdown("\n".join(selected))


def semantic_tokens(value):
    normalized = normalize(value)
    tokens = {
        token
        for token in LATIN_TOKEN.findall(normalized)
        if token not in GENERIC_TOKENS and not token.isdigit()
    }
    for run in CJK_RUN.findall(normalized):
        if len(run) == 1:
            continue
        if len(run) <= 4:
            tokens.add(run)
        for index in range(len(run) - 1):
            tokens.add(run[index : index + 2])
    return tokens


def technical_tokens(value):
    return {
        token
        for token in semantic_tokens(value)
        if re.search(r"[0-9_.-]", token) and not CJK_RUN.fullmatch(token)
    }


def character_ngrams(value, size=3):
    compact = re.sub(r"[^a-z0-9\u3400-\u9fff]+", "", normalize(value))
    if not compact:
        return set()
    gram_size = min(size, len(compact))
    return {
        compact[index : index + gram_size]
        for index in range(len(compact) - gram_size + 1)
    }


def dice(left, right):
    if not left or not right:
        return 0.0
    return 2.0 * len(left.intersection(right)) / (len(left) + len(right))


def jaccard(left, right):
    if not left or not right:
        return 0.0
    return len(left.intersection(right)) / len(left.union(right))


def label_names(issue):
    result = set()
    for label in issue.get("labels") or []:
        name = label.get("name") if isinstance(label, dict) else label
        if isinstance(name, str):
            result.add(name.casefold())
    return result


def classification_labels(issue):
    labels = label_names(issue)
    labels.difference_update(
        label.casefold()
        for label in issue_labeler.obsolete_labels(
            issue.get("body", ""), issue
        )
    )
    labels.update(
        label.casefold()
        for label in issue_labeler.desired_labels(issue.get("body", ""))
    )
    return {
        label
        for label in labels
        if label in CLASSIFICATION_LABELS
        or label.startswith("bsp:")
        or label.startswith("arch:")
        or label.startswith("component:")
    }


def score_candidate(issue, candidate):
    issue_labels = classification_labels(issue)
    candidate_labels = classification_labels(candidate)
    issue_bsp = {label for label in issue_labels if label.startswith("bsp:")}
    candidate_bsp = {
        label for label in candidate_labels if label.startswith("bsp:")
    }
    if issue_bsp and candidate_bsp and issue_bsp.isdisjoint(candidate_bsp):
        return {"accepted": False, "score": 0.0, "reason": "bsp-mismatch"}

    issue_title = strip_title_prefix(issue.get("title", ""))
    candidate_title = strip_title_prefix(candidate.get("title", ""))
    issue_body = relevant_body(issue.get("body", ""))[:1600]
    candidate_body = relevant_body(candidate.get("body", ""))[:1600]
    title_similarity = dice(
        character_ngrams(issue_title), character_ngrams(candidate_title)
    )
    body_similarity = dice(
        character_ngrams(issue_body), character_ngrams(candidate_body)
    )
    token_similarity = jaccard(
        semantic_tokens(issue_title), semantic_tokens(candidate_title)
    )
    issue_technical = technical_tokens("{}\n{}".format(issue_title, issue_body))
    candidate_technical = technical_tokens(
        "{}\n{}".format(candidate_title, candidate_body)
    )
    technical_coverage = (
        len(issue_technical.intersection(candidate_technical)) / len(issue_technical)
        if issue_technical
        else 0.0
    )
    label_similarity = jaccard(issue_labels, candidate_labels)

    score = (
        title_similarity * 0.50
        + body_similarity * 0.12
        + token_similarity * 0.20
        + technical_coverage * 0.13
        + label_similarity * 0.05
    )
    accepted = score >= 0.38 and (
        title_similarity >= 0.24
        or token_similarity >= 0.35
        or technical_coverage >= 0.5
    )
    return {
        "accepted": accepted,
        "score": score,
        "signals": {
            "title": title_similarity,
            "body": body_similarity,
            "tokens": token_similarity,
            "technical": technical_coverage,
            "labels": label_similarity,
        },
    }


def rank_candidates(issue, candidates):
    ranked = []
    issue_number = int(issue.get("number", 0) or 0)
    for candidate in candidates:
        if "pull_request" in candidate:
            continue
        if int(candidate.get("number", 0) or 0) == issue_number:
            continue
        result = score_candidate(issue, candidate)
        if result["accepted"]:
            ranked.append({"candidate": candidate, **result})
    ranked.sort(key=lambda item: item["score"], reverse=True)
    return ranked[:MAX_CANDIDATES]


def search_terms(issue):
    title = strip_title_prefix(issue.get("title", ""))
    technical = sorted(technical_tokens(title), key=lambda token: (-len(token), token))
    ordinary = sorted(
        semantic_tokens(title).difference(technical),
        key=lambda token: (-len(token), token),
    )
    # GitHub's issue search combines terms narrowly. Technical identifiers are
    # strong enough to retrieve broadly on their own; local scoring filters the
    # resulting candidates before anything is shown to users.
    selected = technical[:3] if technical else ordinary[:3]
    query = " ".join(selected)
    if not query:
        query = re.sub(r"[^a-zA-Z0-9\u3400-\u9fff_.-]+", " ", title)
    return " ".join(query.split())[:256]


def is_workflow_comment(comment):
    if not isinstance(comment, dict):
        return False
    user = comment.get("user") or {}
    return str(user.get("login", "")).casefold() == "github-actions[bot]"


def has_marker(comments, marker=COMMENT_MARKER):
    return any(
        is_workflow_comment(comment)
        and marker in str(comment.get("body", ""))
        for comment in comments
    )


def format_comment(ranked):
    references = "\n".join(
        "- #{}".format(item["candidate"]["number"]) for item in ranked
    )
    return (
        "{}\n"
        "以下 Issue 可能与当前问题相关；这是自动检索结果，尚未确认重复：\n\n"
        "The following issues may be related. These automated suggestions are "
        "not confirmed duplicates:\n\n{}"
    ).format(COMMENT_MARKER, references)


def format_claim_hint_comment():
    return (
        "{}\n"
        "如需认领并处理此 Issue，请评论 `/claim`。\n\n"
        "To claim and work on this issue, comment `/claim`."
    ).format(CLAIM_HINT_MARKER)


def ensure_claim_hint(client, repository, issue_number, comments, dry_run=False):
    if has_marker(comments, CLAIM_HINT_MARKER):
        print("Issue #{} already has a claim hint".format(issue_number))
        return False
    comment = format_claim_hint_comment()
    if dry_run:
        print("Dry run claim hint for #{}:\n{}".format(issue_number, comment))
    else:
        client.create_comment(repository, issue_number, comment)
    return True


def is_rate_limit(error):
    return error.status in (429,) or (
        error.status == 403 and "rate limit" in str(error).casefold()
    )


def suggest_for_issue(
    client,
    repository,
    issue,
    dry_run=False,
    best_effort_rate_limit=True,
    add_claim_hint=True,
):
    issue_number = int(issue.get("number", 0) or 0)
    if not issue_number or "pull_request" in issue:
        return []
    comments = client.list_comments(repository, issue_number)
    if add_claim_hint:
        ensure_claim_hint(
            client, repository, issue_number, comments, dry_run=dry_run
        )
    if has_marker(comments):
        print("Issue #{} already has a similar-issue comment".format(issue_number))
        return []

    query = search_terms(issue)
    if len(query) < 2:
        print("Issue #{} has too little searchable text".format(issue_number))
        return []
    try:
        response = client.search_issues(repository, query)
    except GitHubAPIError as error:
        if best_effort_rate_limit and is_rate_limit(error):
            print("Skipping #{} because search is rate limited".format(issue_number))
            return []
        raise

    ranked = rank_candidates(issue, response.get("items") or [])
    if not ranked:
        print("No sufficiently similar issues found for #{}".format(issue_number))
        return []

    comment = format_comment(ranked)
    if dry_run:
        print("Dry run for #{}:\n{}".format(issue_number, comment))
    else:
        if has_marker(client.list_comments(repository, issue_number)):
            print("Issue #{} received a similar-issue comment".format(issue_number))
            return []
        client.create_comment(repository, issue_number, comment)
    return ranked


def process_backfill(client, repository, max_issues, delay_seconds, dry_run):
    issues = client.list_open_issues(repository, max_issues)
    summary = {"processed": 0, "suggested": 0, "candidates": 0, "failures": []}
    for index, issue in enumerate(issues):
        number = issue.get("number")
        print("[{}/{}] Processing #{}".format(index + 1, len(issues), number))
        try:
            ranked = suggest_for_issue(
                client,
                repository,
                issue,
                dry_run=dry_run,
                best_effort_rate_limit=False,
                add_claim_hint=False,
            )
            if ranked:
                summary["suggested"] += 1
                summary["candidates"] += len(ranked)
        except GitHubAPIError as error:
            summary["failures"].append({"number": number, "error": str(error)})
        summary["processed"] += 1
        if index + 1 < len(issues):
            time.sleep(delay_seconds)
    return summary


def event_context(event):
    if not isinstance(event, dict) or event.get("action") != "opened":
        return None
    issue = event.get("issue") or {}
    if "pull_request" in issue:
        return None
    repository = (event.get("repository") or {}).get("full_name")
    if not repository or repository.count("/") != 1:
        return None
    return EventContext(repository, issue)


def boolean_env(name, default=False):
    value = os.getenv(name)
    if value is None:
        return default
    return normalize(value) in ("1", "true", "yes", "on")


def integer_env(name, default, minimum, maximum):
    try:
        value = int(os.getenv(name, str(default)))
    except ValueError as error:
        raise ValueError("{} must be an integer".format(name)) from error
    if value < minimum or value > maximum:
        raise ValueError("{} must be between {} and {}".format(name, minimum, maximum))
    return value


def load_event(path):
    with open(path, "r", encoding="utf-8") as event_file:
        return json.load(event_file)


def main():
    try:
        client = GitHubClient(
            os.getenv("GITHUB_TOKEN", ""),
            os.getenv("GITHUB_API_URL", "https://api.github.com"),
        )
        if boolean_env("BACKFILL"):
            repository = os.getenv("GITHUB_REPOSITORY", "")
            if repository.count("/") != 1:
                raise ValueError("GITHUB_REPOSITORY is required")
            summary = process_backfill(
                client,
                repository,
                max_issues=integer_env(
                    "MAX_ISSUES", 20, minimum=1, maximum=MAX_BACKFILL_ISSUES
                ),
                delay_seconds=integer_env(
                    "SEARCH_DELAY_SECONDS", 3, minimum=2, maximum=30
                ),
                dry_run=boolean_env("DRY_RUN", default=True),
            )
            print(json.dumps(summary, ensure_ascii=True, sort_keys=True))
            return 1 if summary["failures"] else 0

        event_path = os.getenv("GITHUB_EVENT_PATH")
        if not event_path:
            raise ValueError("GITHUB_EVENT_PATH is required")
        context = event_context(load_event(event_path))
        if context is None:
            print("Ignoring event: no supported issue")
            return 0
        suggest_for_issue(
            client,
            context.repository,
            context.issue,
            dry_run=boolean_env("DRY_RUN"),
        )
        return 0
    except (GitHubAPIError, OSError, ValueError) as error:
        print(str(error), file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
