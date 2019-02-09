import os
import sys

def main():
	speed = [6667, 3333, 2222, 1667, 1333, 1111, 952, 833, 741]
	compression = [0, 10, 20, 30, 40, 50, 70, 90]
	numberOfRrh = [2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50]

	for s in speed:
		for n in numberOfRrh:
			for c in compression:
				os.system('scavetool x ../simulations/results/exponential-compression-' + str(s) + ',' + str(n) + ',' + str(c) + '-*.sca -o ../csv/exponential-compression-' + str(s) + '-' + str(n) + '-' + str(c) + '.csv')


if __name__ == "__main__":
    main()