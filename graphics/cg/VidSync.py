import numpy as np
import cv2
from cv2 import xfeatures2d
from cv2 import FlannBasedMatcher
from matplotlib import pyplot as plt
import math
#from kdTreeNNeighbors import createM


def p(x):
	w = 2
	x = x*w
	

	return (math.exp(-x))
sift = cv2.xfeatures2d.SIFT_create()


#orb = cv2.ORB()
cap = cv2.VideoCapture('vid1.mp4')
keypointsVideo1=[]
frameNumber=1
featureCount=1
tim=0
temp=[]
deslist1=[]
deslist2=[]
kplist1 = []
kplist2 = []
while(cap.isOpened()):
	try:
		#print 'yea!'
		ret, frame = cap.read()
		#print frame
		#print frame
		kp1 = sift.detect(frame,None)
		#print kp
		kp1, des1 = sift.compute(frame, kp1)
		for d in des1:
			d2 = []
			for d1 in d:
				d2.append(d1)
			deslist1.append(d2)
		
		for kpp in kp1:
			kplist1.append(kpp)
		#print "yo"
        
        
        #kp, des1 = sift.detectAndCompute(im1,None)
		if tim<3:
			temp.append(kp1)
			tim=tim+1

		#print len(des1)

		for each, despeach in zip(kp1, des1):
			feature={}
			feature['kp']=each
			feature['frame']=frameNumber
			feature['desc']=despeach
			feature['featureCount']=featureCount
			keypointsVideo1.append(feature)
#			deslist1.append(despeach)
			#print despeach

		#img2 = cv2.drawKeypoints(frame,kp,color=(0,255,0), flags=0)
		#print "img2 created"
		#cv2.imshow('img2',img2)
		#print "img2"
		if cv2.waitKey(1) & 0xFF == ord('q'):
			#print 'No!'
			break
		frameNumber=frameNumber+1
	except(Exception):
		print 'Nope'
		break 
cap.release()
numberOfFramesVideo1=frameNumber
print frameNumber
print len(keypointsVideo1)
print len(kplist1)
print "Done till video1"
cap2 = cv2.VideoCapture('vid2.mp4')#changed
keypointsVideo2=[]
frameNumber=1
featureCount=1
while(cap2.isOpened()):
	try:

		ret, frame = cap2.read()
		#print frame
		#print frame
		kp = sift.detect(frame,None)
		#print kp
		kp, ds2 = sift.compute(frame, kp)
		for d in ds2:
			d2 = []
			for d1 in d:
				d2.append(d1)
			deslist2.append(d2)
		#print "yeah"
		for k in kp:
			kplist2.append(k)
		#print "hey"
        #kp, des1 = sift.detectAndCompute(im1,None)
		if tim<3:
			temp.append(kp)
			tim=tim+1

		#print len(des1)

		for each, despeach in zip(kp, ds2):
			feature={}
			feature['kp']=each
			feature['frame']=frameNumber
			feature['desc']=despeach
			feature['featureCount']=featureCount
			keypointsVideo2.append(feature)
#			deslist2.append(despeach)
			#print despeach

		#img2 = cv2.drawKeypoints2(frame,kp,color=(0,255,0), flags=0)
		#print "img2 created"
		#cv2.imshow('img2',img2)
		#print "img2"
		if cv2.waitKey(1) & 0xFF == ord('q'):
			break
		frameNumber=frameNumber+1
	except(Exception):
		break 
cap2.release()
numberOfFramesVideo2=frameNumber
print numberOfFramesVideo1
#print len(keypointsVideo2), len(ds2)
print len(keypointsVideo2)
print len(kplist2)
cv2.destroyAllWindows()
count=0
"""print des1
for eachDesc in des1:
	for eachDesc2 in des1:
		print eachDesc




		'''
		for each in eachDesc:
			for each2 in eachDesc2:
				if each ==each2:
					print eachDesc
					count=count+1
print count, len(des1)
'''
"""
"""
list=[]
for each in keypointsVideo2:
	list.append(each['kp'])
set1=set(list)
print len(set1), len(list)
		
			#print each['desc'], each2['desc']

"""
#print temp
#print keypointsVideo2
print "Done page1"

#print keypointsVideo1

#Shrukuls version

#print len(keypointsVideo2), len(ds2)

# FLANN parameters
FLANN_INDEX_KDTREE = 0
index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 5)
search_params = dict(checks=50)   # or pass empty dictionary

flann = cv2.FlannBasedMatcher(index_params,search_params)

#print deslist1

matches = flann.knnMatch(np.asarray(deslist1,np.float32),np.asarray(deslist2,np.float32),k=1)
print len(matches)


h = [[0 for x in range(numberOfFramesVideo1)] for x in range(numberOfFramesVideo2)]
dist = []
maxh = 0

doc = open('match.txt','a')
for mtch in matches:
 for mc in mtch:
 	m = mc

 #dist.append(m.distance)
 for vid1,vid2 in zip(keypointsVideo1,keypointsVideo2):
	if(vid2['kp'] == kplist2[m.trainIdx]  and  vid1['kp'] == kplist1[m.queryIdx]):
	    h[vid1['frame']][vid2['frame']] = h[vid1['frame']][vid2['frame']] + p(m.distance)*(p(math.sqrt(pow((kplist2[m.trainIdx].pt[0]-kplist1[m.queryIdx].pt[0]),2)+pow((kplist2[m.trainIdx].pt[1]-kplist1[m.queryIdx].pt[1]),2))))
	    #doc.write(m.distance + ' '+vid1['frame']+' '+vid2['frame']+ ' '+h[vid1['frame']][vid2['frame']]+'\n')

 if (maxh < h[vid1['frame']][vid2['frame']]):
 	maxh = h[vid1['frame']][vid2['frame']]
 #xd  =  xd+
#print len(matches)


for i in range(numberOfFramesVideo1):
	for j in range(numberOfFramesVideo2):
		h[i][j] = pow(  (1 - (h[i][j]/maxh)),4)

print h 
fmat = open('finalMatrix.txt','w')
fmat.write(h)
#matchMatrix=createM(keypointsVideo1,keypointsVideo2,numberOfFramesVideo1,numberOfFramesVideo2)
#print matchMatrix

