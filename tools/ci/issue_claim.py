#!/usr/bin/env python3
#
# Copyright (c) 2026, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#

"""Handle /claim and /unclaim commands on selected GitHub issues."""

import json
import os
import re
import sys
import time
from dataclasses import dataclass
from email.utils import parsedate_to_datetime
from urllib.error import HTTPError, URLError
from urllib.parse import quote, urlencode
from urllib.request import Request, urlopen


COMMAND_PATTERN = re.compile(r"\A/(claim|unclaim)\Z", re.IGNORECASE)
PROGRESS_LABEL = "in progress"
MAINTAINER_ROLES = frozenset(("admin", "maintain"))
MARKER_TEMPLATE = "<!-- rt-thread-issue-claim:{comment_id} -->"
STATE_MARKER = re.compile(
    r"<!-- rt-thread-issue-claim:state:(claimed|unclaimed):([A-Za-z0-9-]+) -->"
)


@dataclass(frozen=True)
class EventContext:
    command: str
    repository: str
    issue_number: int
    actor: str
    comment_id: int

    @property
    def marker(self):
        return MARKER_TEMPLATE.format(comment_id=self.comment_id)


@dataclass(frozen=True)
class Decision:
    allowed: bool
    reason: str
    assignees: tuple = ()


class GitHubAPIError(RuntimeError):
    def __init__(self, status, message, rate_limit_reset=None):
        super().__init__(message)
        self.status = status
        self.rate_limit_reset = rate_limit_reset

    def __str__(self):
        detail = "GitHub API request failed"
        if self.status is not None:
            detail += " with status {}".format(self.status)
        if self.rate_limit_reset:
            detail += " (rate limit resets at {})".format(self.rate_limit_reset)
        return "{}: {}".format(detail, super().__str__())


