import os
import cv2
import numpy as np
img1 = cv2.imread("python/result/2.jpg")
img2 = cv2.imread("python/result/3.jpg")

img1 = cv2.resize(img1, (100,50))
img2 = cv2.resize(img2, (100,50))

img = np.hstack((img1,img2))

cv2.imshow("img", img)
cv2.waitKey(0)
