#!/usr/bin/env python3
#
# Copyright (c) 2026, RT-Thread Development Team
#
# SPDX-License-Identifier: Apache-2.0
#

import unittest

import similar_issues


def make_issue(number, title, body="", labels=(), assignees=()):
    return {
        "number": number,
        "title": title,
        "body": body,
        "labels": [{"name": label} for label in labels],
        "assignees": [{"login": login} for login in assignees],
    }


class FakeClient:
    def __init__(
        self,
        search_items=(),
        comments=(),
        open_issues=(),
        search_error=None,
        comment_batches=None,
    ):
        self.search_items = list(search_items)
        self.comments = list(comments)
        self.open_issues = list(open_issues)
        self.search_error = search_error
        self.comment_batches = (
            [list(batch) for batch in comment_batches]
            if comment_batches is not None
            else None
        )
        self.calls = []

    def list_comments(self, repository, issue_number):
        self.calls.append(("list_comments", repository, issue_number))
        if self.comment_batches:
            return self.comment_batches.pop(0)
        return self.comments

    def search_issues(self, repository, query):
        self.calls.append(("search_issues", repository, query))
        if self.search_error:
            raise self.search_error
        return {"items": self.search_items}

    def create_comment(self, repository, issue_number, body):
        self.calls.append(("create_comment", repository, issue_number, body))

    def list_open_issues(self, repository, limit):
        self.calls.append(("list_open_issues", repository, limit))
        return self.open_issues[:limit]


class TextTests(unittest.TestCase):
    def test_ignores_issue_form_metadata(self):
        body = """### RT-Thread Version

v5.2.2

### Hardware/BSP vendor

STM32

### Describe the bug

rt_event_send resumes a timed out thread twice.
"""
        relevant = similar_issues.relevant_body(body)
        self.assertNotIn("STM32", relevant)
        self.assertNotIn("v5.2.2", relevant)
        self.assertIn("rt_event_send", relevant)

    def test_search_terms_prioritize_identifiers(self):
        issue = make_issue(1, "[Bug] rt_event_send timeout race resumes thread twice")
        self.assertEqual(similar_issues.search_terms(issue), "rt_event_send")


class RankingTests(unittest.TestCase):
    def test_accepts_matching_technical_issue(self):
        issue = make_issue(
            10,
            "[Bug] rt_event_send can resume a timed out thread twice",
            "The event send path races with a thread timeout.",
            labels=("Kernel",),
        )
        candidate = make_issue(
            9,
            "rt_event_send timeout race resumes thread twice",
            "A timed out thread can be resumed twice by event send.",
            labels=("Kernel",),
        )
        result = similar_issues.score_candidate(issue, candidate)
        self.assertTrue(result["accepted"])

    def test_accepts_similar_chinese_issue(self):
        issue = make_issue(10, "[Bug] rt_vsnprintf格式化long long数值错误")
        candidate = make_issue(9, "rt_vsnprintf处理long long格式化结果异常")
        self.assertTrue(similar_issues.score_candidate(issue, candidate)["accepted"])

    def test_rejects_unrelated_and_conflicting_bsp_issues(self):
        issue = make_issue(
            10, "STM32 UART interrupt loses bytes", labels=("BSP: STM32",)
        )
        unrelated = make_issue(9, "Update documentation links", labels=("Doc",))
        conflicting = make_issue(
            8, "STM32 UART interrupt loses bytes", labels=("BSP: NXP",)
        )
        self.assertFalse(similar_issues.score_candidate(issue, unrelated)["accepted"])
        self.assertEqual(
            similar_issues.score_candidate(issue, conflicting)["reason"],
            "bsp-mismatch",
        )

    def test_derives_bsp_labels_from_structured_form_fields(self):
        issue = make_issue(
            10,
            "UART interrupt loses bytes",
            "### Hardware/BSP vendor\n\nSTM32\n",
            labels=("BSP: NXP",),
        )
        candidate = make_issue(
            9,
            "UART interrupt loses bytes",
            "### Hardware/BSP vendor\n\nNXP\n",
        )

        result = similar_issues.score_candidate(issue, candidate)

        self.assertFalse(result["accepted"])
        self.assertEqual(result["reason"], "bsp-mismatch")

    def test_excludes_current_pr_and_limits_results(self):
        issue = make_issue(10, "rt_event_send timeout race resumes thread twice")
        candidates = [
            make_issue(number, "rt_event_send timeout race resumes thread twice")
            for number in range(5, 11)
        ]
        pull_request = make_issue(4, "rt_event_send timeout race resumes thread twice")
        pull_request["pull_request"] = {}
        ranked = similar_issues.rank_candidates(issue, candidates + [pull_request])
        self.assertEqual(len(ranked), 3)
        self.assertNotIn(10, [item["candidate"]["number"] for item in ranked])


