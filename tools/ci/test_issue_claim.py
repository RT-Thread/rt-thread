#!/usr/bin/env python3
#
# Copyright (c) 2026, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#

import unittest

import issue_claim


def make_issue(state="open", labels=(), assignees=()):
    return {
        "state": state,
        "labels": [{"name": label} for label in labels],
        "assignees": [{"login": login} for login in assignees],
    }


def make_event(command="/claim", actor="alice", comment_id=100):
    return {
        "action": "created",
        "repository": {"full_name": "RT-Thread/rt-thread"},
        "issue": {"number": 42},
        "comment": {
            "id": comment_id,
            "body": command,
            "created_at": "2026-07-23T08:00:00Z",
            "user": {"login": actor, "type": "User"},
        },
        "sender": {"login": actor, "type": "User"},
    }


class FakeClient:
    def __init__(
        self,
        issues,
        permission=None,
        comments=None,
        progress_label=None,
        assignable=True,
    ):
        self.issues = list(issues)
        self.permission = permission or {}
        self.comments = comments or []
        self.progress_label = progress_label
        self.assignable = assignable
        self.calls = []
        self.current_issue = self.issues[-1] if self.issues else make_issue()

    def list_comments(self, repository, issue_number):
        self.calls.append(("list_comments", repository, issue_number))
        return self.comments

    def get_issue(self, repository, issue_number):
        self.calls.append(("get_issue", repository, issue_number))
        if self.issues:
            self.current_issue = self.issues.pop(0)
        return self.current_issue

    def create_comment(self, repository, issue_number, body):
        self.calls.append(("create_comment", repository, issue_number, body))

    def add_assignees(self, repository, issue_number, assignees):
        self.calls.append(("add_assignees", repository, issue_number, tuple(assignees)))

    def remove_assignees(self, repository, issue_number, assignees):
        self.calls.append(
            ("remove_assignees", repository, issue_number, tuple(assignees))
        )

    def get_permission(self, repository, actor):
        self.calls.append(("get_permission", repository, actor))
        return self.permission

    def can_assign(self, repository, issue_number, actor):
        self.calls.append(("can_assign", repository, issue_number, actor))
        return self.assignable

    def get_label(self, repository, label):
        self.calls.append(("get_label", repository, label))
        return self.progress_label

    def add_labels(self, repository, issue_number, labels):
        self.calls.append(("add_labels", repository, issue_number, tuple(labels)))

    def remove_label(self, repository, issue_number, label):
        self.calls.append(("remove_label", repository, issue_number, label))


class ClientTests(unittest.TestCase):
    def test_assignability_is_checked_for_specific_issue(self):
        class RecordingClient(issue_claim.GitHubClient):
            def __init__(self):
                self.call = None

            def request(self, *args, **kwargs):
                self.call = (args, kwargs)

        client = RecordingClient()

        self.assertTrue(
            client.can_assign("RT-Thread/rt-thread", 42, "external-user")
        )
        self.assertEqual(
            client.call[0],
            (
                "GET",
                "/repos/RT-Thread/rt-thread/issues/42/assignees/external-user",
            ),
        )
        self.assertEqual(client.call[1]["expected"], (204,))

    def test_comment_creation_disables_automatic_retries(self):
        class RecordingClient(issue_claim.GitHubClient):
            def __init__(self):
                self.call = None

            def request(self, *args, **kwargs):
                self.call = (args, kwargs)

        client = RecordingClient()
        client.create_comment("RT-Thread/rt-thread", 42, "result")

        self.assertFalse(client.call[1]["retry"])

    def test_comment_pagination_reads_past_five_hundred(self):
        class PagingClient(issue_claim.GitHubClient):
            def __init__(self):
                self.pages = 0

            def request(self, *args, **kwargs):
                self.pages += 1
                size = 100 if self.pages <= 5 else 1
                return [{"id": self.pages * 100 + index} for index in range(size)]

        client = PagingClient()
        comments = client.list_comments("RT-Thread/rt-thread", 42)

        self.assertEqual(len(comments), 501)
        self.assertEqual(client.pages, 6)


