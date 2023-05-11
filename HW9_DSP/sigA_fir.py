#from __future__ import print_function
#from __future__ import division

import numpy as np
from plotter import *
import pandas as pd


def convolve_A(sigA):
    '''A convolution operation customized to signal A. Uses the "generate list using a 
    Python script" option from the FIIIR website.
    '''
    # Configuration.
    fS_sigA = 10000  # Sampling rate.
    fL_sigA = 100  # Cutoff frequency.
    N_sigA = 461  # Filter length, must be odd.

    # Compute sinc filter.
    h_sigA = np.sinc(2 * fL_sigA / fS_sigA * (np.arange(N_sigA) - (N_sigA - 1) / 2))

    # Apply window.
    h_sigA *= np.blackman(N_sigA)

    # Normalize to get unity gain.
    h_sigA /= np.sum(h_sigA)

    # Applying the filter to a signal s can be as simple as writing
    return np.convolve(s, h_sigA)

def update_function():
    '''Function to pass to FuncAnimation to occur on a regular interval, so as to
    change what's on the graph.
    '''
    global ii
    curr = sigA[ii]
    ii = ii + 1
    return curr

    #grab an extra element of the array and then convolve the entire array with the filter

if __name__ == '__main__':
        
    #fig, ax = plt.subplots()
    #plotter = Plotter(ax)

    #ani = animation.FuncAnimation(fig, plotter.update, update_function, interval=200, #ms
    #                              blit=True, cache_frame_data=False)

    #ax.set_xlabel("Samples")
    #ax.set_ylabel("Signal balue)")
    #fig.canvas.manager.set_window_title('Signal data (no convolution)')
    #fig.tight_layout()
    #plt.show()

    out = np.convolve(sigA, h_sigA)