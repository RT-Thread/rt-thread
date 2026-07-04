import importlib.util
import json
import os
import sys
import tempfile
import types
import unittest


RTT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))


class _FakeRFile:
    def __init__(self, abspath, name):
        self.abspath = abspath
        self.name = name


class _FakeNode:
    """Minimal stand-in for a SCons File node used by the group emitters."""

    def __init__(self, abspath):
        self._r = _FakeRFile(abspath, os.path.basename(abspath))

    def rfile(self):
        return self._r


def load_module_from_path(name, relative_path, stub_rtconfig=False):
    sys.path.insert(0, os.path.join(RTT_ROOT, "tools"))

    old_rtconfig = sys.modules.get("rtconfig")
    if stub_rtconfig:
        rtconfig = types.ModuleType("rtconfig")
        rtconfig.EXEC_PATH = ""
        rtconfig.CC = "gcc"
        rtconfig.CXX = "g++"
        rtconfig.AS = "gcc"
        rtconfig.AR = "ar"
        rtconfig.LINK = "gcc"
        rtconfig.TARGET_EXT = "elf"
        sys.modules["rtconfig"] = rtconfig

    try:
        path = os.path.join(RTT_ROOT, relative_path)
        spec = importlib.util.spec_from_file_location(name, path)
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        return module
    finally:
        if stub_rtconfig:
            if old_rtconfig is None:
                sys.modules.pop("rtconfig", None)
            else:
                sys.modules["rtconfig"] = old_rtconfig


