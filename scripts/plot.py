import sys
import pandas as pd
import matplotlib
import math
import statistics as stat
matplotlib.use('TkAgg')
from matplotlib import rcParams
rcParams['font.family'] = 'serif'
import matplotlib.pyplot as plt

def parseCommand():
    distributions = ['exp', 'log']
    numberOfRRH = [2, 5, 10]

    if len(sys.argv) < 5:
        return None, None
    
    if sys.argv[1] != '-d' or sys.argv[2] not in distributions or sys.argv[3] != '-n' or int(sys.argv[4]) not in numberOfRRH:
        return None, None
        
    if sys.argv[2] == 'exp':
        return 'exponential', sys.argv[4]

    return 'lognormal', sys.argv[4]


#-------------------#
#       MAIN        #
#-------------------#
 
def main():
    d, n = parseCommand()
    if d is None:
        print('python plot.ly -d [exp|log] -n [2|5|10]')
        sys.exit(0)
            
    rho = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]
    files = [6667, 3333, 2222, 1667, 1333, 1111, 952, 833, 741]

    z = 2.576 # 99% for CI
    repetitions = 10

    df = []
    sheets_values = []
    mean_delay_rho = []
    std_dev_delay_rho = []
    n_values = []
    errors = []

    for x in files:
        filename = '../csv/'+d+'-'+str(x)+'-'+str(n)+'.csv'
        print('reading %s ...' % filename)
        data = pd.read_csv(filename, header=None, usecols=[1, 3, 5, 7, 9, 11, 13, 15, 17, 19], skiprows=1)
        df.append(pd.DataFrame(data))

    for i, sheet in enumerate(df):
        print('merge values for df[%d]...' % i)
        sheet_values = []
        for col in sheet.columns:
            for v in sheet[col]:
                if not math.isnan(v):
                    sheet_values.append(v)
        #print(sheet_values)
        sheets_values.append(sheet_values)

    for i, x in enumerate(sheets_values):
        print('computing mean and stdDev for rho = %.1f...' % ((i+1)*0.1))
        mean_delay_rho.append(stat.mean(x))
        std_dev_delay_rho.append(stat.stdev(x))
        n_values.append(int(len(x))/repetitions)

    for stdDev, n in zip(std_dev_delay_rho, n_values):
        errors.append(stdDev/math.sqrt(n)*z)

    plt.errorbar(rho, mean_delay_rho, errors, linestyle='--', marker='*')
    plt.xlabel('rho')
    plt.ylabel('Delay (s)')
    plt.title('Mean delay depending on utilization')
    plt.grid(linestyle='--')
    plt.show()

if __name__ == "__main__":
    main()
