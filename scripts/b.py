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

	if (len(sys.argv) != 5):
		sys.exit()

	if (sys.argv[1] != '-name' or sys.argv[3] != '-const' or sys.argv[4] not in const):
		sys.exit()

	return sys.argv[2], sys.argv[4]

def setAxes(const):
	speed = [6667, 3333, 2222, 1667, 1333, 1111, 952, 833, 741]
	compression = [10, 30, 50, 70, 90]
	#compression = [0, 10, 30, 50]
	#numberOfRrh = [2, 3, 4, 5, 6, 10, 20, 30, 50]
	numberOfRrh = [2, 3, 4, 5, 6, 10]

	if const == 's':
		return numberOfRrh, compression, 'waitingTimeStat:mean', 'Compression percentage (%)', 'waitingTime (s)' 'Number of Rrhs'

	elif const == 'n':
		return speed, compression, 'delayStat:mean', 'Compression percentage (%)', 'Delay (s)', 'Speeds'

	else:
		return speed, numberOfRrh, 'delayStat:mean', 'Number of Rrhs', 'Delay(s)', 'Speeds'

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

		plt.errorbar(x, y, yerr=yerr, fmt="-*", markeredgecolor='red', capsize=4, linewidth=1)


	plt.xlabel(xlabel)
	plt.ylabel(ylabel)
	plt.grid(linestyle='--')
	plt.legend(line, title=legendTitle, loc='upper right')
	plt.show()


if __name__ == "__main__":
    main()