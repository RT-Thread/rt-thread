# -*- coding: utf-8 -*-
import os
import getopt
import sys
import codecs
# hash需要调用的库
import hashlib, binascii
# AES-GCM需要调用的库
from Crypto.Cipher import AES
import struct
# RSA-2048需要调用的库
from Crypto.PublicKey import RSA
from Crypto.Signature import pkcs1_15
from Crypto.Hash import SHA256
from Crypto.Cipher import PKCS1_OAEP
from base64 import b64encode
# gmssl实现了国密sm4、sm3、sm2
from gmssl.sm4 import CryptSM4, SM4_ENCRYPT, SM4_DECRYPT
from gmssl import sm2, func
from gmssl import sm3


"""
AES的相关参数
"""
INITIAL_AES_IV = b'\x9f\xf1\x85\x63\xb9\x78\xec\x28\x1b\x3f\x27\x94'
INITIAL_AES_KEY = b'\x24\x50\x1a\xd3\x84\xe4\x73\x96\x3d\x47\x6e\xdc\xfe\x08\x20\x52\x37\xac\xfd\x49\xb5\xb8\xf3\x38\x57\xf8\x11\x4e\x86\x3f\xec\x7f'
ADD_AUTH_DATA = b''
"""
rsa2048的相关参数
"""
RSA_KEYSIZE = 2048
N = b'\xce\xa8\x04\x75\x32\x4c\x1d\xc8\x34\x78\x27\x81\x8d\xa5\x8b\xac\x06\x9d\x34\x19\xc6\x14\xa6\xea\x1a\xc6\xa3\xb5\x10\xdc\xd7\x2c\xc5\x16\x95\x49\x05\xe9\xfe\xf9\x08\xd4\x5e\x13\x00\x6a\xdf\x27\xd4\x67\xa7\xd8\x3c\x11\x1d\x1a\x5d\xf1\x5e\xf2\x93\x77\x1a\xef\xb9\x20\x03\x2a\x5b\xb9\x89\xf8\xe4\xf5\xe1\xb0\x50\x93\xd3\xf1\x30\xf9\x84\xc0\x7a\x77\x2a\x36\x83\xf4\xdc\x6f\xb2\x8a\x96\x81\x5b\x32\x12\x3c\xcd\xd1\x39\x54\xf1\x9d\x5b\x8b\x24\xa1\x03\xe7\x71\xa3\x4c\x32\x87\x55\xc6\x5e\xd6\x4e\x19\x24\xff\xd0\x4d\x30\xb2\x14\x2c\xc2\x62\xf6\xe0\x04\x8f\xef\x6d\xbc\x65\x2f\x21\x47\x9e\xa1\xc4\xb1\xd6\x6d\x28\xf4\xd4\x6e\xf7\x18\x5e\x39\x0c\xbf\xa2\xe0\x23\x80\x58\x2f\x31\x88\xbb\x94\xeb\xbf\x05\xd3\x14\x87\xa0\x9a\xff\x01\xfc\xbb\x4c\xd4\xbf\xd1\xf0\xa8\x33\xb3\x8c\x11\x81\x3c\x84\x36\x0b\xb5\x3c\x7d\x44\x81\x03\x1c\x40\xba\xd8\x71\x3b\xb6\xb8\x35\xcb\x08\x09\x8e\xd1\x5b\xa3\x1e\xe4\xba\x72\x8a\x8c\x8e\x10\xf7\x29\x4e\x1b\x41\x63\xb7\xae\xe5\x72\x77\xbf\xd8\x81\xa6\xf9\xd4\x3e\x02\xc6\x92\x5a\xa3\xa0\x43\xfb\x7f\xb7\x8d'
E = '0x260445'
D = b'\x09\x97\x63\x4c\x47\x7c\x1a\x03\x9d\x44\xc8\x10\xb2\xaa\xa3\xc7\x86\x2b\x0b\x88\xd3\x70\x82\x72\xe1\xe1\x5f\x66\xfc\x93\x89\x70\x9f\x8a\x11\xf3\xea\x6a\x5a\xf7\xef\xfa\x2d\x01\xc1\x89\xc5\x0f\x0d\x5b\xcb\xe3\xfa\x27\x2e\x56\xcf\xc4\xa4\xe1\xd3\x88\xa9\xdc\xd6\x5d\xf8\x62\x89\x02\x55\x6c\x8b\x6b\xb6\xa6\x41\x70\x9b\x5a\x35\xdd\x26\x22\xc7\x3d\x46\x40\xbf\xa1\x35\x9d\x0e\x76\xe1\xf2\x19\xf8\xe3\x3e\xb9\xbd\x0b\x59\xec\x19\x8e\xb2\xfc\xca\xae\x03\x46\xbd\x8b\x40\x1e\x12\xe3\xc6\x7c\xb6\x29\x56\x9c\x18\x5a\x2e\x0f\x35\xa2\xf7\x41\x64\x4c\x1c\xca\x5e\xbb\x13\x9d\x77\xa8\x9a\x29\x53\xfc\x5e\x30\x04\x8c\x0e\x61\x9f\x07\xc8\xd2\x1d\x1e\x56\xb8\xaf\x07\x19\x3d\x0f\xdf\x3f\x49\xcd\x49\xf2\xef\x31\x38\xb5\x13\x88\x62\xf1\x47\x0b\xd2\xd1\x6e\x34\xa2\xb9\xe7\x77\x7a\x6c\x8c\x8d\x4c\xb9\x4b\x4e\x8b\x5d\x61\x6c\xd5\x39\x37\x53\xe7\xb0\xf3\x1c\xc7\xda\x55\x9b\xa8\xe9\x8d\x88\x89\x14\xe3\x34\x77\x3b\xaf\x49\x8a\xd8\x8d\x96\x31\xeb\x5f\xe3\x2e\x53\xa4\x14\x5b\xf0\xba\x54\x8b\xf2\xb0\xa5\x0c\x63\xf6\x7b\x14\xe3\x98\xa3\x4b\x0d'

