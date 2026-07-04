import contextlib
import importlib.util
import os
import shutil
import subprocess
import sys
import tempfile
import types
import unittest
from io import StringIO


RTT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))


def load_attachconfig_module():
    scons_mod = types.ModuleType("SCons")
    script_mod = types.ModuleType("SCons.Script")
    script_mod.GetOption = lambda name: None

    old_scons = sys.modules.get("SCons")
    old_script = sys.modules.get("SCons.Script")
    sys.modules["SCons"] = scons_mod
    sys.modules["SCons.Script"] = script_mod

    try:
        path = os.path.join(RTT_ROOT, "tools", "attachconfig.py")
        spec = importlib.util.spec_from_file_location("attachconfig_under_test", path)
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        return module
    finally:
        if old_scons is None:
            sys.modules.pop("SCons", None)
        else:
            sys.modules["SCons"] = old_scons
        if old_script is None:
            sys.modules.pop("SCons.Script", None)
        else:
            sys.modules["SCons.Script"] = old_script


class AttachConfigRobustnessTest(unittest.TestCase):

    def test_attach_query_handles_empty_attachconfig_list(self):
        module = load_attachconfig_module()
        module.GetOption = lambda name: "?" if name == "attach" else None
        module.GetAttachConfig = lambda action, attachconfig, result: None

        output = StringIO()
        with contextlib.redirect_stdout(output):
            module.GenAttachConfigProject()

        self.assertIn("AttachConfig", output.getvalue())

    def test_bsp_buildings_reports_missing_srtt_bsp_without_traceback(self):
        env = os.environ.copy()
        env.pop("SRTT_BSP", None)

        result = subprocess.run(
            [sys.executable, os.path.join("tools", "ci", "bsp_buildings.py")],
            cwd=RTT_ROOT,
            env=env,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )

        combined_output = result.stdout + result.stderr
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("SRTT_BSP", combined_output)
        self.assertNotIn("Traceback", combined_output)
    def test_bsp_board_info_allows_missing_optional_commands(self):
        bsp_name = "tmp_attachconfig_board_info_test"
        bsp_dir = os.path.join(RTT_ROOT, "bsp", bsp_name)
        attach_dir = os.path.join(bsp_dir, ".ci", "attachconfig")

        shutil.rmtree(bsp_dir, ignore_errors=True)
        os.makedirs(attach_dir, exist_ok=True)

        try:
            config_file = os.path.join(bsp_dir, ".config")
            backup_file = config_file + ".origin"
            with open(config_file, "w", encoding="utf-8") as f:
                f.write("CONFIG_BASE=y\n")

            with open(os.path.join(attach_dir, "board_attachconfig.yml"), "w", encoding="utf-8") as f:
                f.write(
                    "bsp_board_info:\n"
                    "  run_cmd: \"echo run\"\n"
                    "board_project:\n"
                    "  kconfig:\n"
                    "    - CONFIG_BOARD_PROJECT=y\n"
                )

            env = os.environ.copy()
            env["SRTT_BSP"] = bsp_name

            result = subprocess.run(
                [sys.executable, os.path.join("tools", "ci", "bsp_buildings.py")],
                cwd=RTT_ROOT,
                env=env,
                text=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
            )

            combined_output = result.stdout + result.stderr
            self.assertNotIn("AttributeError", combined_output)
            self.assertNotIn("Traceback", combined_output)
            self.assertFalse(os.path.exists(backup_file))
        finally:
            shutil.rmtree(bsp_dir, ignore_errors=True)
    def test_attachconfig_without_kconfig_does_not_leave_backup(self):
        bsp_name = "tmp_attachconfig_test"
        bsp_dir = os.path.join(RTT_ROOT, "bsp", bsp_name)
        attach_dir = os.path.join(bsp_dir, ".ci", "attachconfig")

        shutil.rmtree(bsp_dir, ignore_errors=True)
        os.makedirs(attach_dir, exist_ok=True)

        try:
            config_file = os.path.join(bsp_dir, ".config")
            backup_file = config_file + ".origin"
            with open(config_file, "w", encoding="utf-8") as f:
                f.write("CONFIG_BASE=y\n")

            with open(os.path.join(attach_dir, "bad_attachconfig.yml"), "w", encoding="utf-8") as f:
                f.write(
                    "no_kconfig_project:\n"
                    "  pre_build: \"echo pre\"\n"
                    "  build_cmd: \"echo build\"\n"
                    "  post_build: \"echo post\"\n"
                )

            env = os.environ.copy()
            env["SRTT_BSP"] = bsp_name

            subprocess.run(
                [sys.executable, os.path.join("tools", "ci", "bsp_buildings.py")],
                cwd=RTT_ROOT,
                env=env,
                text=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
            )

            self.assertFalse(os.path.exists(backup_file))
            with open(config_file, "r", encoding="utf-8") as f:
                self.assertEqual(f.read(), "CONFIG_BASE=y\n")
        finally:
            shutil.rmtree(bsp_dir, ignore_errors=True)


if __name__ == "__main__":
    unittest.main()
