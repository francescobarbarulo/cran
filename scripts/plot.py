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

def main():
	compression = [0, 10, 20, 30, 40, 50]
	speed = 1333
	filename = ['exponential-'+str(speed)+'-5', 'exponential-s-'+str(speed)+'-4-', 'exponential-s-'+str(speed)+'-30-']
	z = 2.845 # level CI 99%

	for f in filename:
		y = []
		yerr = []
		for i in compression:
			try:
				if f == 'exponential-'+str(speed)+'-5':
					df = pd.read_csv('../csv/'+f+'.csv')
				else:
					df = pd.read_csv('../csv/'+f+str(i)+'.csv')

				
				tmp = df[(df.type=='scalar') & (df.name=='delayStat:mean')]

				mean = stat.mean(tmp.value)
				y.append(mean)
				stdev = stat.stdev(tmp.value)
				e = stdev/math.sqrt(len(tmp.value))*z
				yerr.append(e)

			except Exception, e:
				print e

		plt.errorbar(compression, y, yerr=yerr, fmt="-*", markeredgecolor='red', capsize=4, linewidth=1)

	plt.xlabel('Compression percentage (%)')
	plt.ylabel('Delay (s)')
	#plt.yscale('log')
	plt.grid(linestyle='--')
	#plt.yticks(np.arange(0, 9, 1))
	#plt.legend(line, title=legendTitle, loc=2, bbox_to_anchor=(1.05, 1), borderaxespad=0.)
	plt.legend(['No compression', 'Compression 4 RRHs', 'Compression 30 RRHs'], title='System type')
	plt.show()

if __name__ == "__main__":
    main()