"""
sm4的相关参数
SM4_KEY = b'CanaanK230sm4key'   # 16 bytes, SM4-128
SM4_IV = b'\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f'    # 16 bytes
"""
SM4_KEY = b'\x01\x23\x45\x67\x89\xab\xcd\xef\xfe\xdc\xba\x98\x76\x54\x32\x10'
SM4_IV = b'\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f'    # 16 bytes
"""
sm2的相关参数
"""
private_key = b'\x39\x45\x20\x8f\x7b\x21\x44\xb1\x3f\x36\xe3\x8a\xc6\xd3\x9f\x95\x88\x93\x93\x69\x28\x60\xb5\x1a\x42\xfb\x81\xef\x4d\xf7\xc5\xb8'
public_key_x = b'\x09\xf9\xdf\x31\x1e\x54\x21\xa1\x50\xdd\x7d\x16\x1e\x4b\xc5\xc6\x72\x17\x9f\xad\x18\x33\xfc\x07\x6b\xb0\x8f\xf3\x56\xf3\x50\x20'
public_key_y = b'\xcc\xea\x49\x0c\xe2\x67\x75\xa5\x2d\xc6\xea\x71\x8c\xc1\xaa\x60\x0a\xed\x05\xfb\xf3\x5e\x08\x4a\x66\x32\xf6\x07\x2d\xa9\xad\x13'
public_key = public_key_x + public_key_y
K = b'\x59\x27\x6e\x27\xd5\x06\x86\x1a\x16\x68\x0f\x3a\xd9\xc0\x2d\xcc\xef\x3c\xc1\xfa\x3c\xdb\xe4\xce\x6d\x54\xb8\x0d\xea\xc1\xbc\x21'
ID = b'1234567812345678'
_private_key = codecs.encode(private_key, 'hex').decode('ascii')
_public_key = codecs.encode(public_key, 'hex').decode('ascii')
_ID = codecs.encode(ID, 'hex').decode('ascii')

def zeros(count):
    return b'\00' * count

