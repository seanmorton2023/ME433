import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

#functions from fft code
from python_fft import *
from hw9_filters import *



def main(filter_function, filtername, el, fig, col):
    '''import each signal and plot fft of each;
    apply filter if applicable

    filter_function: type = Python function
    filtername: type = string; just the name of the filter
    fig: a figure to plot the signals on
    col: the column of the figure to plot signals on

    '''
    #obtain FFT
    sig = pd.read_csv('sig' + el + '.csv').to_numpy()
    t, s = (sig.transpose()[0], sig.transpose()[1])
    frq, Y = fft_data(t,s)
    s_filt = filter_function(s)
    frq_new, Y_new = fft_data(t, s_filt)

    #plot
    (ax1, ax2) = plot_time_and_fft(t, s, frq, Y, (ax1, ax2), 'k')
    (ax1, ax2) = plot_time_and_fft(t, s_filt, frq_new, Y_new, (ax1, ax2), 'r')
    title = f"Filter: {filtername}, {str(titledata)}"
    fig.suptitle(title)
    return fig


if __name__ == '__main__':
    A = 0.9 #for IIR
    figs = []

    import hw9_filters
    hw9_filters.n_pts_mav = 30 #like "extern", in C
    hw9_filters.iir_scalar = A
    
    #figs 1-3
    fig, axs = plt.subplots(2, 3)
    for i, el in enumerate(['A', 'B', 'D']):
        figs.append(main(mav, "MAV", hw9_filters.n_pts_mav, el, i))

    #figs 4-6
    for el in ['A', 'B', 'D']:
        figs.append(main(iir, "IIR", (A, round(1-A, 2) ), el))

    #figs 7-9
    figs.append(main(convolve_A, "FIR", (100,100), 'A'))
    figs.append(main(convolve_B, "FIR", (33,33), 'B'))
    figs.append(main(convolve_D, "FIR", (10,4), 'D'))
    plt.show()

'''
cutoff freqs needed:
fig1: peak at 25Hz -->cutoff 30Hz
fig2: peak at 9Hz -->cutoff 10Hz
fig3: peak at 30Hz (slight.) -->cutoff 50Hz

sampling rates:
10000Hz
3300Hz
400Hz

FIIIR settings:
sigA: 10000Hz sampling rate, 100Hz cutoff, 100Hz transition bandwidth, Blackman filter
sigB: 3300Hz sampling rate, 33Hz cutoff, 33Hz transition bandwidth, Blackman filter


'''