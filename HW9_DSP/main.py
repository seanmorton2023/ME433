import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

#functions from fft code
from python_fft import *

#import each signal and plot fft of each
sigs = []
figs = []
for el in ['A','B','D']:
    sigs.append(pd.read_csv('sig' + el + '.csv').to_numpy())

i = 0
for sig in sigs: 
    print(f"signal {i}:")
    t, s = (sig.transpose()[0], sig.transpose()[1])
    frq, Y = fft_data(t,s)
    figs.append(plot_time_and_fft(t, s, frq, Y))
    print('\n')
    i += 1

plt.show()