# AES-GCM加密算法
class AES_ALG:
    """
    aes-gcm-256
    加密结果是”固件密文+tag“
    """
    def __init__(self):
        self.key = INITIAL_AES_KEY
        self.mode = AES.MODE_GCM
        self.iv = INITIAL_AES_IV
        self.add = ADD_AUTH_DATA
        self.cipher = AES.new(self.key, self.mode, self.iv)

    def aes_gcm_encrypt(self, input_data):
        cipher = self.cipher
        cipher.update(self.add)
        ciphertext, tag = cipher.encrypt_and_digest(input_data)
        #print('aes-gcm ciphertext: ', ciphertext, '\ntag: ', tag)
        return ciphertext, tag

    def aes_gcm_decrypt(self, encrypted_data):
        (ct, tg) = encrypted_data
        cipher = self.cipher
        cipher.update(self.add)
        plaintext = cipher.decrypt_and_verify(ct, tg)
        print('plaintext: ', plaintext)
        return plaintext


# SM4加密算法
class SM4_ALG:
    """
    调用python库：gmssl
    SM4-CBC encryption & decryption
    SM4-CBC采用了PKCS7填充算法，该算法会在加密明文的后面添加1-16字节的填充数据，当明文的长度是16的倍数时，填充最大，为16个字节。
    在存储密文的时候，为了跟puf保持一致，脚本对加密结果中的填充值去掉了，填充值的长度应该等于”加密结果 - 明文长度“
    """
    def __init__(self):
        self.crypt_sm4 = CryptSM4()
        self.sm4_key = SM4_KEY
        self.sm4_iv = SM4_IV

    def encrypt(self, value):
        crypt_sm4 = self.crypt_sm4
        encrypt_key = self.sm4_key
        encrypt_iv = self.sm4_iv
        crypt_sm4.set_key(encrypt_key, SM4_ENCRYPT)
        encrypt_value = crypt_sm4.crypt_cbc(encrypt_iv, value)
        #print('encryption: ', binascii.hexlify(encrypt_value))
        return encrypt_value

    def decrypt(self, value):
        crypt_sm4 = self.crypt_sm4
        decrypt_key = self.sm4_key
        decrypt_iv = self.sm4_iv
        crypt_sm4.set_key(decrypt_key, SM4_DECRYPT)
        decrypt_value = crypt_sm4.crypt_cbc(decrypt_iv, value)
        return decrypt_value


class RSA_ALG:
    """
    RSA-2048签名算法
    SHA256
    PKCS1_v1_5
    脚本对GCM生成的tag值做了一次签名运算
    """
    def __init__(self):
        self.size = RSA_KEYSIZE
        self.key = RSA.generate(self.size)

    def create_keypair(self):
        key = self.key
        print('\nthe modulus is: ', key.n, '\nthe exponent is: ', key.e)
        print("\nthe modulus's length is(bit): ", key.n.bit_length(), "\nthe exponent's length is(bit): ", key.e.bit_length())
        # 存储公钥
        public_key = key.publickey().export_key()
        with open('public.pem', 'wb') as fpub:
            fpub.write(public_key)
            fpub.close()
        # 存储私钥
        private_key = key.export_key()
        with open('private.pem', 'wb') as fpri:
            fpri.write(private_key)
            fpri.close()
        return key.n, key.e

    def rsa_sign(self, message, private_key):
        """
        fpri = open('private.pem', 'rb')
        private_key = RSA.import_key(fpri.read())
        """
        digest = SHA256.new(message)
        signature = pkcs1_15.new(private_key).sign(digest)
        print('signature: ')
        print(''.join(map(lambda x:('\\x' if len(hex(x))>=4 else '\\x0')+hex(x)[2:],signature)))
        return signature

    def rsa_verify(self, message, signature):
        fpub = open('public.pem', 'rb')
        public_key = RSA.import_key(fpub.read())
        digest = SHA256.new(message)
        try:
            pkcs1_15.new(public_key).verify(digest, signature)
            print('The signature is valid.')
        except (ValueError, TypeError):
            print('The signature is not valid.')

    def rsa_encrypt(self, message, public_key):
        encryptor = PKCS1_OAEP.new(public_key)
        encrypted = encryptor.encrypt(message)
        #print('Encrypted: ', encrypted, '\nlength: ', len(encrypted))
        #print('the rsa encryption: ', binascii.hexlify(encrypted))
        return encrypted

    def rsa_decrypt(self, message):
        fpri = open('private.pem', 'rb')
        private_key = RSA.import_key(fpri.read())
        decryptor = PKCS1_OAEP.new(private_key)
        decrypted = decryptor.decrypt(message)
        print('the rsa decryption: ', decrypted)


