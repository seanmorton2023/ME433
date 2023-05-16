# Your assignment: Make an array with 1024 elements. Into the array, sum 3 sine waves each with a different frequency. Take an FFT of the array and plot the output. Upload your code and a screenshot of the plot in a folder called HW11 in your repo.

from ulab import numpy as np  # to get access to ulab numpy functions

def fft_data(t,s):
    '''Calculates and returns arrays of frequencies and their magnitudes
    for the sake of plotting an FFT graph.
    '''
    Ts = t[-1] / len(t)
    Fs  = 1.0/Ts

    y = s # the data to make the fft from
    n = len(y) # length of the signal
    k = np.arange(n)
    T = n/Fs
    frq = k/T # two sides frequency range
    frq = frq[0:int(n/2)] # one side frequency range, modified for CircuitPython
    (re, im) = np.fft.fft(y) #different from how ndarrays work on regular python - in regular python it's one array w/ real + im components
    complex_abs = (re**2 + im**2) ** 0.5
    Y = complex_abs/n # fft computing and normalization
    Y = Y[0:int(n/2)] #modified for CircuitPython
    return frq, Y
    
def gen_data():
    #make an array with 1024 elements
    arr1 = np.zeros(1024)

    #sum 3 sine waves into it with diff. freqs
    t_arr = np.linspace(0, 5, 1024)
    arr1 = arr1 + np.sin(4*2*np.pi*t_arr)
    arr1 = arr1 + np.sin(10*2*np.pi*t_arr)
    arr1 = arr1 + np.sin(40*2*np.pi*t_arr)

    #take the FFT of the output
    frq, Y = fft_data(t_arr, arr1)
    return t_arr, arr1, frq, Y
    
def send_data(arr, name):
    print(name + "_start")
    for entry in arr:
        print(entry)
    print(name + "_end")
    
#save data to CSV files and plot on local PC
t, s, frq, Y = gen_data()

#the jank way: send all the arrays over serial
input("Send a command over Serial when ready to receive data. ")
send_data(t, "time")
send_data(s, "sig")
send_data(frq, "frq")
send_data(Y, "fft")


    

                
