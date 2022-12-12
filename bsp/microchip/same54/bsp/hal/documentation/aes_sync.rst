======================
AES Synchronous driver
======================

The Advanced Encryption Standard (AES) is a specification for the encryption of
electronic data established by the U.S. National Institute of Standards and
Technology (NIST) in 2001. AES operates on a 128-bit block of input data. The
key size used for an AES cipher specifies the number of repetitions of
transformation rounds that convert the input, called the plaintext, into the
final output, called the ciphertext. The AES works on a symmetric-key
algorithm, meaning the same key is used for both encrypting and decrypting the
data.

The driver supports ECB/CBC/CFB/OFB/CTR mode for data encryption, and GCM/CCM
for authenticated encryption. Before use any encrypt mode of AES, the key must
be set firstly. And for privacy situaion, after encrypt/decrypt data, the key
should be cleared by application. Common practice is set the key to zero.

Features
--------

* Initialization and de-initialization
* Enabling and Disabling
* Set 128/192/256 bit cryptographic key
* Electronic Code Book (ECB)
* Cipher Block Chaining (CBC)
* Cipher Feedback (CFB) in 8,16,32,64,128 bits size
* Output Feedback (OFB)
* Counter (CTR)
* CCM (Counter with CBC-MAC) mode for authenticated encryption
* GCM (Galois Counter mode) encryption and authentication

Applications
------------
* Encrypt plain data to ciphered data, or decrypt ciphered data to plain text with
  the same authentication key, the ciphered data cannot be recovered without
  authentication key.

Dependencies
------------
* AES capable hardware

Concurrency
-----------
N/A

Limitations
-----------
* GCM only support known length data process, that mean the aes_sync_gcm_update
  cannot be invoke multiple times, application should assembly all data into a
  data buffer and then call once aes_sync_gcm_update to encrypt/decrypt data.

Known issues and workarounds
----------------------------
N/A