class TargetSerializationTest(unittest.TestCase):

    def test_target_utils_normalizes_scons_defines(self):
        target_utils = load_module_from_path(
            "target_utils_under_test",
            os.path.join("tools", "targets", "target_utils.py"),
        )

        defines = target_utils.normalize_defines([
            "PLAIN",
            ("WITH_VALUE", "1"),
            "FROM_STRING=2",
            'QUOTED="a b"',
        ])

        self.assertEqual(
            defines,
            [
                "PLAIN",
                "WITH_VALUE=1",
                "FROM_STRING=2",
                'QUOTED="a b"',
            ],
        )

    def test_vsc_empty_compile_commands_does_not_crash(self):
        vsc = load_module_from_path(
            "vsc_under_test",
            os.path.join("tools", "targets", "vsc.py"),
            stub_rtconfig=True,
        )

        with tempfile.TemporaryDirectory() as temp_dir:
            root_path = os.path.join(temp_dir, "project")
            build_dir = os.path.join(root_path, "build")
            os.makedirs(build_dir)

            command_json_path = os.path.join(build_dir, "compile_commands.json")
            with open(command_json_path, "w", encoding="utf-8") as f:
                json.dump([], f)

            old_cwd = os.getcwd()
            os.chdir(temp_dir)
            try:
                vsc.command_json_to_workspace(root_path, command_json_path)
            finally:
                os.chdir(old_cwd)

    def test_vsc_extract_source_dirs_handles_quoted_include_paths(self):
        vsc = load_module_from_path(
            "vsc_under_test_quoted",
            os.path.join("tools", "targets", "vsc.py"),
            stub_rtconfig=True,
        )

        with tempfile.TemporaryDirectory() as temp_dir:
            source_dir = os.path.join(temp_dir, "src")
            include_dir = os.path.join(temp_dir, "dir with space", "inc")
            os.makedirs(source_dir)
            os.makedirs(include_dir)

            source_file = os.path.join(source_dir, "main.c")
            with open(source_file, "w", encoding="utf-8") as f:
                f.write("int main(void) { return 0; }\n")

            compile_commands = [
                {
                    "directory": temp_dir,
                    "file": source_file,
                    "command": f'gcc -I"{include_dir}" -c "{source_file}"',
                }
            ]

            dirs = vsc.extract_source_dirs(compile_commands)
            self.assertIn(os.path.abspath(include_dir), dirs)

    def _target_utils(self):
        return load_module_from_path(
            "target_utils_helpers",
            os.path.join("tools", "targets", "target_utils.py"),
        )

    def test_normalize_defines_supports_tuple_list_value_quoted(self):
        t = self._target_utils()
        self.assertEqual(t.normalize_define("FOO"), "FOO")
        self.assertEqual(t.normalize_define(("FOO", "1")), "FOO=1")
        self.assertEqual(t.normalize_define(["FOO", "1"]), "FOO=1")
        self.assertEqual(t.normalize_define(("FOO", None)), "FOO")
        self.assertEqual(t.normalize_define("FOO=bar"), "FOO=bar")
        self.assertEqual(t.normalize_define('FOO="a b"'), 'FOO="a b"')
        self.assertIsNone(t.normalize_define(None))
        self.assertEqual(
            t.normalize_defines(["A", ("B", "1"), ["C", "2"], "A", None, ("D", None)]),
            ["A", "B=1", "C=2", "D"],
        )

    def test_ordered_unique_preserves_order(self):
        t = self._target_utils()
        self.assertEqual(
            t.ordered_unique(["b", "a", "b", "c", "a", "d"]),
            ["b", "a", "c", "d"],
        )

    def test_cmake_quote_handles_space_semicolon_quote(self):
        t = self._target_utils()
        self.assertEqual(t.cmake_quote('a b'), 'a b')
        self.assertEqual(t.cmake_quote('a;b'), 'a\\;b')
        self.assertEqual(t.cmake_quote('a"b'), 'a\\"b')
        self.assertEqual(t.cmake_quote('a\\b'), 'a\\\\b')

    def test_make_quote_handles_space_hash_dollar_and_keeps_make_var(self):
        t = self._target_utils()
        self.assertEqual(t.make_quote('a b'), 'a\\ b')
        self.assertEqual(t.make_quote('a#b'), 'a\\#b')
        # a bare '$' is escaped, but a $(VAR)/${VAR} reference is preserved
        self.assertEqual(t.make_quote('a$b'), 'a$$b')
        self.assertEqual(t.make_quote('$(BSP_ROOT)/x'), '$(BSP_ROOT)/x')
        self.assertEqual(t.make_quote('${RTT_ROOT}/x'), '${RTT_ROOT}/x')

    def test_lua_quote_handles_quote_backslash(self):
        t = self._target_utils()
        self.assertEqual(t.lua_quote('a"b'), '"a\\"b"')
        self.assertEqual(t.lua_quote('a\\b'), '"a\\\\b"')

    def test_zig_quote_handles_quote_backslash(self):
        t = self._target_utils()
        self.assertEqual(t.zig_quote('a"b'), '"a\\"b"')
        self.assertEqual(t.zig_quote('a\\b'), '"a\\\\b"')

    def test_xml_attr_and_list_value(self):
        t = self._target_utils()
        # xml_attr is attribute-safe: escapes & < > and both quote chars
        self.assertEqual(t.xml_attr('a&b<c>"d"'), 'a&amp;b&lt;c&gt;&quot;d&quot;')
        # xml_list_value only concatenates (ElementTree escapes on write)
        self.assertEqual(t.xml_list_value(["A", "B=1", "C"]), "A;B=1;C")
        self.assertEqual(t.semicolon_list(["x", "y", "z"]), "x;y;z")

    def test_normalize_link_script_flags_forms(self):
        t = self._target_utils()
        self.assertEqual(
            t.normalize_link_script_flags('-Tlink.lds -nostartfiles'), ['link.lds'])
        self.assertEqual(
            t.normalize_link_script_flags('-T link.lds'), ['link.lds'])
        self.assertEqual(
            t.normalize_link_script_flags('-T "dir with space/link.lds"'),
            ['dir with space/link.lds'])
        self.assertEqual(
            t.normalize_link_script_flags('-Wl,-T,build/link.lds'),
            ['build/link.lds'])
        self.assertEqual(t.normalize_link_script_flags(''), [])

    def test_xml_attr_and_path_attr_escape_special_chars(self):
        t = self._target_utils()
        # xml_attr now escapes the quote characters too (attribute-safe)
        self.assertEqual(t.xml_attr('a&b<c>"d"\'e'),
                         'a&amp;b&lt;c&gt;&quot;d&quot;&apos;e')
        # xml_path_attr normalizes separators then escapes
        self.assertEqual(t.xml_path_attr('a\\b/c&d'), 'a/b/c&amp;d')
        self.assertEqual(t.xml_path_attr('dir with space/x"y'),
                         'dir with space/x&quot;y')
        # backslash convention keeps '\\' as separator
        self.assertEqual(t.xml_path_attr('a/b', sep='\\'), 'a\\b')

    def test_normalize_group_file_path_is_stable_and_relative(self):
        t = self._target_utils()
        with tempfile.TemporaryDirectory() as temp_dir:
            project = os.path.join(temp_dir, "proj")
            src_dir = os.path.join(project, "sub dir", "drivers")
            os.makedirs(src_dir)

            rel = t.normalize_group_file_path(project, src_dir, "main.c")
            # relative, single '/' separator, no backslashes, no drive/abs prefix
            self.assertEqual(rel, "sub dir/drivers/main.c")
            self.assertNotIn("\\", rel)
            self.assertFalse(os.path.isabs(rel))

            # backslash convention for IAR's $PROJ_DIR$ paths
            rel_bs = t.normalize_group_file_path(project, src_dir, "main.c", sep="\\")
            self.assertEqual(rel_bs, "sub dir\\drivers\\main.c")
            self.assertNotIn("/", rel_bs)

    def test_elementtree_escapes_group_attr_round_trip(self):
        import xml.etree.ElementTree as etree
        t = self._target_utils()
        # the file-group emitters rely on ElementTree escaping the raw path we
        # assign; verify a path with XML-special chars round-trips intact
        raw = t.normalize_group_file_path("/proj", "/proj/a&b/<c>", 'x".c')
        root = etree.Element("File")
        root.set("RelativePath", raw)
        serialized = etree.tostring(root, encoding="unicode")
        self.assertIn("&amp;", serialized)
        parsed = etree.fromstring(serialized)
        self.assertEqual(parsed.get("RelativePath"), raw)

    def test_group_define_serialization_keeps_foo_1(self):
        t = self._target_utils()
        # Keil/IAR join defines; VS/VS2012 use semicolon list -- all must keep
        # the tuple ('FOO','1') as FOO=1, never split into FOO and 1
        normalized = t.normalize_defines(["A", ("FOO", "1"), ("BAR", None)])
        self.assertEqual(normalized, ["A", "FOO=1", "BAR"])
        self.assertEqual(t.semicolon_list(normalized), "A;FOO=1;BAR")
        self.assertEqual(", ".join(normalized), "A, FOO=1, BAR")
        self.assertNotIn(";1", t.semicolon_list(normalized))

    def test_escape_quoted_flags_normalizes_backslash_and_quote(self):
        t = self._target_utils()
        # backslash -> '/', embedded quote escaped so the "..." literal is safe
        self.assertEqual(
            t.escape_quoted_flags('-Ic:\\a\\b -DNAME=\"x\"'),
            '-Ic:/a/b -DNAME=\\"x\\"',
        )
        self.assertEqual(t.escape_quoted_flags('-O2 -g'), '-O2 -g')

    def test_normalize_flags_tokenizes_and_dedupes(self):
        t = self._target_utils()
        self.assertEqual(
            t.normalize_flags('-O2 -g -O2 "-DA=1"'),
            ['-O2', '-g', '-DA=1'],
        )
        self.assertIn('-nostartfiles', t.normalize_flags('-T link.lds -nostartfiles'))

    def test_split_command_and_extract_include_args(self):
        t = self._target_utils()
        # string command with a quoted include path containing a space
        parts = t.split_command('gcc -I"/dir with space/inc" -c "/x/main.c"')
        self.assertEqual(t.extract_include_args(parts), ['/dir with space/inc'])
        # arguments list with the split "-I", "path" form
        args = ["gcc", "-I", "/a/inc", "-Ib/inc", "/Ic/inc", "-c", "main.c"]
        self.assertEqual(
            t.extract_include_args(t.split_command(args)),
            ['/a/inc', 'b/inc', 'c/inc'],
        )

    def test_tuple_define_serializes_as_foo_1_across_generators(self):
        t = self._target_utils()
        defines = ["PLAIN", ("STM32", "1"), ("EMPTY", None)]
        normalized = t.normalize_defines(defines)
        self.assertEqual(normalized, ["PLAIN", "STM32=1", "EMPTY"])
        # cmake: -D<name> list, no bare "1"
        cmake_text = t.cmake_list(["-D" + d for d in normalized])
        self.assertIn("-DSTM32=1", cmake_text)
        self.assertNotIn("-D1", cmake_text)
        # xmake (lua) and zig list quote each define, tuple folded to FOO=1
        self.assertIn('"STM32=1"', t.lua_list(normalized))
        self.assertIn('"STM32=1"', t.zig_list(normalized))
        # vs / keil semicolon or comma joined XML value
        self.assertEqual(t.xml_list_value(normalized), "PLAIN;STM32=1;EMPTY")
        self.assertNotIn(";1;", t.xml_list_value(normalized))

    def test_codeblocks_define_and_python3_xml(self):
        import xml.etree.ElementTree as etree

        codeblocks = load_module_from_path(
            "codeblocks_under_test",
            os.path.join("tools", "targets", "codeblocks.py"),
            stub_rtconfig=True,
        )
        import building
        import utils

        with tempfile.TemporaryDirectory() as temp_dir:
            src_dir = os.path.join(temp_dir, "app dir")
            os.makedirs(src_dir)
            src_file = os.path.join(src_dir, "main.c")
            with open(src_file, "w", encoding="utf-8") as f:
                f.write("int main(void){return 0;}\n")

            template = os.path.join(temp_dir, "template.cbp")
            with open(template, "w", encoding="utf-8") as f:
                f.write("<CodeBlocks_project_file><Project>"
                        "<Compiler /></Project></CodeBlocks_project_file>")

            target = os.path.join(temp_dir, "project.cbp")
            script = [{"name": "Applications", "src": [_FakeNode(src_file)]}]

            building.Env = {
                "CPPPATH": [os.path.join(temp_dir, "inc dir")],
                "CPPDEFINES": ["RT_USING_FINSH", ("STM32", "1")],
            }
            utils.source_list = []

            old_cwd = os.getcwd()
            os.chdir(temp_dir)
            try:
                # must not raise AttributeError (str.decode) or TypeError (bytes write)
                codeblocks.CBProject(target, script, [])
            finally:
                os.chdir(old_cwd)

            # output must be valid XML
            tree = etree.parse(target)
            options = [a.get("option") for a in tree.iter("Add") if a.get("option")]
            self.assertIn("-DRT_USING_FINSH", options)
            self.assertIn("-DSTM32=1", options)     # tuple folded, name kept
            self.assertNotIn("-DH", options)         # not char-by-char truncated
            self.assertNotIn("-D1", options)         # tuple name not dropped

            # file path uses forward slashes, no mixed separators
            filenames = [u.get("filename") for u in tree.iter("Unit")]
            self.assertTrue(any("app dir/main.c" in fn for fn in filenames))
            self.assertFalse(any("\\" in fn for fn in filenames))

    def test_cdk_tuple_define_serialization(self):
        import xml.etree.ElementTree as etree

        cdk = load_module_from_path(
            "cdk_under_test",
            os.path.join("tools", "targets", "cdk.py"),
        )

        template_xml = (
            "<Project><BuildConfigs><BuildConfig>"
            "<Compiler><IncludePath /><Define /><OtherFlags /></Compiler>"
            "<Asm><IncludePath /><Define /></Asm>"
            "<Linker><OtherFlags /><LibName /></Linker>"
            "</BuildConfig></BuildConfigs></Project>"
        )
        tree = etree.ElementTree(etree.fromstring(template_xml))

        script = [{
            "name": "kernel",
            "src": [],
            "CPPPATH": [],
            "CPPDEFINES": ["A", ("FOO", "1"), "A"],
            "CCFLAGS": "",
            "LINKFLAGS": "",
        }]

        with tempfile.TemporaryDirectory() as temp_dir:
            target = os.path.join(temp_dir, "project.cdkproj")
            # must not raise TypeError on the ('FOO','1') tuple
            cdk._CDKProject(tree, target, script)

            parsed = etree.parse(target)
            define = parsed.find("BuildConfigs/BuildConfig/Compiler/Define").text
            self.assertEqual(define, "A; FOO=1")   # folded + order-preserving de-dup
            self.assertNotIn(";1;", define)

    def test_esp_idf_cmake_paths_are_quoted(self):
        esp_idf = load_module_from_path(
            "esp_idf_under_test",
            os.path.join("tools", "targets", "esp_idf.py"),
            stub_rtconfig=True,
        )

        with tempfile.TemporaryDirectory() as temp_dir:
            src_dir = os.path.join(temp_dir, "src space")
            os.makedirs(src_dir)
            src_file = os.path.join(src_dir, "main.c")
            with open(src_file, "w", encoding="utf-8") as f:
                f.write("/* no init export */\n")

            inc_dir = os.path.join(temp_dir, "inc space")
            esp_idf.utils.ProjectInfo = lambda env: {"CPPPATH": [inc_dir]}

            project = [{"name": "app", "src": [_FakeNode(src_file)]}]

            os.makedirs(os.path.join(temp_dir, "main"))
            old_cwd = os.getcwd()
            os.chdir(temp_dir)
            try:
                esp_idf.GenerateCFiles({}, project)
                with open(os.path.join(temp_dir, "main", "CMakeLists.txt"),
                          encoding="utf-8") as f:
                    content = f.read()
            finally:
                os.chdir(old_cwd)

            # the space-containing paths must be a single quoted CMake list item
            self.assertIn('"', content)
            self.assertRegex(content, r'"[^"\n]*src space/main\.c"')
            self.assertRegex(content, r'"[^"\n]*inc space"')

    def test_ses_project_generation_works_on_python3(self):
        ses = load_module_from_path(
            "ses_under_test",
            os.path.join("tools", "targets", "ses.py"),
        )

        ses.ProjectInfo = lambda env: {
            "CPPPATH": [],
            "CPPDEFINES": [],
        }

        class FakeEnv(dict):
            pass

        with tempfile.TemporaryDirectory() as temp_dir:
            old_cwd = os.getcwd()
            os.chdir(temp_dir)
            try:
                with open("template.emProject", "w", encoding="utf-8") as f:
                    f.write("<solution><project><configuration /></project></solution>")

                env = FakeEnv()
                env["BSP_ROOT"] = temp_dir
                env["project"] = []

                ses.SESProject(env)

                self.assertTrue(os.path.exists("project.emProject"))
            finally:
                os.chdir(old_cwd)


if __name__ == "__main__":
    unittest.main()
