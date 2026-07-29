#!/usr/bin/env python3
#
# Copyright (c) 2026, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#

"""Add existing RT-Thread labels from structured GitHub issue-form fields."""

import json
import os
import re
import sys
import unicodedata
from dataclasses import dataclass
from urllib.error import HTTPError, URLError
from urllib.parse import quote, urlencode
from urllib.request import Request, urlopen


API_VERSION = "2022-11-28"
FORM_SECTION = re.compile(r"^###\s+(.+?)\s*$", re.MULTILINE)

AREA_LABELS = {
    "kernel": ("Kernel",),
    "board support package (bsp)": ("BSP",),
    "device drivers": ("Component", "component: drivers"),
    "file systems (dfs)": ("Component",),
    "networking": ("Component", "component: net"),
    "ipc": ("Component", "component: ipc"),
    "finsh": ("Component", "component: finsh"),
    "rt-smart": ("RT-Smart",),
    "architecture / libcpu": ("libcpu",),
    "documentation": ("Doc",),
    "build system and tools": ("tools",),
    "ci / github actions": ("action",),
    "tests and examples": ("testcase",),
}

VENDOR_LABELS = {
    "stm32": ("BSP", "BSP: STM32"),
    "nxp": ("BSP", "BSP: NXP"),
    "gd32": ("BSP", "BSP: GD32"),
    "at32": ("BSP", "BSP: AT32"),
    "infineon": ("BSP", "BSP: Infineon"),
    "renesas": ("BSP", "BSP: Renesas"),
    "phytium": ("BSP", "BSP: Phytium"),
    "cvitek": ("BSP", "BSP: Cvitek"),
    "wch": ("BSP", "BSP: WCH"),
    "raspberry pi": ("BSP", "BSP: Raspberry-Pi"),
    "rockchip": ("BSP", "BSP: Rockchip"),
    "loongson": ("BSP", "BSP: Loongson"),
    "esp32": ("BSP", "BSP: ESP32"),
    "hc32": ("BSP", "BSP: HC32"),
    "novosns": ("BSP", "BSP: Novosns"),
    "hpmicro": ("BSP", "BSP: HPMicro"),
    "bluetrum": ("BSP", "BSP: Bluetrum"),
    "k230": ("BSP", "BSP: K230"),
    "nuvoton": ("BSP", "BSP: Nuvoton"),
}

ARCHITECTURE_LABELS = {
    "arm / aarch64": ("Arch: ARM/AArch64",),
    "risc-v": ("Arch: RISC-V",),
}

FIELD_MAPPINGS = {
    "affected area": AREA_LABELS,
    "hardware/bsp vendor": VENDOR_LABELS,
    "architecture": ARCHITECTURE_LABELS,
}

MUTUALLY_EXCLUSIVE_FIELDS = {
    "hardware/bsp vendor": frozenset(
        label.casefold()
        for labels in VENDOR_LABELS.values()
        for label in labels
        if label.casefold().startswith("bsp:")
    ),
    "architecture": frozenset(
        label.casefold()
        for labels in ARCHITECTURE_LABELS.values()
        for label in labels
    ),
}
EMPTY_FIELD_VALUES = frozenset(("not applicable / other",))


@dataclass(frozen=True)
class EventContext:
    repository: str
    issue_number: int
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
            "User-Agent": "rt-thread-issue-labeler",
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

    def list_labels(self, repository):
        labels = []
        repository_path = self.repository_path(repository)
        for page in range(1, 11):
            query = urlencode({"per_page": 100, "page": page})
            batch = self.request("GET", "{}/labels?{}".format(repository_path, query))
            labels.extend(batch)
            if len(batch) < 100:
                break
        return labels

    def get_issue(self, repository, issue_number):
        return self.request(
            "GET",
            "{}/issues/{}".format(self.repository_path(repository), issue_number),
        )

    def add_labels(self, repository, issue_number, labels):
        return self.request(
            "POST",
            "{}/issues/{}/labels".format(
                self.repository_path(repository), issue_number
            ),
            {"labels": list(labels)},
        )

    def remove_label(self, repository, issue_number, label):
        try:
            return self.request(
                "DELETE",
                "{}/issues/{}/labels/{}".format(
                    self.repository_path(repository),
                    issue_number,
                    quote(label, safe=""),
                ),
            )
        except GitHubAPIError as error:
            if error.status == 404:
                return None
            raise


