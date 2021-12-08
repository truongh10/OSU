from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding
import sys

class Encrypt:
	def __init__(self):
		print ("Encrypting")

	def encrypt(self):
		# read plaintext from text.txt
		with open(sys.argv[1], 'r') as f:
			content = f.read()
    		# read text file line by line
		with open('words.txt') as f:
			for index, line in enumerate(f):
				key = line.strip()  # get key

				if (len(key) <= 16):
					# the numbers in the IV are all zeros
					iv = b'\0' * 16
					# print(iv)

					# ciphertext in hex format
					ciphertext = "8d20e5056a8d24d0462ce74e4904c1b513e10d1df4a2ef2ad4540fae1ca0aaf9"
					# print(type(ciphertext))

					# print(ciphertext)

					# plaintext
					plaintext = content.encode()


					# Pad to AES Block Size
					padder = padding.PKCS7(128).padder()
					padded_data = padder.update(plaintext)
					padded_data += padder.finalize()

					# print(type(padded_data))
					# print(padded_data)


					# append spaces to key that is less than 16 in length
					while (len(key) < 16):
						key = key + " "

					# print(key)
					key = key.encode()
					# print(key)
			

					cipher = Cipher(algorithms.AES(key), modes.CBC(iv))
					encryptor = cipher.encryptor()
					ct = encryptor.update(padded_data) + encryptor.finalize()

					ct = ct.hex()

					if ct == ciphertext:
						print("************************************************")
						print("Encrypted cipher: ",ct)
						print("Given Cipher    : ",ciphertext)
						print("Key found: ",key)
						return
		
if __name__ == "__main__":
	_encrypt = Encrypt()
	_encrypt.encrypt()