class GitHubClient:
    def __init__(
        self, token, api_url="https://api.github.com", retries=3, sleep=time.sleep
    ):
        if not token:
            raise ValueError("GITHUB_TOKEN is required")
        self.token = token
        self.api_url = api_url.rstrip("/")
        self.retries = retries
        self.sleep = sleep

    def request(self, method, path, payload=None, expected=(200,), retry=True):
        url = self.api_url + path
        body = None
        headers = {
            "Accept": "application/vnd.github+json",
            "Authorization": "Bearer {}".format(self.token),
            "User-Agent": "rt-thread-issue-claim",
            "X-GitHub-Api-Version": "2022-11-28",
        }
        if payload is not None:
            body = json.dumps(payload).encode("utf-8")
            headers["Content-Type"] = "application/json"

        for attempt in range(self.retries + 1):
            request = Request(url, data=body, headers=headers, method=method)
            try:
                with urlopen(request, timeout=30) as response:
                    status = response.getcode()
                    response_body = response.read()
                    if status not in expected:
                        raise GitHubAPIError(status, "unexpected response status")
                    if not response_body:
                        return None
                    return json.loads(response_body.decode("utf-8"))
            except HTTPError as error:
                message = self._error_message(error)
                if retry and attempt < self.retries and self._is_retryable(error):
                    self.sleep(self._retry_delay(error.headers, attempt))
                    continue
                raise GitHubAPIError(
                    error.code,
                    message,
                    error.headers.get("X-RateLimit-Reset"),
                ) from error
            except URLError as error:
                if retry and attempt < self.retries:
                    self.sleep(min(2 ** attempt, 10))
                    continue
                raise GitHubAPIError(None, str(error.reason)) from error

        raise GitHubAPIError(None, "retry limit exceeded")

    @staticmethod
    def _error_message(error):
        try:
            response = json.loads(error.read().decode("utf-8"))
        except (ValueError, UnicodeDecodeError):
            return str(error.reason)
        return str(response.get("message", error.reason))

    @staticmethod
    def _is_retryable(error):
        return (
            error.code == 429
            or error.code >= 500
            or (
                error.code == 403
                and error.headers.get("X-RateLimit-Remaining") == "0"
            )
        )

    @staticmethod
    def _retry_delay(headers, attempt):
        retry_after = headers.get("Retry-After")
        if retry_after:
            try:
                return min(max(float(retry_after), 0), 30)
            except ValueError:
                try:
                    retry_time = parsedate_to_datetime(retry_after).timestamp()
                    return min(max(retry_time - time.time(), 0), 30)
                except (TypeError, ValueError, OverflowError):
                    pass

        reset = headers.get("X-RateLimit-Reset")
        if reset:
            try:
                return min(max(float(reset) - time.time(), 0), 30)
            except ValueError:
                pass
        return min(2 ** attempt, 10)

    @staticmethod
    def _repository_path(repository):
        owner, name = repository.split("/", 1)
        return "/repos/{}/{}".format(quote(owner, safe=""), quote(name, safe=""))

    def get_issue(self, repository, issue_number):
        return self.request(
            "GET",
            "{}/issues/{}".format(self._repository_path(repository), issue_number),
        )

    def list_comments(self, repository, issue_number):
        comments = []
        repository_path = self._repository_path(repository)
        page = 1
        while True:
            query = urlencode({"per_page": 100, "page": page})
            batch = self.request(
                "GET",
                "{}/issues/{}/comments?{}".format(
                    repository_path, issue_number, query
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
                self._repository_path(repository), issue_number
            ),
            {"body": body},
            expected=(201,),
            retry=False,
        )

    def add_assignees(self, repository, issue_number, assignees):
        return self.request(
            "POST",
            "{}/issues/{}/assignees".format(
                self._repository_path(repository), issue_number
            ),
            {"assignees": list(assignees)},
            expected=(201,),
        )

    def remove_assignees(self, repository, issue_number, assignees):
        return self.request(
            "DELETE",
            "{}/issues/{}/assignees".format(
                self._repository_path(repository), issue_number
            ),
            {"assignees": list(assignees)},
        )

    def get_permission(self, repository, actor):
        try:
            return self.request(
                "GET",
                "{}/collaborators/{}/permission".format(
                    self._repository_path(repository), quote(actor, safe="")
                ),
            )
        except GitHubAPIError as error:
            if error.status == 404:
                return {}
            raise

    def can_assign(self, repository, issue_number, actor):
        try:
            self.request(
                "GET",
                "{}/issues/{}/assignees/{}".format(
                    self._repository_path(repository),
                    issue_number,
                    quote(actor, safe=""),
                ),
                expected=(204,),
            )
            return True
        except GitHubAPIError as error:
            if error.status == 404:
                return False
            raise

    def get_label(self, repository, label):
        try:
            return self.request(
                "GET",
                "{}/labels/{}".format(
                    self._repository_path(repository), quote(label, safe="")
                ),
            )
        except GitHubAPIError as error:
            if error.status == 404:
                return None
            raise

    def add_labels(self, repository, issue_number, labels):
        return self.request(
            "POST",
            "{}/issues/{}/labels".format(
                self._repository_path(repository), issue_number
            ),
            {"labels": list(labels)},
        )

    def remove_label(self, repository, issue_number, label):
        try:
            return self.request(
                "DELETE",
                "{}/issues/{}/labels/{}".format(
                    self._repository_path(repository),
                    issue_number,
                    quote(label, safe=""),
                ),
            )
        except GitHubAPIError as error:
            if error.status == 404:
                return None
            raise


def parse_command(body):
    if not isinstance(body, str):
        return None
    match = COMMAND_PATTERN.fullmatch(body)
    return match.group(1).lower() if match else None


def is_bot(user):
    if not isinstance(user, dict):
        return False
    login = str(user.get("login", "")).lower()
    return str(user.get("type", "")).lower() == "bot" or login.endswith("[bot]")


def is_workflow_bot(user):
    if not isinstance(user, dict):
        return False
    return str(user.get("login", "")).casefold() == "github-actions[bot]"


def event_context(event):
    if not isinstance(event, dict) or event.get("action") != "created":
        return None

    issue = event.get("issue") or {}
    comment = event.get("comment") or {}
    actor_data = event.get("sender") or comment.get("user") or {}
    command = parse_command(comment.get("body"))
    if not command or "pull_request" in issue or is_bot(actor_data):
        return None

    repository = (event.get("repository") or {}).get("full_name")
    actor = actor_data.get("login")
    try:
        issue_number = int(issue["number"])
        comment_id = int(comment["id"])
    except (KeyError, TypeError, ValueError):
        return None

    if not repository or repository.count("/") != 1 or not actor:
        return None
    return EventContext(
        command=command,
        repository=repository,
        issue_number=issue_number,
        actor=str(actor),
        comment_id=comment_id,
    )


