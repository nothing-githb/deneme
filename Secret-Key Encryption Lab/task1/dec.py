import collections
import pprint
import operator
import collections

with open("ciphertext.txt", 'r') as info:
	data = info.read().replace(" ","").replace("\n","")
	count = collections.Counter(data)

x = dict(count)
print(sorted(x.items(), key = lambda kv:(kv[1], kv[0])))

alphabet = "abcdefghijklmnopqrstuvwxyz"
freq =     "etaonisrhdlucmwfygpbvkxjqz"
aa= 	   "nyvxuqmhtipaczlgbredfskjow"

		   "etaoinshrdlucmwfygpbvkxjqz"
etaonsirhldcmuwbfgpyvkxqjz