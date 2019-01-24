import sys
import pandas as pd
import matplotlib
import math
import numpy as np
matplotlib.use('TkAgg')
from matplotlib import rcParams
rcParams['font.family'] = 'serif'
import matplotlib.pyplot as plt

def main():
	delay = []
	simTime = []

	window = 10000

	df = pd.read_csv('../csv/warmup.csv', header=None, skiprows=1)

	for col in df.columns:
		values = []
		for x in df[col]:
			if not math.isnan(x):
				values.append(x)
		if col%2 == 0:
			simTime.append(values)
		else:
			delay.append(values)

	for x, y in zip(simTime, delay):
		plt.plot(x, pd.Series(y).rolling(window, 1).mean())


	plt.xlabel('simTime (s)')
	plt.ylabel('Delay (s)')
	plt.yticks(np.arange(0, 50, step=5))
	plt.ticklabel_format(axis='x', style='sci')
	plt.grid(linestyle='--')
	plt.show()


if __name__ == "__main__":
    main()