def assignee_logins(issue):
    assignees = []
    for assignee in issue.get("assignees") or []:
        login = assignee.get("login") if isinstance(assignee, dict) else assignee
        if isinstance(login, str) and login:
            assignees.append(login)
    return tuple(assignees)


def decide_claim(issue, claimant=None):
    if str(issue.get("state", "")).casefold() != "open":
        return Decision(False, "closed")
    assignees = assignee_logins(issue)
    if assignees:
        return Decision(False, "assigned", assignees)
    if claimant:
        return Decision(False, "assigned", (claimant,))
    return Decision(True, "claim")


def has_maintainer_permission(permission):
    if not isinstance(permission, dict):
        return False
    roles = {
        str(permission.get("permission", "")).casefold(),
        str(permission.get("role_name", "")).casefold(),
    }
    nested = (permission.get("user") or {}).get("permissions") or {}
    return bool(roles.intersection(MAINTAINER_ROLES)) or bool(
        nested.get("admin") or nested.get("maintain")
    )


def decide_unclaim(issue, actor, maintainer=False, claimant=None):
    assignees = assignee_logins(issue)
    if not assignees and not claimant:
        return Decision(False, "unassigned")
    if maintainer:
        return Decision(True, "unclaim", assignees)
    actor_matches = [
        login for login in assignees if login.casefold() == actor.casefold()
    ]
    if actor_matches:
        return Decision(True, "unclaim", tuple(actor_matches))
    if claimant and claimant.casefold() == actor.casefold():
        return Decision(True, "unclaim")
    return Decision(False, "unauthorized", assignees or (claimant,))


def already_processed(comments, marker):
    for comment in comments or []:
        if not isinstance(comment, dict) or not is_workflow_bot(
            comment.get("user") or {}
        ):
            continue
        if marker in str(comment.get("body", "")):
            return True
    return False


def active_claimant(comments):
    claimant = None
    for comment in comments or []:
        if not isinstance(comment, dict) or not is_workflow_bot(
            comment.get("user") or {}
        ):
            continue
        for state, actor in STATE_MARKER.findall(str(comment.get("body", ""))):
            if state == "claimed":
                claimant = actor
            elif claimant and claimant.casefold() == actor.casefold():
                claimant = None
    return claimant


def format_users(logins):
    return ", ".join("@{}".format(login) for login in logins)


def rejection_message(command, decision):
    if command == "claim":
        if decision.reason == "closed":
            return "This issue is closed and cannot be claimed."
        if decision.reason == "assigned":
            return "This issue is already assigned to {}.".format(
                format_users(decision.assignees)
            )
        return "This issue cannot be claimed."

    if decision.reason == "unassigned":
        return "This issue has no assignee to remove."
    if decision.reason == "unauthorized":
        return "Only a current assignee or repository maintainer can use `/unclaim`."
    return "This issue cannot be unclaimed."


def post_result(client, context, message, state=None, claimant=None):
    markers = [context.marker]
    if state and claimant:
        markers.append(
            "<!-- rt-thread-issue-claim:state:{}:{} -->".format(state, claimant)
        )
    body = "{}\n{}".format("\n".join(markers), message)
    client.create_comment(context.repository, context.issue_number, body)


def update_progress_label(client, context, add):
    label = client.get_label(context.repository, PROGRESS_LABEL)
    if not label:
        return
    label_name = label.get("name", PROGRESS_LABEL)
    if add:
        client.add_labels(context.repository, context.issue_number, (label_name,))
    else:
        client.remove_label(context.repository, context.issue_number, label_name)


