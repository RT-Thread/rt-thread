#!/usr/bin/env python3
#
# Copyright (c) 2026, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#

import unittest

import issue_labeler


def make_event(body, labels=(), action="opened"):
    return {
        "action": action,
        "repository": {"full_name": "RT-Thread/rt-thread"},
        "issue": {
            "number": 42,
            "body": body,
            "labels": [{"name": label} for label in labels],
        },
    }


class FakeClient:
    def __init__(self, available_labels, current_issue=None):
        self.available_labels = [{"name": label} for label in available_labels]
        self.current_issue = current_issue
        self.calls = []

    def list_labels(self, repository):
        self.calls.append(("list_labels", repository))
        return self.available_labels

    def add_labels(self, repository, issue_number, labels):
        self.calls.append(("add_labels", repository, issue_number, tuple(labels)))

    def get_issue(self, repository, issue_number):
        self.calls.append(("get_issue", repository, issue_number))
        return self.current_issue

    def remove_label(self, repository, issue_number, label):
        self.calls.append(("remove_label", repository, issue_number, label))


class FormParsingTests(unittest.TestCase):
    def test_maps_only_structured_allowlisted_values(self):
        body = """### Affected area

Device drivers

### Hardware/BSP vendor

STM32

### Architecture

ARM / AArch64

### Describe the bug

Mentions GD32 and RISC-V here, but free text must not add labels.
"""
        self.assertEqual(
            issue_labeler.desired_labels(body),
            (
                "Component",
                "component: drivers",
                "BSP",
                "BSP: STM32",
                "Arch: ARM/AArch64",
            ),
        )

    def test_unknown_and_no_response_values_are_ignored(self):
        body = """### Affected area

Other / Not sure

### Hardware/BSP vendor

_No response_

### Architecture

x86
"""
        self.assertEqual(issue_labeler.desired_labels(body), ())

    def test_headings_and_values_are_case_insensitive(self):
        body = "### AFFECTED AREA\n\nnetworking\n\n### Architecture\n\nrisc-v\n"
        self.assertEqual(
            issue_labeler.desired_labels(body),
            ("Component", "component: net", "Arch: RISC-V"),
        )


class EventTests(unittest.TestCase):
    def test_accepts_supported_issue_actions(self):
        context = issue_labeler.event_context(make_event("", action="edited"))
        self.assertEqual(context.issue_number, 42)

    def test_rejects_pull_requests_and_other_actions(self):
        pull_request = make_event("")
        pull_request["issue"]["pull_request"] = {"url": "https://example.test"}
        self.assertIsNone(issue_labeler.event_context(pull_request))
        self.assertIsNone(
            issue_labeler.event_context(make_event("", action="closed"))
        )


class LabelApplicationTests(unittest.TestCase):
    def test_adds_only_existing_labels_and_preserves_current_labels(self):
        body = """### Affected area

Kernel

### Hardware/BSP vendor

GD32
"""
        context = issue_labeler.event_context(
            make_event(body, labels=("Kernel", "bug"))
        )
        client = FakeClient(("Kernel", "BSP", "bug"))

        result = issue_labeler.apply_labels(client, context)

        self.assertEqual(result["added"], ["BSP"])
        self.assertEqual(result["missing"], ["BSP: GD32"])
        self.assertIn(
            ("add_labels", "RT-Thread/rt-thread", 42, ("BSP",)), client.calls
        )

    def test_replaces_stale_vendor_and_architecture_labels(self):
        body = """### Hardware/BSP vendor

NXP

### Architecture

RISC-V
"""
        context = issue_labeler.event_context(
            make_event(
                body,
                labels=("bug", "BSP", "BSP: STM32", "Arch: ARM/AArch64"),
            )
        )
        client = FakeClient(
            (
                "bug",
                "BSP",
                "BSP: STM32",
                "BSP: NXP",
                "Arch: ARM/AArch64",
                "Arch: RISC-V",
            ),
            current_issue=context.issue,
        )

        result = issue_labeler.apply_labels(client, context)

        self.assertEqual(result["added"], ["BSP: NXP", "Arch: RISC-V"])
        self.assertEqual(result["removed"], ["BSP: STM32", "Arch: ARM/AArch64"])
        self.assertIn(
            ("remove_label", "RT-Thread/rt-thread", 42, "BSP: STM32"),
            client.calls,
        )
        self.assertIn(
            ("remove_label", "RT-Thread/rt-thread", 42, "Arch: ARM/AArch64"),
            client.calls,
        )

    def test_dry_run_reports_without_mutating(self):
        body = "### Affected area\n\nDocumentation\n"
        context = issue_labeler.event_context(make_event(body))
        client = FakeClient(("Doc",))

        result = issue_labeler.apply_labels(client, context, dry_run=True)

        self.assertEqual(result["added"], ["Doc"])
        self.assertFalse(any(call[0] == "add_labels" for call in client.calls))


if __name__ == "__main__":
    unittest.main()
