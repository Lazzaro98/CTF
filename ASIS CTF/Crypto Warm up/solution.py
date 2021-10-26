from Crypto.Util.number import *
import string
import re

def decrypt(enc, s):
	p = len(enc)
	msg = ['0']*p
	msg[0] = enc[0]
	for i in range(1, p):
		msg[pow(s,i-1,p)] = enc[i]
	msg = ''.join(msg)
	if "ASIS{" in msg:
		print(re.search("(ASIS{.*})", msg).group(1))

lines = ''
with open('all_s_values.py') as f:
    lines = f.readlines()
lines = lines[0].replace('\n','').split(',')
map(str.strip, lines)

enc = ''
with open('output.txt') as f:
    enc = f.readlines()[0]



print("Decrypting...")
for i in lines:
	decrypt(enc,int(i))




