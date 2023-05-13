import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

from helpers import *
from hw9_filters import *

'''
FIIIR website settings for FIR signal:
sigA: 10000Hz sampling rate, 100Hz cutoff, 100Hz transition bandwidth, Blackman filter
sigB:  3300Hz sampling rate,  33Hz cutoff,  33Hz transition bandwidth, Blackman filter
sigD:   400Hz sampling rate,  10Hz cutoff,   4Hz transition bandwidth, Blackman filter
'''

def main(filter_function, el, fig, axs):
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
    (ax1, ax2) = axs
    (ax1, ax2) = plot_time_and_fft(t,      s,     frq,     Y, (ax1, ax2), 'k')
    (ax1, ax2) = plot_time_and_fft(t, s_filt, frq_new, Y_new, (ax1, ax2), 'r')
    return fig

def gen_fig(title, filter=None):
    '''Code repeated across the MAV and IIR functions; function added for ease of editing.
    '''
    fig, axs = plt.subplots(nrows=2, ncols=3, figsize=(17, 8))
    fig.suptitle(title)
    for i, el in enumerate(['A', 'B', 'D']):
        axs_temp = (axs[0,i], axs[1,i])

        if not filter: #case of FIR, where everysignal has a diff. filter
            filter_res = conv_filters[i]
            #necessarily complex so I can use {} for TEX notation rather than for fstring
            subtitle = 'Signal %s: (f_{L}, b_{L}) = (%d, %d)  Hz' \
                        % (el, conv_data[i][0], conv_data[i][1]) 
            subtitle = '$' + subtitle + '$'
            axs_temp[0].set_title(subtitle)
        else:
            filter_res = filter
            axs_temp[0].set_title(f'Signal {el}')

        main(filter_res, el, fig, axs_temp)

    #limit visible area of graph
    axs[0, 0].set_xlim([0.64, 1])
    axs[0, 2].set_xlim([3,10])


if __name__ == '__main__':
    A = 0.9 #for IIR
    figs = []

    import hw9_filters
    hw9_filters.n_pts_mav = 30 #like "extern", in C
    hw9_filters.iir_scalar = A
    conv_filters = [convolve_A, convolve_B, convolve_D]
    conv_data = [(100,100), (33,33), (10,4)]
    
    #MAV, figures 1-3
    title_mav = f"Filter: MAV; Datapoints avg'd: {hw9_filters.n_pts_mav}"
    gen_fig(title_mav, mav)

    #IIR, figures 4-6
    title_iir = f"Filter: IIR; Weights: {(A, round(1-A, 2))}"
    gen_fig(title_iir, iir)

    #FIR, figs 7-9
    title_fir = f"Filter: FIR; # Coefficients: 461"
    gen_fig(title_fir)
    plt.show()