class SM2_ALG:
    """
    调用python库：gmssl
    gmssl在签名运算的过程中，直接对message进行签名；而根据官方文档，在计算sm2签名的过程中，应该首先计算message的Z值，然后根据Z值计算hash，
    最后再对message的hash值做签名运算。
    脚本根据gmssl-python项目实现了“Z值的计算”
    """
    def __init__(self):
        _K = codecs.encode(K, 'hex').decode('ascii')
        self._K = _K

    def sm2_sign(self, message):
        _K = self._K
        sm2_crypt = sm2.CryptSM2(public_key=_public_key, private_key=_private_key)
        # 计算Z值
        z = '0080' + _ID + sm2_crypt.ecc_table['a'] + sm2_crypt.ecc_table['b'] + sm2_crypt.ecc_table[
            'g'] + sm2_crypt.public_key
        z = binascii.a2b_hex(z)
        Za = sm3.sm3_hash(func.bytes_to_list(z))
        M_ = (Za + message.hex()).encode('utf-8')
        e = sm3.sm3_hash(func.bytes_to_list(binascii.a2b_hex(M_)))
        sign_data = binascii.a2b_hex(e.encode('utf-8'))
        if _K is None:
            _K = func.random_hex(sm2_crypt.para_len)
        sign = sm2_crypt.sign(sign_data, _K)  # 16进制
        r = sign[0:sm2_crypt.para_len]
        s = sign[sm2_crypt.para_len:]
        return sign, r, s

    def sm2_verify(self, message, signature):
        sm2_crypt = sm2.CryptSM2(public_key=_public_key, private_key=_private_key)
        # 计算Z值
        z = '0080' + _ID + sm2_crypt.ecc_table['a'] + sm2_crypt.ecc_table['b'] + sm2_crypt.ecc_table[
            'g'] + sm2_crypt.public_key
        z = binascii.a2b_hex(z)
        Za = sm3.sm3_hash(func.bytes_to_list(z))
        M_ = (Za + message.hex()).encode('utf-8')
        e = sm3.sm3_hash(func.bytes_to_list(binascii.a2b_hex(M_)))
        sign_data = binascii.a2b_hex(e.encode('utf-8'))
        verify = sm2_crypt.verify(signature, sign_data)
        print(verify)


# rsa签名对应的固件头格式
def rsa_format(patch_otp, modulus, exponent, signed_data):
    """
    根据bootrom的固件头，生成rsa的固件头格式
    :param patch_otp: 生成的新固件
    :param modulus: rsa的n值
    :param exponent: rsa的e值
    :param signed_data: rsa的签名
    :return: 无
    """
    modulus_hex = '{:x}'.format(modulus)  # int convert hex
    modulus_byte = bytes.fromhex(modulus_hex)  # hex convert bytes, 'bytes.hex()--->bytes to hex'
    patch_otp.write(modulus_byte)  # modulus's length is 2048 bit
    exponent_byte = exponent.to_bytes(4, byteorder=sys.byteorder, signed=True)  # int convert bytes
    exponent_int = int.from_bytes(exponent_byte, byteorder=sys.byteorder, signed=True)  # bytes convert int
    patch_otp.write(exponent_byte)  # exponent's original length is 17 bit, now, it's length is 32 bit
    # write signature
    patch_otp.write(signed_data)
    # 计算n、e的hash值
    pubkey = modulus_byte + exponent_byte
    pub_hash = hashlib.sha256(pubkey).digest()
    print('the hash value of RSA puk-key is: ')
    print(''.join(map(lambda x:('\\x' if len(hex(x))>=4 else '\\x0')+hex(x)[2:],pub_hash)))