def normalize(value):
    return " ".join(
        unicodedata.normalize("NFKC", str(value or "")).strip().casefold().split()
    )


def parse_form_sections(body):
    text = str(body or "")
    matches = list(FORM_SECTION.finditer(text))
    sections = {}
    for index, match in enumerate(matches):
        start = match.end()
        end = matches[index + 1].start() if index + 1 < len(matches) else len(text)
        value = text[start:end].strip()
        if value == "_No response_":
            value = ""
        sections[normalize(match.group(1))] = value
    return sections


def desired_labels(body):
    sections = parse_form_sections(body)
    result = []
    seen = set()
    for field, mapping in FIELD_MAPPINGS.items():
        value = normalize(sections.get(field, ""))
        for label in mapping.get(value, ()):
            key = label.casefold()
            if key not in seen:
                seen.add(key)
                result.append(label)
    return tuple(result)


def event_context(event):
    if not isinstance(event, dict):
        return None
    if event.get("action") not in ("opened", "edited", "reopened"):
        return None
    issue = event.get("issue") or {}
    if "pull_request" in issue:
        return None
    repository = (event.get("repository") or {}).get("full_name")
    try:
        issue_number = int(issue["number"])
    except (KeyError, TypeError, ValueError):
        return None
    if not repository or repository.count("/") != 1:
        return None
    return EventContext(repository, issue_number, issue)


def existing_label_names(issue):
    names = set()
    for label in issue.get("labels") or []:
        name = label.get("name") if isinstance(label, dict) else label
        if isinstance(name, str):
            names.add(name.casefold())
    return names


def existing_label_map(issue):
    labels = {}
    for label in issue.get("labels") or []:
        name = label.get("name") if isinstance(label, dict) else label
        if isinstance(name, str):
            labels[name.casefold()] = name
    return labels


def obsolete_labels(body, issue):
    sections = parse_form_sections(body)
    existing = existing_label_map(issue)
    obsolete = []
    for field, managed in MUTUALLY_EXCLUSIVE_FIELDS.items():
        value = normalize(sections.get(field, ""))
        mapping = FIELD_MAPPINGS[field]
        if value not in mapping and value not in EMPTY_FIELD_VALUES:
            continue
        selected = {label.casefold() for label in mapping.get(value, ())}
        obsolete.extend(
            existing[label]
            for label in sorted(managed)
            if label in existing and label not in selected
        )
    return tuple(obsolete)


def apply_labels(client, context, dry_run=False):
    issue = client.get_issue(context.repository, context.issue_number) or context.issue
    requested = desired_labels(issue.get("body", ""))
    available = {
        label["name"].casefold(): label["name"]
        for label in client.list_labels(context.repository)
        if isinstance(label, dict) and isinstance(label.get("name"), str)
    }
    existing = existing_label_names(issue)
    missing = [label for label in requested if label.casefold() not in available]
    to_add = [
        available[label.casefold()]
        for label in requested
        if label.casefold() in available and label.casefold() not in existing
    ]
    to_remove = list(obsolete_labels(issue.get("body", ""), issue))

    if missing:
        print("Skipping labels that do not exist: {}".format(", ".join(missing)))
    if to_add and not dry_run:
        client.add_labels(context.repository, context.issue_number, to_add)
    if to_remove and not dry_run:
        for label in to_remove:
            client.remove_label(context.repository, context.issue_number, label)

    return {
        "requested": list(requested),
        "added": to_add,
        "removed": to_remove,
        "missing": missing,
    }


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

    context = event_context(event)
    if context is None:
        print("Ignoring event: no supported issue")
        return 0

    try:
        client = GitHubClient(
            os.getenv("GITHUB_TOKEN", ""),
            os.getenv("GITHUB_API_URL", "https://api.github.com"),
        )
        result = apply_labels(
            client,
            context,
            dry_run=normalize(os.getenv("DRY_RUN", "")) in ("1", "true", "yes"),
        )
    except (GitHubAPIError, ValueError) as error:
        print(str(error), file=sys.stderr)
        return 1

    print(json.dumps(result, ensure_ascii=True, sort_keys=True))
    return 0


if __name__ == "__main__":
    sys.exit(main())
