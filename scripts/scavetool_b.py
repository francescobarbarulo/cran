import os
import sys

def parseCommand():
	const = ['s', 'c', 'n']

	if (len(sys.argv) != 5):
		sys.exit()

	if (sys.argv[1] != '-name' or sys.argv[3] != '-const' or sys.argv[4] not in const):
		sys.exit()

	return sys.argv[2], sys.argv[4]

def main():
	name, const = parseCommand()
	speed = [6667, 3333, 2222, 1667, 1333, 1111, 952, 833, 741]
	#compression = [10, 30, 50, 70, 90]
	compression = [0, 10, 30, 50]
	#numberOfRrh = [2, 3, 4, 5, 6, 10, 20, 30, 50]
	numberOfRrh = [2, 3, 4, 5, 6, 10]

	if const == 's':
		for n in numberOfRrh:
			for c in compression:
				os.system('scavetool x ../simulations/results/'+name+'-' + str(n) + ',' + str(c) + '-*.sca -o ../csv/'+name+'-' + str(n) + '-' + str(c) +'.csv')
	elif const == 'n':
		for s in speed:
			for c in compression:
				os.system('scavetool x ../simulations/results/'+name+'-' + str(s) + ',' + str(c) + '-*.sca -o ../csv/'+name+'-' + str(s) + '-' + str(c) +'.csv')
	else:
		for s in speed:
			for n in numberOfRrh:
				os.system('scavetool x ../simulations/results/'+name+'-' + str(s) + ',' + str(n) + '-*.sca -o ../csv/'+name+'-' + str(s) + '-' + str(n) +'.csv')


if __name__ == "__main__":
    main()