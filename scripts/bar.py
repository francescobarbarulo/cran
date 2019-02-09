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
	if len(sys.argv) != 5:
		sys.exit()

	if sys.argv[1] != '-name' or sys.argv[3] != '-n':
		sys.exit()

	return sys.argv[2], sys.argv[4]

def setAxes(const):
	speed = [6667, 3333, 2222, 1667, 1333, 1111, 952, 833, 741]
	compression = [10, 30, 50, 70, 90]
	#compression = [0, 10, 30, 50]
	#numberOfb = [2, 3, 4, 5, 6, 10, 20, 30, 50]
	numberOfb = [2, 3, 4, 5, 6, 10]

	if const == 's':
		return numberOfb, compression, 'waitingTimeStat:mean', 'Compression percentage (%)', 'waitingTime (s)', 'Number of bs'

	elif const == 'n':
		return speed, compression, 'delayStat:mean', 'Compression percentage (%)', 'Delay (s)', 'Speeds'

	else:
		return speed, numberOfb, 'delayStat:mean', 'Number of bs', 'Delay(s)', 'Speeds'

def main():
	name, n = parseCommand()
	z = 2.845 # level CI 99%

	#line, x, nameStat, xlabel, ylabel, legendTitle = setAxes(const)
	x = [10, 20, 30, 40, 50, 60, 70, 80, 90]

	aMeans = []
	bMeans = []
	aErr = []
	bErr = []

	for i in x:
		filename = '../csv/'+name+'-'+n+'-'+str(i)+'.csv'
		print 'Open ' + filename
		try:
			df = pd.read_csv(filename)
			a = df[(df.type=='scalar') & (df.name=='waitingTimeStat:mean')]
			b = df[(df.type=='scalar') & (df.name=='responseTimeStat:mean')]
			
			aMeans.append(stat.mean(a.value))
			bMeans.append(stat.mean(b.value)-stat.mean(a.value))
			
			aErr.append(stat.stdev(a.value)/math.sqrt(len(a.value))*z)
			#bErr.append((stat.stdev(b.value)-stat.mean(a.value))/math.sqrt(len(b.value))*z)
			
		except Exception, e:
			print e

	plt.bar(x, aMeans, yerr=aErr, width=3, color='m', capsize=4)
	plt.bar(x, bMeans, width=3, color='c', bottom=aMeans, capsize=4)


	plt.xlabel('Compression percentage (%)')
	plt.ylabel('RRH Response time (s)')
	plt.grid(linestyle='--')
	plt.xticks(np.arange(10,91,10))
	plt.yticks(np.arange(0,12,2))
	plt.ylim(0, 12)
	plt.legend(['E[W]', 'E[t]'])
	plt.show()


if __name__ == "__main__":
    main()