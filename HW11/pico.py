# Your assignment: Make an array with 1024 elements. Into the array, sum 3 sine waves each with a different frequency. Take an FFT of the array and plot the output. Upload your code and a screenshot of the plot in a folder called HW11 in your repo.

from ulab import numpy as np  # to get access to ulab numpy functions
#import numpy as np

import matplotlib.pyplot as plt

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
    frq = frq[range(int(n/2))] # one side frequency range
    (re, im) = np.fft.fft(y) #different from how ndarrays work on regular python - in regular python it's one array w/ real + im components
    complex_abs = (re**2 + im**2)**0.5
    Y = complex_abs/n # fft computing and normalization
    
    Y = Y[range(int(n/2))]
    return frq, abs(Y)
    
def plot_time_and_fft(t, s, frq, Y, axs, c):
    '''Simply plots the time-domain and frequency-domain data for our signal on one plot
    '''
    (ax1, ax2) = axs
    ax1.plot(t,s,c=c)
    ax1.set_xlabel('Time')
    ax1.set_ylabel('Amplitude')
    ax2.loglog(frq,Y,c=c) # plotting the fft
    ax2.set_xlabel('Freq (Hz)')
    ax2.set_ylabel('|Y(freq)|')
    
def gen_data():
    #make an array with 1024 elements
    arr1 = np.zeros(1024)

    #sum 3 sine waves into it with diff. freqs
    t_arr = np.linspace(0, 10, 1024)
    arr1 = arr1 + np.sin(t_arr)
    arr1 = arr1 + np.sin(3*t_arr)
    arr1 = arr1 + np.sin(10*t_arr)

    #take the FFT of the output
    frq, Y = fft_data(t_arr, arr1)
    return t_arr, arr1, frq, Y

def gen_fig(output_filepath):
    '''Code repeated across the MAV and IIR functions; function added for ease of editing.

    title: the title of the overall plot
    output_filepath: where the figure gets saved
    filter: the function applied to the signal to filter it
    '''
    t, s, frq, Y = gen_data()  
    fig, (ax1, ax2) = plt.subplots(nrows=2, ncols=1) #figsize = (,) is another param
    
    fig.suptitle("Signal and FFT - CircuitPython")
    ax1.set_title("Signal")
    ax2.set_title("FFT")
    
    # #limit visible area of graph
    # axs[0, 0].set_xlim([0.64, 1])
    # axs[0, 2].set_xlim([3,10])

    #export
    plt.savefig(output_filepath)

#plot the output
gen_fig("fig_out.png")