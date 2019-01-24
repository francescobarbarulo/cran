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
	if (len(sys.argv) != 3):
		sys.exit()

	if (sys.argv[1] != '-name'):
		sys.exit()

	return sys.argv[2]

def main():
	name = parseCommand()
	z = 2.845 # level CI 99%
	compression = [10, 30, 50, 70, 90]
	numberOfRrh = [4, 5, 6, 10, 20, 30, 50]

	for n in numberOfRrh:
		y = []
		yerr = []
		for c in compression:
			filename = '../csv/'+name+'-'+str(c)+'-'+str(n)+'.csv'
			try:
				df = pd.read_csv(filename)
				waiting = df[(df.type=='scalar') & (df.name=='waitingTimeStat:mean')]
				
				mean = stat.mean(waiting.value)
				y.append(mean)
				stdev = stat.stdev(waiting.value)
				e = stdev/math.sqrt(len(waiting.value))*z
				yerr.append(e)
				#print "%s: %f / %f (%d)" % (filename, mean, stdev, len(delay.value))
				#print delay.value
			except:
				print 'Cannot read %s' % filename
				sys.exit()

		plt.errorbar(compression, y, yerr=yerr, fmt="-*", markeredgecolor='red', capsize=4, linewidth=1)


	plt.xlabel('Compression percentage (%)')
	plt.ylabel('waitingTime (s)')
	plt.grid(linestyle='--')
	plt.legend(numberOfRrh, title='Number of Rrhs')
	plt.show()


if __name__ == "__main__":
    main()