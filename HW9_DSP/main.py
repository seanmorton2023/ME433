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

def gen_subplot(filter_function, char, axs):
    '''import each signal and plot fft of each;
    apply filter if applicable

    filter_function: type = Python function. if None, just plot original data
    char: the letter corresponding to the signal
    axs: the subplots we're plotting to
    '''
    #obtain FFT
    sig = pd.read_csv('sig' + char + '.csv').to_numpy()
    t, s = (sig.transpose()[0], sig.transpose()[1])
    frq, Y = fft_data(t,s)

    #plot
    (ax1, ax2) = axs
    plot_time_and_fft(t, s, frq, Y, (ax1, ax2), 'k')

    if filter_function:
        s_filt = filter_function(s)
        frq_new, Y_new = fft_data(t, s_filt)
        plot_time_and_fft(t, s_filt, frq_new, Y_new, (ax1, ax2), 'r')

    ###

def gen_fig(title, output_filepath, fir=False, filter=None):
    '''Code repeated across the MAV and IIR functions; function added for ease of editing.

    title: the title of the overall plot
    output_filepath: where the figure gets saved
    filter: the function applied to the signal to filter it
    '''
    fig, axs = plt.subplots(nrows=2, ncols=3, figsize=(17, 8))
    fig.suptitle(title)
    for i, char in enumerate(['A', 'B', 'D']):
        axs_temp = (axs[0,i], axs[1,i])

        if fir: #where every signal has a diff. filter
            filter_res = conv_filters[i]
            #necessarily complex so I can use {} for TEX notation rather than for fstring
            subtitle = 'Signal %s: (f_{L}, b_{L}) = (%d, %d)  Hz' \
                        % (char, conv_data[i][0], conv_data[i][1]) 
            subtitle = '$' + subtitle + '$'
            axs_temp[0].set_title(subtitle)

        elif not filter:
            gen_subplot(None, char, axs_temp)
            axs_temp[0].set_title(f'Signal {char}')
            continue

        else:
            filter_res = filter
            axs_temp[0].set_title(f'Signal {char}')

        gen_subplot(filter_res, char, axs_temp)

    #limit visible area of graph
    axs[0, 0].set_xlim([0.64, 1])
    axs[0, 2].set_xlim([3,10])

    #export
    plt.savefig(output_filepath)


if __name__ == '__main__':
    A = 0.9 #for IIR
    figs = []

    print("Working...\n")

    import hw9_filters
    hw9_filters.n_pts_mav = 30 #like "extern", in C
    hw9_filters.iir_scalar = A
    conv_filters = [convolve_A, convolve_B, convolve_D]
    conv_data = [(100,100), (33,33), (10,4)]
    
    #original signal, figure 0
    gen_fig('Original Signals + FFT', 'out/original.png', filter=None)

    #MAV, figures 1-3
    title_mav = f"Filter: MAV; Datapoints avg'd: {hw9_filters.n_pts_mav}"
    gen_fig(title_mav, 'out/mav.png', filter=mav)

    #IIR, figures 4-6
    title_iir = f"Filter: IIR; Weights (A,B): {(A, round(1-A, 2))}"
    gen_fig(title_iir, 'out/iir.png', filter=iir)

    #FIR, figs 7-9
    title_fir = f"Filter: FIR; # Coefficients: 461"
    gen_fig(title_fir, 'out/fir.png', fir=True)
    
    print("Figures saved to /out/ folder.")
