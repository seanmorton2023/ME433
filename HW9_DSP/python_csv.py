#import csv
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt # for plotting


t = [] # column 0
data1 = [] # column 1
data2 = [] # column 2

#with open('csv_file.csv') as f:
#    # open the csv file
#    reader = csv.reader(f)
#    for row in reader:
#        # read the rows 1 one by one
#        t.append(float(row[0])) # leftmost column
#        data1.append(float(row[1])) # second column
#        data2.append(float(row[2])) # third column

#for i in range(t):
#    # print the data to verify it was read
#    print(str(t[i]) + ", " + str(data1[i]) + ", " + str(data2[i]))


#alt method: use Pandas to import data
signal_csv = 'sigA.csv'
data = pd.read_csv(signal_csv).to_numpy()
print(data)

#find sampling rate
dt = data[-1][0]/data.shape[0]
freq_hz = 1/dt

