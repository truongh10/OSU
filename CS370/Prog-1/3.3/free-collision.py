import hashlib
import random


class CollisionFree:
	def __init__(self, strLen):
		self.strLen = strLen

# generate a random string
#**************************************************************
	def stringGen(self, strLen):
		a = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
		'p','q','r','s','t','u','v','w','x','y','z','0','1','2','3',
		'4','5','6','7','8','9']
		# create a random string of length 16
		randStr = ''
		for i in range(strLen):
			rand = random.randint(0,35)	# generate random number from 0 to 35
			randStr += a[rand]

		randStr = randStr.encode()	# convert to byte type
		# print('Random Str: ',randStr)
		return randStr
#***********************************************************

# Hash Generator
#************************************************************
	def hashGen(self, input):
		digest = hashlib.md5()
		digest.update(input)
		msg = digest.hexdigest()

		# print('Digest msg(byte):',msg)
		# print('Digest msg(str) :',msg.hex())
		return msg
#************************************************************

if __name__ == "__main__":
	counter = 0
	strLen = 16
	dup = dict()
	_collisionFree = CollisionFree(strLen)

	

	avgTrials = 0
	for i in range(100):
		while True:
			counter += 1
			input = _collisionFree.stringGen(strLen)	#generate a string
			hash = _collisionFree.hashGen(input)	#hash generator
			hash_24bits = hash[0:6]	# get first 24 bits

			if hash_24bits in dup and dup.get(hash_24bits) != input:				
				# print('count: ', counter)
				break
			dup[hash_24bits] = input
				
		avgTrials += counter

	avgTrials = avgTrials / 10
	print('Avg Trials: ', avgTrials)

			


		


		