def sm2_format(patch_otp, R, S):
    """
    根据bootrom的固件头，生成sm2的固件头格式
    :param patch_otp: 生成的新固件
    :param R: sm2的签名分量
    :param S: sm2的签名分量
    :return: 无
    """
    Len_ID = len(ID)
    Len_ID_byte = Len_ID.to_bytes(4, byteorder=sys.byteorder, signed=True)  # int convert 4 bytes
    # 写ID长度
    patch_otp.write(Len_ID_byte)
    # 写ID
    id_byte = ID + zeros(512-32*4-Len_ID)
    id_str = id_byte.decode('utf-8')
    patch_otp.write(id_byte)
    # 写公钥x、y分量
    pubx = public_key_x
    puby = public_key_y
    patch_otp.write(pubx)
    patch_otp.write(puby)
    # 写签名R、S
    signature_r = R
    signature_s = S
    patch_otp.write(signature_r)
    patch_otp.write(signature_s)
    # 计算idlen、id、pukx、puky的hash值
    pubkey = Len_ID_byte + id_byte + pubx + puby
    pub_hash = sm3.sm3_hash(func.bytes_to_list(pubkey))
    print('the hash value of sm2 puk-key is: ')
    print(''.join(map(lambda x:('\\x' if len(hex(x))>=4 else '\\x0')+hex(x)[2:],binascii.a2b_hex(pub_hash))))


# 对固件进行hash256
def hash_256(message):
    """
    当不需要对固件进行加密运算时，脚本会计算固件明文的hash值
    :param message: 固件明文
    :return: 固件明文的hash
    """
    mesg_hash = hashlib.sha256(message).digest()
    #print('the length of mesg_hash: ', len(mesg_hash))
    print('mesg_hash: ', binascii.hexlify(mesg_hash))
    return mesg_hash


# 没有经过加密和签名的固件头格式
def hash_format(patch_otp, hash_data):
    """
    根据bootrom的固件头格式，生成没有经过加密和签名的固件头格式
    :param patch_otp: 生成的新固件
    :param hash_data: 固件明文的hash值
    :return: 无
    """
    # 写hash数据，32字节
    patch_otp.write(hash_data)
    # 保留（516-32）字节
    reverse_value = bytes(516-32)
    #print(len(reverse_value))
    patch_otp.write(reverse_value)