class CommandParsingTests(unittest.TestCase):
    def test_accepts_only_standalone_commands(self):
        self.assertEqual(issue_claim.parse_command("/claim"), "claim")
        self.assertEqual(issue_claim.parse_command("/UNCLAIM"), "unclaim")
        for body in (
            " /claim",
            "/claim\n",
            "/claim me",
            "please /claim",
            "/claim\nthanks",
            "`/claim`",
            "",
        ):
            self.assertIsNone(issue_claim.parse_command(body))

    def test_filters_pull_requests_bots_and_other_actions(self):
        pull_request = make_event()
        pull_request["issue"]["pull_request"] = {"url": "https://example.test/pr/42"}
        self.assertIsNone(issue_claim.event_context(pull_request))

        bot = make_event(actor="helper[bot]")
        self.assertIsNone(issue_claim.event_context(bot))

        edited = make_event()
        edited["action"] = "edited"
        self.assertIsNone(issue_claim.event_context(edited))


class PermissionTests(unittest.TestCase):
    def test_only_admin_and_maintain_roles_are_maintainers(self):
        self.assertTrue(
            issue_claim.has_maintainer_permission({"role_name": "maintain"})
        )
        self.assertTrue(issue_claim.has_maintainer_permission({"permission": "admin"}))
        self.assertTrue(
            issue_claim.has_maintainer_permission(
                {"user": {"permissions": {"maintain": True}}}
            )
        )
        self.assertFalse(issue_claim.has_maintainer_permission({"permission": "write"}))
        self.assertFalse(issue_claim.has_maintainer_permission({"role_name": "triage"}))

    def test_unclaim_targets_self_or_all_for_maintainer(self):
        own = issue_claim.decide_unclaim(
            make_issue(assignees=("alice", "bob")), "Alice"
        )
        self.assertTrue(own.allowed)
        self.assertEqual(own.assignees, ("alice",))

        denied = issue_claim.decide_unclaim(make_issue(assignees=("bob",)), "alice")
        self.assertFalse(denied.allowed)
        self.assertEqual(denied.reason, "unauthorized")

        maintainer = issue_claim.decide_unclaim(
            make_issue(assignees=("bob", "carol")), "alice", maintainer=True
        )
        self.assertTrue(maintainer.allowed)
        self.assertEqual(maintainer.assignees, ("bob", "carol"))


class ClaimStateTests(unittest.TestCase):
    def test_claim_requires_open_unassigned_issue(self):
        self.assertTrue(issue_claim.decide_claim(make_issue()).allowed)
        self.assertTrue(
            issue_claim.decide_claim(make_issue(labels=("bug",))).allowed
        )
        self.assertEqual(
            issue_claim.decide_claim(make_issue(state="closed")).reason, "closed"
        )
        self.assertEqual(
            issue_claim.decide_claim(make_issue(assignees=("bob",))).reason,
            "assigned",
        )

    def test_duplicate_marker_must_come_from_a_bot(self):
        marker = "<!-- rt-thread-issue-claim:100 -->"
        user_comment = {"body": marker, "user": {"login": "alice", "type": "User"}}
        bot_comment = {
            "body": marker + "\nDone",
            "user": {"login": "github-actions[bot]", "type": "Bot"},
        }
        other_bot_comment = {
            "body": marker,
            "user": {"login": "helper[bot]", "type": "Bot"},
        }
        self.assertFalse(issue_claim.already_processed([user_comment], marker))
        self.assertFalse(issue_claim.already_processed([other_bot_comment], marker))
        self.assertTrue(issue_claim.already_processed([bot_comment], marker))

    def test_last_bot_state_marker_controls_logical_claim(self):
        comments = [
            {
                "body": "<!-- rt-thread-issue-claim:state:claimed:alice -->",
                "user": {"login": "github-actions[bot]", "type": "Bot"},
            },
            {
                "body": "<!-- rt-thread-issue-claim:state:unclaimed:alice -->",
                "user": {"login": "github-actions[bot]", "type": "Bot"},
            },
            {
                "body": "<!-- rt-thread-issue-claim:state:claimed:bob -->",
                "user": {"login": "github-actions[bot]", "type": "Bot"},
            },
        ]
        self.assertEqual(issue_claim.active_claimant(comments), "bob")

    def test_unclaim_marker_only_clears_the_matching_logical_claim(self):
        comments = [
            {
                "body": "<!-- rt-thread-issue-claim:state:claimed:bob -->",
                "user": {"login": "github-actions[bot]", "type": "Bot"},
            },
            {
                "body": "<!-- rt-thread-issue-claim:state:unclaimed:alice -->",
                "user": {"login": "github-actions[bot]", "type": "Bot"},
            },
        ]
        self.assertEqual(issue_claim.active_claimant(comments), "bob")


