import os
import sys

def parseCommand():
	if (len(sys.argv) < 3):
		sys.exit()

	if (sys.argv[1] != '-name'):
		sys.exit()

	return sys.argv[2]

def main():
	name = parseCommand()
	speed = [6667, 3333, 2222, 1667, 1333, 1111, 952, 833, 741]
	numberOfRrh = [2, 5, 10]

	for s in speed:
		for n in numberOfRrh:
			os.system('scavetool x ../simulations/results/'+name+'-' + str(s) + ',' + str(n) + '*.sca -o ../csv/'+name+'-' + str(s) + '-' + str(n) + '.csv')


if __name__ == "__main__":
    main()