def handle_claim(client, context, comments):
    initial_issue = client.get_issue(context.repository, context.issue_number)
    initial = decide_claim(initial_issue, active_claimant(comments))
    if not initial.allowed:
        post_result(client, context, rejection_message("claim", initial))
        return initial.reason

    latest_comments = client.list_comments(context.repository, context.issue_number)
    latest_issue = client.get_issue(context.repository, context.issue_number)
    latest = decide_claim(latest_issue, active_claimant(latest_comments))
    if not latest.allowed:
        post_result(client, context, rejection_message("claim", latest))
        return "race_{}".format(latest.reason)

    assignable = client.can_assign(
        context.repository, context.issue_number, context.actor
    )
    if assignable:
        client.add_assignees(context.repository, context.issue_number, (context.actor,))
    confirmed_issue = client.get_issue(context.repository, context.issue_number)
    confirmed_assignees = assignee_logins(confirmed_issue)
    actor_is_assigned = any(
        login.casefold() == context.actor.casefold() for login in confirmed_assignees
    )
    other_assignees = tuple(
        login
        for login in confirmed_assignees
        if login.casefold() != context.actor.casefold()
    )
    if (assignable and not actor_is_assigned) or other_assignees:
        if assignable and actor_is_assigned:
            client.remove_assignees(
                context.repository, context.issue_number, (context.actor,)
            )
        decision = Decision(False, "assigned", other_assignees or confirmed_assignees)
        post_result(client, context, rejection_message("claim", decision))
        return "race_assigned"

    if assignable:
        update_progress_label(client, context, add=True)
        message = "@{} has claimed this issue.".format(context.actor)
        result = "claimed"
        post_result(client, context, message)
    else:
        message = (
            "@{} has claimed this issue. GitHub cannot assign this account, so "
            "the claim is tracked by this comment and the `in progress` label."
        ).format(context.actor)
        result = "claimed_by_comment"
        post_result(
            client,
            context,
            message,
            state="claimed",
            claimant=context.actor,
        )
        update_progress_label(client, context, add=True)
    return result


def handle_unclaim(client, context, comments):
    permission = client.get_permission(context.repository, context.actor)
    maintainer = has_maintainer_permission(permission)
    initial_issue = client.get_issue(context.repository, context.issue_number)
    initial = decide_unclaim(
        initial_issue, context.actor, maintainer, active_claimant(comments)
    )
    if not initial.allowed:
        post_result(client, context, rejection_message("unclaim", initial))
        return initial.reason

    latest_comments = client.list_comments(context.repository, context.issue_number)
    latest_issue = client.get_issue(context.repository, context.issue_number)
    latest_claimant = active_claimant(latest_comments)
    latest = decide_unclaim(
        latest_issue, context.actor, maintainer, latest_claimant
    )
    if not latest.allowed:
        post_result(client, context, rejection_message("unclaim", latest))
        return "race_{}".format(latest.reason)

    if latest.assignees:
        client.remove_assignees(
            context.repository, context.issue_number, latest.assignees
        )
    confirmed_issue = client.get_issue(context.repository, context.issue_number)
    remaining = assignee_logins(confirmed_issue)
    removed = {login.casefold() for login in latest.assignees}.isdisjoint(
        login.casefold() for login in remaining
    )
    if not removed:
        raise GitHubAPIError(None, "assignee removal was not applied")

    release_logical = bool(
        latest_claimant
        and (
            maintainer
            or latest_claimant.casefold() == context.actor.casefold()
        )
    )
    released_users = list(latest.assignees)
    if release_logical:
        released_users.append(latest_claimant)
    post_result(
        client,
        context,
        "Released this issue from {}.".format(
            format_users(dict.fromkeys(released_users))
        ),
        state="unclaimed" if release_logical else None,
        claimant=latest_claimant if release_logical else None,
    )
    if not remaining and not (latest_claimant and not release_logical):
        update_progress_label(client, context, add=False)
    return "unclaimed"


def handle_event(event, client):
    context = event_context(event)
    if context is None:
        return "ignored"

    comments = client.list_comments(context.repository, context.issue_number)
    if already_processed(comments, context.marker):
        return "duplicate"

    if context.command == "claim":
        return handle_claim(client, context, comments)
    return handle_unclaim(client, context, comments)


def load_event(path):
    with open(path, "r", encoding="utf-8") as event_file:
        return json.load(event_file)


def main():
    event_path = os.getenv("GITHUB_EVENT_PATH")
    if not event_path:
        print("GITHUB_EVENT_PATH is required", file=sys.stderr)
        return 2

    try:
        event = load_event(event_path)
    except (OSError, ValueError) as error:
        print("Unable to read GitHub event: {}".format(error), file=sys.stderr)
        return 2

    if event_context(event) is None:
        print("Ignoring event: no supported issue command")
        return 0

    try:
        client = GitHubClient(
            os.getenv("GITHUB_TOKEN", ""),
            os.getenv("GITHUB_API_URL", "https://api.github.com"),
        )
        result = handle_event(event, client)
    except (GitHubAPIError, ValueError) as error:
        print(str(error), file=sys.stderr)
        return 1

    print("Issue command result: {}".format(result))
    return 0


if __name__ == "__main__":
    sys.exit(main())