class SuggestionTests(unittest.TestCase):
    def test_marker_makes_comment_idempotent(self):
        issue = make_issue(10, "rt_event_send timeout race resumes thread twice")
        client = FakeClient(
            comments=[
                {
                    "body": similar_issues.COMMENT_MARKER,
                    "user": {"login": "github-actions[bot]", "type": "Bot"},
                }
            ]
        )
        self.assertEqual(
            similar_issues.suggest_for_issue(
                client, "RT-Thread/rt-thread", issue
            ),
            [],
        )
        self.assertFalse(any(call[0] == "search_issues" for call in client.calls))

    def test_user_cannot_spoof_the_idempotency_marker(self):
        issue = make_issue(10, "rt_event_send timeout race resumes thread twice")
        candidate = make_issue(9, "rt_event_send timeout race resumes thread twice")
        client = FakeClient(
            search_items=[candidate],
            comments=[
                {
                    "body": similar_issues.COMMENT_MARKER,
                    "user": {"login": "alice", "type": "User"},
                }
            ],
        )

        ranked = similar_issues.suggest_for_issue(
            client, "RT-Thread/rt-thread", issue
        )

        self.assertEqual(len(ranked), 1)
        self.assertTrue(any(call[0] == "create_comment" for call in client.calls))

    def test_rechecks_marker_before_creating_a_comment(self):
        issue = make_issue(10, "rt_event_send timeout race resumes thread twice")
        candidate = make_issue(9, "rt_event_send timeout race resumes thread twice")
        bot_marker = {
            "body": similar_issues.COMMENT_MARKER,
            "user": {"login": "github-actions[bot]", "type": "Bot"},
        }
        client = FakeClient(
            search_items=[candidate], comment_batches=[[], [bot_marker]]
        )

        ranked = similar_issues.suggest_for_issue(
            client, "RT-Thread/rt-thread", issue
        )

        self.assertEqual(ranked, [])
        comments = [call for call in client.calls if call[0] == "create_comment"]
        self.assertEqual(len(comments), 1)
        self.assertIn(similar_issues.CLAIM_HINT_MARKER, comments[0][3])

    def test_dry_run_does_not_create_comment(self):
        issue = make_issue(10, "rt_event_send timeout race resumes thread twice")
        candidate = make_issue(9, "rt_event_send timeout race resumes thread twice")
        client = FakeClient(search_items=[candidate])
        ranked = similar_issues.suggest_for_issue(
            client, "RT-Thread/rt-thread", issue, dry_run=True
        )
        self.assertEqual(len(ranked), 1)
        self.assertFalse(any(call[0] == "create_comment" for call in client.calls))

    def test_claim_hint_is_posted_when_no_matches(self):
        issue = make_issue(10, "rt_event_send timeout race resumes thread twice")
        client = FakeClient()

        ranked = similar_issues.suggest_for_issue(
            client, "RT-Thread/rt-thread", issue
        )

        self.assertEqual(ranked, [])
        comments = [call for call in client.calls if call[0] == "create_comment"]
        self.assertEqual(len(comments), 1)
        self.assertIn(similar_issues.CLAIM_HINT_MARKER, comments[0][3])
        self.assertIn("如需认领", comments[0][3])
        self.assertIn("`/claim`", comments[0][3])

    def test_claim_hint_is_separate_from_similar_issue_comment(self):
        issue = make_issue(10, "rt_event_send timeout race resumes thread twice")
        candidate = make_issue(9, "rt_event_send timeout race resumes thread twice")
        client = FakeClient(search_items=[candidate])

        ranked = similar_issues.suggest_for_issue(
            client, "RT-Thread/rt-thread", issue
        )

        self.assertEqual(len(ranked), 1)
        comments = [call[3] for call in client.calls if call[0] == "create_comment"]
        self.assertEqual(len(comments), 2)
        self.assertIn(similar_issues.CLAIM_HINT_MARKER, comments[0])
        self.assertNotIn(similar_issues.COMMENT_MARKER, comments[0])
        self.assertIn(similar_issues.COMMENT_MARKER, comments[1])
        self.assertNotIn(similar_issues.CLAIM_HINT_MARKER, comments[1])

    def test_rate_limit_is_best_effort(self):
        issue = make_issue(10, "rt_event_send timeout race resumes thread twice")
        client = FakeClient(
            search_error=similar_issues.GitHubAPIError(403, "rate limit exceeded")
        )
        self.assertEqual(
            similar_issues.suggest_for_issue(
                client, "RT-Thread/rt-thread", issue
            ),
            [],
        )

    def test_backfill_reports_rate_limits_as_failures(self):
        issue = make_issue(10, "rt_event_send timeout race resumes thread twice")
        client = FakeClient(
            open_issues=[issue],
            search_error=similar_issues.GitHubAPIError(403, "rate limit exceeded"),
        )

        summary = similar_issues.process_backfill(
            client,
            "RT-Thread/rt-thread",
            max_issues=1,
            delay_seconds=0,
            dry_run=True,
        )

        self.assertEqual(summary["processed"], 1)
        self.assertEqual(summary["failures"][0]["number"], 10)

    def test_backfill_does_not_add_claim_hint(self):
        issue = make_issue(10, "rt_event_send timeout race resumes thread twice")
        client = FakeClient(open_issues=[issue])

        summary = similar_issues.process_backfill(
            client,
            "RT-Thread/rt-thread",
            max_issues=1,
            delay_seconds=0,
            dry_run=False,
        )

        self.assertEqual(summary["processed"], 1)
        self.assertEqual(summary["suggested"], 0)
        self.assertFalse(any(call[0] == "create_comment" for call in client.calls))

    def test_comment_is_bilingual_and_cautious(self):
        ranked = [{"candidate": make_issue(9, "Example"), "score": 1.0}]
        comment = similar_issues.format_comment(ranked)
        self.assertIn(similar_issues.COMMENT_MARKER, comment)
        self.assertIn("#9", comment)
        self.assertIn("尚未确认重复", comment)
        self.assertIn("not confirmed duplicates", comment)


class ClientTests(unittest.TestCase):
    def test_comment_pagination_reads_past_five_hundred(self):
        class PagingClient(similar_issues.GitHubClient):
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


if __name__ == "__main__":
    unittest.main()
