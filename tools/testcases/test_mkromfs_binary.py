import struct
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path


class MkromfsBinaryTest(unittest.TestCase):
    def test_utf8_names_align_directory_entries_and_file_data(self):
        script = Path(__file__).resolve().parents[1] / 'mkromfs.py'
        base = 0x1000
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp) / 'root'
            directory = root / '中a'
            directory.mkdir(parents=True)
            (directory / '文').write_bytes(b'abc')
            output = Path(tmp) / 'romfs.bin'
            subprocess.run([sys.executable, str(script), '--binary', '--addr',
                            hex(base), str(root), str(output)], check=True)
            image = output.read_bytes()

        dirent = struct.Struct('=4I')
        _, _, root_data, _ = dirent.unpack_from(image)
        _, dir_name, dir_data, _ = dirent.unpack_from(image, root_data - base)
        self.assertEqual(dir_data % 4, 0)
        self.assertEqual(image[dir_name - base:dir_data - base],
                         '中a'.encode('utf-8') + b'\0' * 4)

        _, file_name, file_data, size = dirent.unpack_from(image, dir_data - base)
        self.assertEqual(file_data % 4, 0)
        self.assertEqual(image[file_name - base:file_data - base],
                         '文'.encode('utf-8') + b'\0')
        self.assertEqual(image[file_data - base:file_data - base + size], b'abc')


if __name__ == '__main__':
    unittest.main()
