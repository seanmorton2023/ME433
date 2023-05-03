import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

#functions from fft code
from python_fft import *
from hw9_filters import *

def main(filter_function, filtername, titledata):
    '''import each signal and plot fft of each;
    apply filter if applicable

    filter_function: type = Python function
    filtername: type = string; just the name of the filter
    titledata: type = any; will get converted to string
    '''
    figs = []
    for i, el in enumerate(['A','B','D']):
        #obtain FFT
        sig = pd.read_csv('sig' + el + '.csv').to_numpy()
        t, s = (sig.transpose()[0], sig.transpose()[1])
        frq, Y = fft_data(t,s)

        #plot
        #fig, (ax1, ax2, ax3) = plt.subplots(3, 1)
        fig, (ax1, ax2) = plt.subplots(2, 1)

        fig, (ax1, ax2) = plot_time_and_fft(t, s, frq, Y, fig, (ax1, ax2), 'k')
        if filter_function:
            frq_new, Y_new = fft_data(t, filter_function(s))
            fig, (ax1, ax2) = plot_time_and_fft(t, filter_function(s), \
                                        frq_new, Y_new, fig, (ax1, ax2), 'r')
            title = f"Filter: {filtername}, {str(titledata)}"
        else:
            title = "Original signal"

        fig.suptitle(title)
        figs.append(fig)




if __name__ == '__main__':
    A = 0.9 #for IIR

    import hw9_filters
    hw9_filters.n_pts_mav = 30 #like "extern", in C
    hw9_filters.iir_scalar = A
    
    main(mav, "MAV", hw9_filters.n_pts_mav)
    main(iir, "IIR", (A, round(1-A, 2) ) )
    plt.show()

'''
cutoff freqs needed:
fig1: peak at 25Hz -->cutoff 30Hz
fig2: peak at 9Hz -->cutoff 10Hz
fig3: peak at 30Hz (slight.) -->cutoff 50Hz
'''