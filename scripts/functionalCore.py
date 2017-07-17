from bvt_python import *
from ctypes import *
import cv2
import numpy as np

class functionalCore:
	def __init__(self):
		rootPath = "/home/turk/Thesis/"
		dataPath = rootPath + "dat/"
		mapperPath = rootPath + "bvtsdk/colormaps/copper.cmap"
		fileName = "Apr_25_2017_231947.son"
		fullPath = dataPath + fileName
		
		self.sonar = Sonar()
		self.sonar.open("FILE",fullPath)
		self.head = self.sonar.get_head(0)
		self.ping = self.head.get_ping(-1)

		self.img = ImageGenerator()
		self.img.set_head(self.head)
		self.map = ColorMapper()
		self.map.load(mapperPath)
		self.mag = self.img.get_image_xy(self.ping)
		self.cimg = self.map.map_image(self.mag)

		print self.head.ping_count
		x = self.cimg.bits
		height = self.cimg.height;
		width = self.cimg.width;
		arr = (c_float * height * width * 3).from_address(addressof(x.contents))
		t = np.ndarray(buffer=arr,shape=(width,height,3),dtype=np.uint8)

		print x.contents


	def debug(self):
		while(True):
			# pass
			self.ping = self.head.get_ping(-1)
			self.mag = self.img.get_image_xy(self.ping)
			self.cimg = self.map.map_image(self.mag)



if __name__ == "__main__":
	f = functionalCore()
