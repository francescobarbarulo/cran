import os
import sys

def parseCommand():
	const = ['s', 'c', 'n']

	if (len(sys.argv) != 5):
		sys.exit()

	if (sys.argv[1] != '-name' or sys.argv[3] != '-const' or sys.argv[4] not in const):
		sys.exit()

	return sys.argv[2], sys.argv[4]

def getFactors(const):
	speed = [6667, 3333, 2222, 1667, 1333, 1111, 952, 833, 741]
	compression = [0, 10, 20, 30, 40, 50, 60, 70, 80, 90]
	numberOfRrh = [4, 5, 6, 7, 8, 9, 10, 20, 30]

	if const == 's':
		return numberOfRrh, compression

	elif const == 'n':
		return speed, compression

	return speed, numberOfRrh


def main():
	name, const = parseCommand()

	x, y = getFactors(const)

	for i in x:
		for j in y:
			os.system('scavetool x ../simulations/results/'+name+'-' + str(i) + ',' + str(j) + '-*.sca -o ../csv/'+name+'-' + str(i) + '-' + str(j) +'.csv')


if __name__ == "__main__":
    main()