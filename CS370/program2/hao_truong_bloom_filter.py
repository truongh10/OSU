import time
import hashlib
import sys



hash3 = 3
hash5 = 5


# create an array that contains 5 different hash functions
hashArray = ['md5', 'sha1', 'sha224', 'sha512', 'sha3_256']


# function that parses data from input file
def parseData(path):
	data = []
	f = open(path,'rb')
	for line in f:
		data.append(line.strip())
	f.close()
	return data

pws = parseData(sys.argv[2])
pwsToCheck = parseData(sys.argv[4])

print(len(pwsToCheck))

size = len(pws) * 8

bloomFilter3 = [False] * size
bloomFilter5 = [False] * size

def add(pw, hashNum, bloomFilter):
	for i in range(hashNum):
		hash = getattr(hashlib, hashArray[i])
		index = int(hash(pw).hexdigest(),16) % size
		bloomFilter[index] = True

def check3(pw, bloomFilter, outputFile):
	# tmp = [False] * size

	hash = getattr(hashlib, hashArray[0])
	index0 = int(hash(pw).hexdigest(),16) % size

	hash = getattr(hashlib, hashArray[1])
	index1 = int(hash(pw).hexdigest(),16) % size	

	hash = getattr(hashlib, hashArray[2])
	index2 = int(hash(pw).hexdigest(),16) % size


	f = open(outputFile, 'a')


	if (bloomFilter[index1] == True and bloomFilter[index0] == True and bloomFilter[index2] == True):
		f.write(pw.decode('utf-8') + ' maybe\n')
	else:
		f.write(pw.decode('utf-8') + ' no\n')
	f.close()


def check5(pw, bloomFilter, outputFile):
	hash = getattr(hashlib, hashArray[0])
	index0 = int(hash(pw).hexdigest(),16) % size

	hash = getattr(hashlib, hashArray[1])
	index1 = int(hash(pw).hexdigest(),16) % size	

	hash = getattr(hashlib, hashArray[2])
	index2 = int(hash(pw).hexdigest(),16) % size

	hash = getattr(hashlib, hashArray[3])
	index3 = int(hash(pw).hexdigest(),16) % size

	hash = getattr(hashlib, hashArray[4])
	index4 = int(hash(pw).hexdigest(),16) % size	


	f = open(outputFile, 'a')

	if (bloomFilter[index1] == True and bloomFilter[index0] == True and bloomFilter[index2] == True and bloomFilter[index3] == True and bloomFilter[index4] == True ):		
		f.write(pw.decode('utf-8') + ' maybe\n')
	else:
		f.write(pw.decode('utf-8') + ' no\n')
	f.close()

for pw in pws:
	add(pw,hash3,bloomFilter3)
	add(pw,hash5,bloomFilter5)

t1 = 0
t2 = 0

for pw in pwsToCheck:
	time1 = time.time()
	check3(pw,bloomFilter3,sys.argv[6])
	time2 = time.time()
	t1=time2-time1
	print('time to check 1 password for 3 hases: ', t1)

	check5(pw,bloomFilter5,sys.argv[8])
	time3 = time.time()

	t2=time3-time2
	print('time to check 1 password for 5 hases: ', t2)


		
print(len(pws))
	
