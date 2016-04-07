import numpy as np
import cv2

cap = cv2.VideoCapture('testvideo.mp4')

if (cap.isOpened()):
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray=frame
    cv2.imshow('frame',gray)
    if cv2.waitKey(25) & 0xFF == ord('q'):
        print "hello"

#cap.release()
#cv2.destroyAllWindows()

