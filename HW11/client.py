import matplotlib.pyplot as plt
import serial 

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
    
def rcv_data(ser, data_name):
    '''Takes in data over Serial and returns it as arrays
    '''    
    data = []
    
    # check for the start of the array
    while True:
        print("Waiting for data: " + data_name)
        line = ser.readline().decode().strip()
        if line == data_name + '_start':
            break
            
    # check for the end of the array
    while True:
        line = ser.readline().decode().strip()
        if line == data_name + '_end':
            break
        try:
            data.append(float(line))
        except:
            data.append(line)

    return data
    

def main(output_filepath):
    '''Code repeated across the MAV and IIR functions; function added for ease of editing.

    title: the title of the overall plot
    output_filepath: where the figure gets saved
    filter: the function applied to the signal to filter it
    '''
    ser = serial.Serial('COM5', 9600)
    if(not ser.isOpen()):
        raise Exception("Error connecting to Serial")

    #receive data transmitted over Serial
    ser.write(b"Ready\r\n")

    t = rcv_data(ser, "time")
    s = rcv_data(ser, "sig")
    frq = rcv_data(ser, "frq")
    Y = rcv_data(ser, "fft") 
       
    #plot
    fig, (ax1, ax2) = plt.subplots(nrows=1, ncols=2, figsize = (12, 6))
    fig.suptitle("Signal and FFT - CircuitPython")
    ax1.set_title("Signal")
    ax2.set_title("FFT")
    ax2.grid(True, which='both')
    plot_time_and_fft(t, s, frq, Y, (ax1, ax2), 'r')
    
    #export
    print("\nSaving figure at " + output_filepath) 
    plt.savefig(output_filepath)
    
    ser.close()
    plt.show()
    #figure looks offset somehow - showing 1.6, 4, and 16 as the freqs


main('out.png')