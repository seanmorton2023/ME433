#import csv
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt # for plotting

#alt method: use Pandas to import data
signal_csv = 'sigA.csv'
data = pd.read_csv(signal_csv).to_numpy()
print(data)