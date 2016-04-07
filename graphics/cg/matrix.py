import csv
import numpy
'''with open('final_matches1.txt','r') as inf:
    dict_from_file = eval(inf.read())

for dc in dict_from_file:
	if(dc['frame1']==100):
		print dc['kp1']
'''
#fl = open('mp.txt','r')

# st = fl.readlines()
# mat = []
# for line in st:
#     row = []
#     row.append(line)
#     mat.append(row)
# print mat
# open 
# #suf = open('hmat.txt','w')

reader=csv.reader(open("finalMatrix.txt","rb"),delimiter=',')
x=list(reader)
result=numpy.array(x).astype('float')
print result[2][1]