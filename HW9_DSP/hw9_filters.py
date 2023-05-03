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