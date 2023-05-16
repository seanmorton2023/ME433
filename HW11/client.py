def plot_time_and_fft(t, s, frq, Y, axs, c):
    '''Simply plots the time-domain and frequency-domain data for our signal on one plot
    '''
    (ax1, ax2) = axs
    ax1.plot(t,s,c=c)
    ax1.set_xlabel('Time')
    ax1.set_ylabel('Amplitude')
    ax2.loglog(frq,Y,c=c) # plotting the fft
    ax2.set_xlabel('Freq (Hz)')
    ax2.set_ylabel('|Y(freq)|')
    

def gen_fig(output_filepath):
    '''Code repeated across the MAV and IIR functions; function added for ease of editing.

    title: the title of the overall plot
    output_filepath: where the figure gets saved
    filter: the function applied to the signal to filter it
    '''
    t, s, frq, Y = gen_data()  
    fig, (ax1, ax2) = plt.subplots(nrows=2, ncols=1) #figsize = (,) is another param
    
    fig.suptitle("Signal and FFT - CircuitPython")
    ax1.set_title("Signal")
    ax2.set_title("FFT")
    
    # #limit visible area of graph
    # axs[0, 0].set_xlim([0.64, 1])
    # axs[0, 2].set_xlim([3,10])

    #export
    plt.savefig(output_filepath)

#plot the output
gen_fig("fig_out.png")