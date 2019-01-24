import sys
import pandas as pd
import matplotlib
import math
import numpy as np
import statistics as stat
matplotlib.use('TkAgg')
from matplotlib import rcParams
rcParams['font.family'] = 'serif'
import matplotlib.pyplot as plt

def parseCommand():
	if (len(sys.argv) < 3):
		sys.exit()

	if (sys.argv[1] != '-name'):
		sys.exit()

	return sys.argv[2]

def main():
	name = parseCommand()
	z = 2.845 # level CI 99%
	speed = [6667, 3333, 2222, 1667, 1333, 1111, 952, 833, 741]
	numberOfRrh = [2, 5, 10]

	for n in numberOfRrh:
		y = []
		yerr = []
		for s in speed:
			filename = '../csv/'+name+'-'+str(s)+'-'+str(n)+'.csv'
			try:
				df = pd.read_csv(filename)
				delay = df[(df.type=='scalar') & (df.module=='CRan.collector')]
				mean = stat.mean(delay.value)
				y.append(mean)
				stdev = stat.stdev(delay.value)
				e = stdev/math.sqrt(len(delay.value))*z
				yerr.append(e)
				#print "%s: %f / %f (%d)" % (filename, mean, stdev, len(delay.value))
				#print delay.value
			except:
				print 'Cannot read %s' % filename
				sys.exit()

		plt.errorbar(speed, y, yerr=yerr, fmt="-*", markeredgecolor='red', ecolor="black", capsize=4, linewidth=1)


	plt.xlabel('BbuSpeed (bytes/s)')
	plt.ylabel('Delay (s)')
	plt.grid(linestyle='--')
	plt.show()


if __name__ == "__main__":
    main()