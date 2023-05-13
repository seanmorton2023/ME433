import matplotlib.pyplot as plt
import numpy as np

# Create some data
x = np.linspace(0, 10, 100)
y1 = np.sin(x)
y2 = np.cos(x)
y3 = np.tan(x)
y4 = np.exp(x)
y5 = np.log(x)
y6 = np.sqrt(x)

# Create the figure and axes objects
fig, axs = plt.subplots(nrows=2, ncols=3, figsize=(12, 8))

# Plot the data on the axes objects
axs[0, 0].plot(x, y1)

axs[0, 1].plot(x, y2)
axs[0, 1].set_title('Cos(x)')
axs[0, 2].plot(x, y3)
axs[0, 2].set_title('Tan(x)')
axs[1, 0].plot(x, y4)
axs[1, 0].set_title('Exp(x)')
axs[1, 1].plot(x, y5)
axs[1, 1].set_title('Log(x)')
axs[1, 2].plot(x, y6)
axs[1, 2].set_title('Sqrt(x)')

# Add a suptitle for the entire figure
fig.suptitle('Six Different Plots')

# Show the figure
plt.show()

