import qrcode
import time
import hashlib
import hmac
import sys
import base64
import math

def qrCode_Generation():
	# QR code will be generated using the following url
	# This url is an example from https://github.com/google/google-authenticator/wiki/Key-Uri-Format
	url = "otpauth://totp/Example:alice@google.com?secret=JBSWY3DPEHPK3PXP&issuer=Example"

	QRcode = qrcode.make(url)	# generate QR code
	QRcode.save('QRcode.jpg')	# save QR code as jpg in the same directory



def otp_Generation():
	currentTime = int(time.time())
	t = math.floor(currentTime / 30)
	key = base64.b32decode('JBSWY3DPEHPK3PXP')

	hashResult = hmac.new(
		key,
		t.to_bytes(length=8, byteorder='big'),
		hashlib.sha1
	).hexdigest()

	# this following block is adapted from RFC
	# https://datatracker.ietf.org/doc/html/rfc4226#section-5.4
	offset = int(format(ord(hashResult[19]), 'b'), 2) & 0xf
	bin_code = ((int(format(ord(hashResult[offset]), 'b')) & 0x7f) << 24 |
		(int(format(ord(hashResult[offset+1]), 'b')) & 0xff) << 16   |
		(int(format(ord(hashResult[offset+2]), 'b')) & 0xff) <<  8   |
		(int(format(ord(hashResult[offset+3]), 'b')) & 0xff))

	result = str(bin_code % 1000000)
	print(result)
	
	return

if sys.argv[1] == '--generate-qr':
	qrCode_Generation()
elif sys.argv[1] == '--get-opt':
	while True:	
		otp_Generation()
		time.sleep(30)