class HandlerTests(unittest.TestCase):
    def test_successful_claim_rechecks_and_confirms_state(self):
        client = FakeClient(
            [
                make_issue(),
                make_issue(),
                make_issue(assignees=("alice",)),
            ],
            progress_label={"name": "in progress"},
        )
        result = issue_claim.handle_event(make_event(), client)

        self.assertEqual(result, "claimed")
        self.assertIn(
            ("can_assign", "RT-Thread/rt-thread", 42, "alice"), client.calls
        )
        self.assertIn(
            ("add_assignees", "RT-Thread/rt-thread", 42, ("alice",)),
            client.calls,
        )
        self.assertIn(
            ("add_labels", "RT-Thread/rt-thread", 42, ("in progress",)),
            client.calls,
        )
        comment = [call for call in client.calls if call[0] == "create_comment"][-1]
        self.assertIn("<!-- rt-thread-issue-claim:100 -->", comment[3])
        self.assertNotIn("state:claimed", comment[3])

    def test_unassignable_user_is_tracked_by_comment_and_label(self):
        client = FakeClient(
            [make_issue(), make_issue(), make_issue()],
            progress_label={"name": "in progress"},
            assignable=False,
        )

        result = issue_claim.handle_event(make_event(), client)

        self.assertEqual(result, "claimed_by_comment")
        self.assertFalse(any(call[0] == "add_assignees" for call in client.calls))
        self.assertIn(
            ("add_labels", "RT-Thread/rt-thread", 42, ("in progress",)),
            client.calls,
        )
        comment = [call for call in client.calls if call[0] == "create_comment"][-1]
        self.assertIn("state:claimed:alice", comment[3])

    def test_existing_logical_claim_blocks_another_user(self):
        comments = [
            {
                "body": "<!-- rt-thread-issue-claim:state:claimed:bob -->",
                "user": {"login": "github-actions[bot]", "type": "Bot"},
            }
        ]
        client = FakeClient([make_issue()], comments=comments)

        result = issue_claim.handle_event(make_event(actor="alice"), client)

        self.assertEqual(result, "assigned")
        self.assertFalse(any(call[0] == "add_assignees" for call in client.calls))
        comment = [call for call in client.calls if call[0] == "create_comment"][-1]
        self.assertIn("@bob", comment[3])

    def test_concurrent_claim_is_rejected_before_mutation(self):
        client = FakeClient(
            [make_issue(), make_issue(assignees=("bob",))]
        )
        result = issue_claim.handle_event(make_event(), client)

        self.assertEqual(result, "race_assigned")
        self.assertFalse(any(call[0] == "add_assignees" for call in client.calls))
        comment = [call for call in client.calls if call[0] == "create_comment"][-1]
        self.assertIn("@bob", comment[3])

    def test_post_assignment_race_rolls_back_actor(self):
        client = FakeClient(
            [
                make_issue(),
                make_issue(),
                make_issue(assignees=("alice", "bob")),
            ]
        )
        result = issue_claim.handle_event(make_event(), client)

        self.assertEqual(result, "race_assigned")
        self.assertIn(
            ("remove_assignees", "RT-Thread/rt-thread", 42, ("alice",)),
            client.calls,
        )
        self.assertFalse(any(call[0] == "add_labels" for call in client.calls))

    def test_non_assignee_cannot_unclaim(self):
        client = FakeClient([make_issue(assignees=("bob",))])
        result = issue_claim.handle_event(make_event("/unclaim"), client)

        self.assertEqual(result, "unauthorized")
        self.assertFalse(any(call[0] == "remove_assignees" for call in client.calls))

    def test_assignee_can_unclaim_and_remove_existing_progress_label(self):
        client = FakeClient(
            [
                make_issue(assignees=("alice",)),
                make_issue(assignees=("alice",)),
                make_issue(assignees=()),
            ],
            progress_label={"name": "in progress"},
        )
        result = issue_claim.handle_event(make_event("/unclaim"), client)

        self.assertEqual(result, "unclaimed")
        self.assertIn(
            ("remove_assignees", "RT-Thread/rt-thread", 42, ("alice",)),
            client.calls,
        )
        self.assertIn(
            ("remove_label", "RT-Thread/rt-thread", 42, "in progress"),
            client.calls,
        )

    def test_logical_claimant_can_unclaim_without_being_an_assignee(self):
        comments = [
            {
                "body": "<!-- rt-thread-issue-claim:state:claimed:alice -->",
                "user": {"login": "github-actions[bot]", "type": "Bot"},
            }
        ]
        client = FakeClient(
            [make_issue(), make_issue(), make_issue()],
            comments=comments,
            progress_label={"name": "in progress"},
            assignable=False,
        )

        result = issue_claim.handle_event(make_event("/unclaim"), client)

        self.assertEqual(result, "unclaimed")
        self.assertFalse(any(call[0] == "remove_assignees" for call in client.calls))
        self.assertIn(
            ("remove_label", "RT-Thread/rt-thread", 42, "in progress"),
            client.calls,
        )
        comment = [call for call in client.calls if call[0] == "create_comment"][-1]
        self.assertIn("state:unclaimed:alice", comment[3])

    def test_actual_assignee_unclaim_does_not_clear_another_logical_claim(self):
        comments = [
            {
                "body": "<!-- rt-thread-issue-claim:state:claimed:bob -->",
                "user": {"login": "github-actions[bot]", "type": "Bot"},
            }
        ]
        client = FakeClient(
            [
                make_issue(assignees=("alice",)),
                make_issue(assignees=("alice",)),
                make_issue(),
            ],
            comments=comments,
            progress_label={"name": "in progress"},
        )

        result = issue_claim.handle_event(make_event("/unclaim"), client)

        self.assertEqual(result, "unclaimed")
        self.assertFalse(any(call[0] == "remove_label" for call in client.calls))
        comment = [call for call in client.calls if call[0] == "create_comment"][-1]
        self.assertNotIn("state:unclaimed:bob", comment[3])

    def test_logical_unclaim_preserves_an_unrelated_actual_assignee(self):
        comments = [
            {
                "body": "<!-- rt-thread-issue-claim:state:claimed:bob -->",
                "user": {"login": "github-actions[bot]", "type": "Bot"},
            }
        ]
        client = FakeClient(
            [
                make_issue(assignees=("alice",)),
                make_issue(assignees=("alice",)),
                make_issue(assignees=("alice",)),
            ],
            comments=comments,
            progress_label={"name": "in progress"},
        )

        result = issue_claim.handle_event(
            make_event("/unclaim", actor="bob"), client
        )

        self.assertEqual(result, "unclaimed")
        self.assertFalse(any(call[0] == "remove_assignees" for call in client.calls))
        self.assertFalse(any(call[0] == "remove_label" for call in client.calls))
        comment = [call for call in client.calls if call[0] == "create_comment"][-1]
        self.assertIn("state:unclaimed:bob", comment[3])

    def test_duplicate_event_does_not_read_or_mutate_issue(self):
        marker = "<!-- rt-thread-issue-claim:100 -->"
        client = FakeClient(
            [make_issue()],
            comments=[
                {
                    "body": marker,
                    "user": {"login": "github-actions[bot]", "type": "Bot"},
                }
            ],
        )
        result = issue_claim.handle_event(make_event(), client)

        self.assertEqual(result, "duplicate")
        self.assertFalse(any(call[0] == "get_issue" for call in client.calls))


if __name__ == "__main__":
    unittest.main()