if __name__ == "__main__":
    inputfile = ''
    outputfile = ''
    try:
        opts, args = getopt.getopt(sys.argv[1:], 'hi:o:asn', ['ifile=', 'ofile=', 'aes', 'sm4', 'non-encryption'])
    except getopt.GetoptError:
        print('rsa+noaes.py -i <inputfile> -o <outputfile> -a <aes> -s <sm4> -n <non-encryption>')
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print('rsa+noaes.py -i <inputfile> -o <outputfile> -a(aes) -s(sm4) -n(non-encryption)')
            sys.exit()
        elif opt in ('-i', '--ifile'):
            inputfile = arg
        elif opt in ('-o', '--ofile'):
            outputfile = arg
    # 在firmware中添加版本号version
    with open(inputfile, 'rb+') as f:
        origin_content = f.read()
        f.seek(0, 0)
        # write version
        version = b'\x00\x00\x00\x00'
        f.write(version + origin_content)
        f.close()

    input = open(inputfile, 'rb')
    patch_otp = open(outputfile, 'wb')
    input_data = input.read()
    """
    # file length
    file_len = len(input_data)
    data_len = file_len
    """
    # construct file header
    # write Magic
    magic = b'\x4b\x32\x33\x30'
    print('the magic is: ', magic)
    patch_otp.write(magic)
    """
    # write length
    length = struct.pack('I', data_len)
    print('the length of firmware: ', data_len)
    patch_otp.write(length)
    """
    # 全局变量
    message = input_data
    # 判断生成哪种形式的固件头
    for opt, arg in opts:
        if opt in ('-a', '--aes'):
            print('----- AES-GCM + RSA-2048 -----')
            # GCM加密
            AES_GCM = AES_ALG()
            encrypted_data = AES_GCM.aes_gcm_encrypt(input_data)
            message = encrypted_data[0] + encrypted_data[1]
            # 写长度: （固件密文+tag）
            data_len = len(message)
            data_len_byte = data_len.to_bytes(4, byteorder=sys.byteorder, signed=True)  # int convert 4 bytes
            patch_otp.write(data_len_byte)
            # 写加密类型
            encrypto_type = 2
            encrypto_type_b = encrypto_type.to_bytes(4, byteorder=sys.byteorder, signed=True)  # int convert bytes
            print('the encryption type: ', encrypto_type)
            patch_otp.write(encrypto_type_b)
            # RSA签名
            modulus = N
            modulus_hex = bytes.hex(modulus)
            modulus_int = int(modulus_hex, 16)
            exponent = E
            exponent_int = int(E, 16)
            d = D
            d_hex = bytes.hex(d)
            d_int = int(d_hex, 16)
            rsa_component_pub = (modulus_int, exponent_int)
            rsa_component_pri = (modulus_int, exponent_int, d_int)
            pub_key = RSA.construct(rsa_component_pub)
            pri_key = RSA.construct(rsa_component_pri)
            RSA = RSA_ALG()
            data_to_sign = encrypted_data[1]
            print('tag:')
            print(''.join(map(lambda x:('\\x' if len(hex(x))>=4 else '\\x0')+hex(x)[2:],data_to_sign)))
            signed_data = RSA.rsa_sign(data_to_sign, pri_key)
            # encryption_rsa = RSA.rsa_encrypt(data_to_enc, pub_key)
            # print(len(encryption_rsa))
            # 写RSA文件头
            rsa_format(patch_otp, modulus_int, exponent_int, signed_data)
        elif opt in ('-s', '--sm4'):
            print('----- SM4-CBC + SM2 -----')
            # SM4加密
            SM4 = SM4_ALG()
            encrypted_value = SM4.encrypt(input_data)
            message = encrypted_value#encrypted_value[0:len(input_data)]
            # 写长度: （固件密文）
            data_len = len(message)
            data_len_byte = data_len.to_bytes(4, byteorder=sys.byteorder, signed=True)  # int convert 4 bytes
            patch_otp.write(data_len_byte)
            # 写加密类型
            encrypto_type = 1
            encrypto_type_b = encrypto_type.to_bytes(4, byteorder=sys.byteorder, signed=True)  # int convert bytes
            print('the encryption type: ', encrypto_type)
            patch_otp.write(encrypto_type_b)
            # SM2签名
            SM2 = SM2_ALG()
            signature, r, s = SM2.sm2_sign(message)
            sign_hex = binascii.a2b_hex(signature)
            r_hex = binascii.a2b_hex(r)             # 功能跟bytes.fromhex()类似
            s_hex = binascii.a2b_hex(s)
            #print(binascii.hexlify(sign_hex), binascii.hexlify(r_hex), binascii.hexlify(s_hex))
            print('sign:')
            print(''.join(map(lambda x:('\\x' if len(hex(x))>=4 else '\\x0')+hex(x)[2:],sign_hex)))
            print('r:')
            print(''.join(map(lambda x:('\\x' if len(hex(x))>=4 else '\\x0')+hex(x)[2:],r_hex)))
            print('s:')
            print(''.join(map(lambda x:('\\x' if len(hex(x))>=4 else '\\x0')+hex(x)[2:],s_hex)))
            #SM2.sm2_verify(message, signature)
            # 写SM2文件头
            sm2_format(patch_otp, r_hex, s_hex)
        elif opt in ('-n', '--non-encryption'):
            print('----- NO ENCRYPTION + HASH-256 -----')
            # 写长度: （version+固件明文）
            data_len = len(input_data)
            data_len_byte = data_len.to_bytes(4, byteorder=sys.byteorder, signed=True)  # int convert 4 bytes
            patch_otp.write(data_len_byte)
            # write encryption type
            encrypto_type = 0
            encrypto_type_b = encrypto_type.to_bytes(4, byteorder=sys.byteorder, signed=True)  # int convert bytes
            print('the encryption type: ', encrypto_type)
            patch_otp.write(encrypto_type_b)
            # 对明文做hash256
            hash_data = hash_256(input_data)
            # 写hash头
            hash_format(patch_otp, hash_data)

    # write firmware
    patch_otp.write(message)
    patch_otp.close()
    input.close()



