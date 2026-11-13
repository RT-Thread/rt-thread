import importlib.util
import os
import shutil
import sys
import tempfile
import types
import unittest
import xml.etree.ElementTree as etree
from pathlib import Path
from unittest import mock


ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))


def load_target(name):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'tools' / 'targets' / (name + '.py'))
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


class IDETargetTests(unittest.TestCase):
    def test_keil_targets_preserve_include_order(self):
        keil = load_target('keil')
        target_xml = '''<Target><TargetOption><TargetArmAds>
            <Cads><uC99>0</uC99><uGnu>0</uGnu><VariousControls>
            <IncludePath/><Define/></VariousControls></Cads>
            <LDads><Misc/></LDads></TargetArmAds></TargetOption><Groups/>
            </Target>'''
        tree = etree.ElementTree(etree.fromstring('<Project><Targets>' + target_xml * 2 + '</Targets></Project>'))
        with tempfile.TemporaryDirectory() as temp:
            includes = [os.path.join(temp, 'first'), os.path.join(temp, 'second')]
            source = types.SimpleNamespace(name='main.c', abspath=os.path.join(temp, 'main.c'))
            node = types.SimpleNamespace(rfile=lambda: source)
            group = {'name': 'test', 'src': [node], 'CPPPATH': [includes[1], includes[0]],
                     'LINKFLAGS': '--keep=x', 'CFLAGS': '-std=c99 -gnu'}
            keil.MDK45Project({'CPPPATH': includes, 'CPPDEFINES': ['TEST']},
                              tree, os.path.join(temp, 'project.uvprojx'), [group])
            targets = tree.findall('Targets/Target')
            for target in targets:
                options = target.find('TargetOption/TargetArmAds')
                self.assertEqual(options.findtext('Cads/VariousControls/IncludePath'), 'first;second')
                self.assertEqual(options.findtext('Cads/VariousControls/Define'), 'TEST')
                self.assertEqual(options.findtext('Cads/uC99'), '1')
                self.assertEqual(options.findtext('Cads/uGnu'), '1')
                self.assertEqual(options.findtext('LDads/Misc'), '--keep=x')
                self.assertEqual(target.findtext('Groups/Group/GroupName'), 'test')
                self.assertEqual(target.findtext('Groups/Group/Files/File/FileName'), 'main.c')

    def test_iar_linker_symbols_and_other_options(self):
        iar = load_target('iar')
        template = ROOT / 'bsp' / 'nxp' / 'imx' / 'imxrt' / 'imxrt1180-nxp-evk' / 'cm33' / 'template.ewp'
        with tempfile.TemporaryDirectory() as temp:
            shutil.copyfile(template, os.path.join(temp, 'template.ewp'))
            template_tree = etree.parse(os.path.join(temp, 'template.ewp'))
            for option in template_tree.findall('configuration/settings/data/option'):
                if option.findtext('name') == 'IlinkExtraOptions':
                    option.find('state').text = '--existing'
            template_tree.write(os.path.join(temp, 'template.ewp'), encoding='utf-8')
            previous = os.getcwd()
            try:
                os.chdir(temp)
                groups = [
                    {'name': 'one', 'src': [], 'LINKFLAGS': '--keep=Reset_Handler --config_def APP_OFFSET=0x1000'},
                    {'name': 'two', 'src': [], 'LINKFLAGS': '--config_def=MODE=2 --entry "my entry"'},
                ]
                with mock.patch.dict(sys.modules, {'rtconfig': types.ModuleType('rtconfig')}):
                    iar.IARProject({}, 'project.ewp', groups)
            finally:
                os.chdir(previous)
            tree = etree.parse(os.path.join(temp, 'project.ewp'))
            for config in tree.findall('configuration'):
                options = {o.findtext('name'): o for o in config.findall('settings/data/option')}
                defines = [s.text for s in options['IlinkConfigDefines'].findall('state') if s.text]
                self.assertEqual(defines, ['APP_OFFSET=0x1000', 'MODE=2'])
                self.assertEqual(options['IlinkUseExtraOptions'].findtext('state'), '1')
                self.assertEqual(options['IlinkExtraOptions'].findtext('state'),
                                 '--existing --keep=Reset_Handler --entry "my entry"')

    def test_iar_invalid_or_quoted_linker_flags(self):
        iar = load_target('iar')
        defines, extra = iar._split_iar_linkflags(
            '--keep=Reset_Handler --config_def "NAME=2" --log "C:\\Program Files\\log.txt"')
        self.assertEqual(defines, ['NAME=2'])
        self.assertEqual(extra, '--keep=Reset_Handler --log "C:\\Program Files\\log.txt"')
        for flags in ['--config_def', '--config_def --keep=Reset_Handler', '--log "broken']:
            with self.subTest(flags=flags), self.assertRaises(ValueError):
                iar._split_iar_linkflags(flags)

    def test_iar_wsdt_repeated_utf8_updates(self):
        iar = load_target('iar')
        with tempfile.TemporaryDirectory() as temp:
            wsdt = os.path.join(temp, 'settings', 'project.wsdt')
            for config in ['ram', 'nor', 'hyperram']:
                iar._update_iar_wsdt(wsdt, 'project & test', config)
                self.assertIn(b"encoding='utf-8'", Path(wsdt).read_bytes())
                tree = etree.parse(wsdt)
                self.assertEqual(tree.findtext('ConfigDictionary/CurrentConfigs/Project'), 'project & test/' + config)


if __name__ == '__main__':
    unittest.main()
