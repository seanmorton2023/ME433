import matplotlib.pyplot as plt
import numpy as np

def fft_data(t,s):
    '''Calculates and returns arrays of frequencies and their magnitudes
    for the sake of plotting an FFT graph.
    '''
    Fs = 10000 # sample rate
    Ts = 1.0/Fs; # sampling interval
    ts = np.arange(0,t[-1],Ts) # time vector
    y = s # the data to make the fft from
    n = len(y) # length of the signal
    k = np.arange(n)
    T = n/Fs
    frq = k/T # two sides frequency range
    frq = frq[range(int(n/2))] # one side frequency range
    Y = np.fft.fft(y)/n # fft computing and normalization
    Y = Y[range(int(n/2))]
    return frq, abs(Y)

def plot_time_and_fft(t, s, frq, Y, fig, subplots, c):
    '''Simply plots the time-domain and frequency-domain data for our signal on one plot
    '''
    (ax1, ax2) = subplots
    ax1.plot(t,s,c=c)
    ax1.set_xlabel('Time')
    ax1.set_ylabel('Amplitude')
    ax2.loglog(frq,Y,c=c) # plotting the fft
    ax2.set_xlabel('Freq (Hz)')
    ax2.set_ylabel('|Y(freq)|')
    return fig, (ax1, ax2)

if __name__ == '__main__':
    dt = 1.0/10000.0 # 10kHz
    # a constant plus 100Hz and 1000Hz
    t = np.arange(0.0, 1.0, dt) # 10s
    s = 4.0 * np.sin(2 * np.pi * 100 * t) + 0.25 * np.sin(2 * np.pi * 1000 * t) + 25
    
    frq, Y = fft_data(t, s)
    fig = plot_time_and_fft(t, s, frq, Y)

    plt.show()