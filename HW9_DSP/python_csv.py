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
freq_samp = 1/dt

#apply fft and visualize
#data = data.reshape(data.shape[::-1])
fft_out = np.fft.fft(data)
print(fft_out)

n_pts = len(fft_out)
index_array = np.arange(n_pts)
t_final = n_pts * dt
freq_array = index_array/t_final #I don't understand this part of Marchuk's code

#print(data)
#print(len(data))
#print("Index array:")
#print(index_array)
#print(t_final)
#print("Freq array:")
#print(freq_array)

#plot freqs
print(len(freq_array))
print(len(np.abs(fft_out)))

plt.stem(freq_array, np.abs(fft_out))

