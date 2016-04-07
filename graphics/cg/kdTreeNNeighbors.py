import numpy as np
from sklearn.neighbors import KDTree
import ast

import warnings
warnings.filterwarnings("ignore")

def createM(keypointsVideo1,keypointsVideo2,numberOfFramesVideo1,numberOfFramesVideo2):
	#X=np.array([[1, 4], [3, 4], [5, 4], [7, 4]])
	#X=np.array([[1, 2, 3], [2, 4, 5], [3, 5, 6], [4, 7, 8]])
	"""keypointsList2=[]
	#list=keypointsVideo2.split(',')
	#print list
	#j=json.loads(keypointsVideo2)
	#print j
	s=keypointsVideo2
	flag=0
	dicString=""
	for each in keypointsVideo2:
		#print each
		#print type(each)
		if flag==1:
			dicString+=str(each)
			#print "dicString", dicString
			flag=1
		elif each is "{":
			dicString+=str(each)
			#print "dicString", dicString
			flag=1
		if(each=="}"):
			#print dicString
			keypointsList2.append(dicString)
			dicString=""
			flag=0



	print list
	dict = list[1]"""
	
	#for each in keypointsVideo2:
	#	print each['frame']
	#	list.append(each['kp'])
	isFirst=1
	for eachFeature in keypointsVideo2:
		#print eachFeature['desc']
		if isFirst is 1:
			X=np.array(eachFeature['desc'])
			isFirst=0
		else:
			X=np.vstack((X,np.array(eachFeature['desc'])))
	#print X
		
	print "Done some work"	
	
	tree = KDTree(X, leaf_size=2,metric='euclidean')
	matchMatrix=[]
	for each in keypointsVideo1:
		distance, indices = tree.query(each['desc'], k=len(X))
		#print keypointsVideo2[indices[0][0]]
		match={}
		match['frame1']=each['frame']
		match['frame2']=keypointsVideo2[indices[0][0]]['frame']
		match['kp1']=each['kp']
		match['kp2']=keypointsVideo2[indices[0][0]]['kp']
		matchMatrix.append(match)
		#print "Yep"
	#print matchMatrix
	return matchMatrix


	


if __name__ == "__main__":
    kdTree()