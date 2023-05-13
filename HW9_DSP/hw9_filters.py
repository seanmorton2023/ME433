import numpy as np
import pandas as pd

def mav(s):
    '''Compute moving average of an array, and return a new array based on this
    filtered data.
    
    s: array to filter
    (global) n_pts_mav: number of points moving average is based on
    '''
    global n_pts_mav
    out = []
    mav_array = np.zeros(n_pts_mav)

    for i, curr in enumerate(s):
        mav_array[i%n_pts_mav] = curr
        if i >= n_pts_mav:           
            out.append(np.average(mav_array))
        else:
            #match the size of the original array
            out.append(0)

    return out

def iir(s):
    '''Low-pass filter the data using an "infinite-impulse response",
    or in other words, a scalar times previous data + (1-scalar) * new data.
    Commonly used discrete-time filter we used in RDS.
    '''
    global iir_scalar
    (A, B) = (iir_scalar, 1 - iir_scalar)
    out = []

    for i, curr in enumerate(s):
        if i > 0:
            #this notation isn't as pretty as it is with pure array indexing
            next = A * out[i-1] + B*curr
            out.append(next)
        else:
            out.append(0)

    return out

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
    return np.convolve(sigA, h_sigA)

def convolve_B(sigB):

    # Configuration.
    fS_sigB = 3300  # Sampling rate.
    fL_sigB = 33  # Cutoff frequency.
    N_sigB = 461  # Filter length, must be odd.

    # Compute sinc filter.
    h_sigB = np.sinc(2 * fL_sigB / fS_sigB * (np.arange(N_sigB) - (N_sigB - 1) / 2))

    # Apply window.
    h_sigB *= np.blackman(N_sigB)

    # Normalize to get unity gain.
    h_sigB /= np.sum(h_sigB)

    # Applying the filter to a signal s can be as simple as writing
    return np.convolve(sigB, h_sigB)

def convolve_D(sigD):
    # Example code, computes the coefficients of a low-pass windowed-sinc filter.

    # Configuration.
    fS_sigD = 400  # Sampling rate.
    fL_sigD = 10  # Cutoff frequency. 32+155 was good.
    N_sigD = 461  # Filter length, must be odd.

    # Compute sinc filter.
    h_sigD = np.sinc(2 * fL_sigD / fS_sigD * (np.arange(N_sigD) - (N_sigD - 1) / 2))

    # Apply window.
    h_sigD *= np.blackman(N_sigD)

    # Normalize to get unity gain.
    h_sigD /= np.sum(h_sigD)

    # Applying the filter to a signal s can be as simple as writing
    return np.convolve(sigD, h_sigD)