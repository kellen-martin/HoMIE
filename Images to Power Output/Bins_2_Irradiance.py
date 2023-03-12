import cv2 as cv
import matplotlib.pyplot as plt
from PIL import Image
import numpy as np

"""
Bias = 0-5 bins
Average Bias = 2 bins

"""

"""
Finding Intensity Bins
"""
img_dark = cv.imread('Dark View 3_9 0d5ms.tif',0) # 0 = grayscale
img = cv.imread('Direct View 3_9 0d05ms.tif',0)
# shape = img.shape
# print(shape)

int_light = []
int_dark = []
electron_signal = []
Gain = 1 # linear units

"""
Intensity Bins -> Electron Signal
"""
for i in range(0,2048): 
    for j in range(0,2048):
           #int_light.append(img[i][j])
           #int_dark.append(img_dark[i][j])
           temp = (img[i][j]-2)*Gain
           electron_signal.append(temp)

# print(min(electron_signal))
# print(max(electron_signal))

"""
Electron Signal -> Photon Signal
"""
QE = 0.33 # Quantum Efficiency at 405nm
photon_count = np.divide(electron_signal,QE)
h = 6.6262*10**-34 # [J*s] -- Plancks Constant
c = 3.0*10**8 # [m/s]
wl = 405*10**-9 # [nm] -> [m]
f = c/wl 
E = np.multiply(h*f,photon_count) # Energy of a photon [J]
deltat = 5*10**-3 # [ms] - > [s]
Power = np.divide(E,deltat)
print(Power)



#print(min(int_dark))
#print(max(int_dark))
# print(min(int_light))
# print(np.mean(int_dark)) # AVERAGE BIAS = 2 

# print(len(intensities))
# img_new = Image.open("Direct View 3_9 0d05ms.tif")
# px = img_new.load()
# print(px[4,4])
  
# alternative way to find histogram of an image
# plt.hist(img.ravel(),255,[0,255])
# plt.title('Intensity Histogram Direct View 5ms')
# plt.xlabel('Pixel Intensity')
# plt.ylabel('Number of Pixels')
# plt.show()