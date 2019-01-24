import os

def parseCommand():
	if (len(sys.argv) < 3):
		sys.exit()

	if (sys.argv[1] != '-name'):
		sys.exit()

	return sys.argv[2]

def main():
	name = parseCommand()
	speed = [6667, 3333, 2222, 1667, 1333, 1111, 952, 833, 741]
	compression = [10, 30, 50, 70, 90]
	numberOfRrh = [4, 5, 6, 10, 20, 30, 50]

	#for s in speed:
	for c in compression:
		for n in numberOfRrh:
			os.system('scavetool x ../simulations/results/'+name+'-' + str(c) + ',' + str(n) + '-*.sca -o ../csv/'+name+'-' + str(c) + '-' + str(n) +'.csv')


if __name__ == "__main__":
    main()