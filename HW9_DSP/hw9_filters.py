import numpy as np

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