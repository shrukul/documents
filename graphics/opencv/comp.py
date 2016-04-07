'''import numpy as np
import cv2
from matplotlib import pyplot as plt

img1 = cv2.imread('image1.png',0)          # queryImage
img2 = cv2.imread('image2.png',0) # trainImage

# Initiate SIFT detector
orb = cv2.ORB_create()

# find the keypoints and descriptors with SIFT
kp1, des1 = orb.detectAndCompute(img1,None)
kp2, des2 = orb.detectAndCompute(img2,None)

# create BFMatcher object
bf = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=True)

# Match descriptors.
matches = bf.match(des1,des2)

# Sort them in the order of their distance.
matches = sorted(matches, key = lambda x:x.distance)

# Draw first 10 matches.
img3 = cv2.drawMatches(img1,kp1,img2,kp2,matches[:10],None, flags=2)

#plt.imshow(img3),plt.show()
#print matches

for m in matches:
  #print m.distance
  print m.trainIdx, m.queryIdx, m.imgIdx ,m.distance'''
import numpy as np
import cv2
from cv2 import xfeatures2d
from matplotlib import pyplot as plt
import math

def index_2d(myList, v):
    for i, x in enumerate(myList):
        if v in x:
            return (i, x.index(v))

def p(x):
	w = 2
	x = x*w
	

	return (math.exp(-x))

img1 = cv2.imread('/home/shrukul/Documents/graphics/opencv/image1.png',0)          # queryImage
#img1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
img2 = cv2.imread('/home/shrukul/Documents/graphics/opencv/image2.png',0) # trainImage
#img2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)

# Initiate SIFT detector
sift = cv2.xfeatures2d.SIFT_create()

# find the keypoints and descriptors with SIFT
kp1, des1 = sift.detectAndCompute(img1,None)
kp2, des2 = sift.detectAndCompute(img2,None)
'''
for i in range(0,len(des1)) :
  print des1[i].pt[0], des1[i].pt[1]'''

# BFMatcher with default params
bf = cv2.BFMatcher()
#matches = bf.knnMatch(des1,des2, k=2)
matches = bf.match(des1,des2)
print len(matches), len(des1), len(des2)

h = 0

#print matches
for m in matches[0:20]:
 print m.trainIdx
 #desd = desd+pow((m.distance),2)
 h = h+p(m.distance)*(p(math.sqrt(pow((kp1[m.trainIdx].pt[0]-kp2[m.queryIdx].pt[0]),2)+pow((kp1[m.trainIdx].pt[1]-kp2[m.queryIdx].pt[1]),2))))
 #xd  =  xd+

print h
'''
for m in matches:
  print m.distance
  print m.trainIdx, m.queryIdx, m.imgIdx ,m.distance'''

# Apply ratio test
'''good = []
for m,n in matches:
    if m.distance < 0.75*n.distance:
        good.append([m])
        #print m, index_2d(matches,m)'''

#print good

# cv2.drawMatchesKnn expects list of lists as matches.
#img3 = cv2.drawMatchesKnn(img1,kp1,img2,kp2,good,None,flags=2)

# Sort them in the order of their distance.
matches = sorted(matches, key = lambda x:x.distance)

# Draw first 10 matches.
img3 = cv2.drawMatches(img1,kp1,img2,kp2,matches[:200],None, flags=2)

plt.imshow(img3),plt.show()
