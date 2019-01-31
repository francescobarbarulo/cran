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
	const = ['s', 'c', 'n']

	if len(sys.argv) != 5:
		sys.exit()

	if sys.argv[1] != '-name' or sys.argv[3] != '-const' or sys.argv[4] not in const:
		sys.exit()

	return sys.argv[2], sys.argv[4]

def setAxes(const):
	speed = [741, 833, 952, 1111, 1333, 1667, 2222, 3333, 6667]
	#x = [{'rho': 0.1, 'speed': 6667}, {'rho': 0.2, 'speed': 3333}, {'rho': 0.3, 'speed': 2222}, {'rho': 0.4, 'speed': 1667}, {'rho': 0.5, 'speed': 1333}, {'rho': 0.6, 'speed': 1111}, {'rho': 0.7, 'speed': 952}, {'rho': 0.8, 'speed': 833}, {'rho': 0.9, 'speed': 741}]
	compression = [10, 20, 30, 40, 50, 70, 90]
	#compression = [10, 30, 50, 70, 90]
	#numberOfRrh = [2, 3, 4, 5, 6, 10, 20, 30, 50]
	numberOfRrh = [4, 5, 6, 7, 8, 9, 10, 20, 30, 50]

	if const == 's':
		return numberOfRrh, compression, 'responseTimeStat:mean', 'Compression percentage (%)', 'RRH Response Time (s)', 'Number of Rrhs'

	elif const == 'n':
		return speed, compression, 'responseTimeBbuStat:mean', 'Compression percentage (%)', 'Delay (s)', 'Speeds (bytes/s)'

	else:
		return speed, numberOfRrh, 'responseTimeStat:mean', 'Number of Rrhs', 'Delay(s)', 'Speeds (bytes/s)'

def main():
	name, const = parseCommand()
	z = 2.845 # level CI 99%

	line, x, nameStat, xlabel, ylabel, legendTitle = setAxes(const)

	for l in line:
		y = []
		yerr = []
		for i in x:
			filename = '../csv/'+name+'-'+str(l)+'-'+str(i)+'.csv'
			try:
				df = pd.read_csv(filename)
				tmp = df[(df.type=='scalar') & (df.name==nameStat)]
				
				mean = stat.mean(tmp.value)
				y.append(mean)
				stdev = stat.stdev(tmp.value)
				e = stdev/math.sqrt(len(tmp.value))*z
				yerr.append(e)
				#print "%s: %f / %f (%d)" % (filename, mean, stdev, len(delay.value))
				#print delay.value
			except Exception, e:
				print e

		print '%.2f - %.2f' % (y[0], y[-1])
		plt.errorbar(x, y, yerr=yerr, fmt="-*", markeredgecolor='red', capsize=4, linewidth=1)


	plt.xlabel(xlabel)
	plt.ylabel(ylabel)
	#plt.yscale('log')
	plt.grid(linestyle='--')
	#plt.ylim(0, 12)
	plt.yticks(np.arange(0, 12, 2))
	#plt.legend(line, title=legendTitle, loc=2, bbox_to_anchor=(1.05, 1), borderaxespad=0.)
	plt.legend(line, title=legendTitle)
	plt.show()


if __name__ == "__main__":
    main()