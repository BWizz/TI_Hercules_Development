"""
A simple example of an animated plot
"""
import numpy as m
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serial

ser = serial.Serial('COM5')
ser.baudrate = 115200
ser.bytesize = 8
ser.parity='N'
ser.stopbits=1


plt.ion()
figure = plt.figure()
plt.plot([0], [0],'.')
ax = plt.gca() # get axis handle
lines = ax.lines[0]
ydata = [None]*1000
xdata = [None]*1000
print('Begin')
def plot_data():
    try:
        x = ser.readline().strip()
        A = x.decode().split(',')
        #print(len(A))
        if len(A) == 3:
            r = float(A[0])
            a = float(A[1])
            if a > 0 and a < 360:
                X= r* m.cos(a*3.14 / 180)
                Y= r* m.sin(a*3.14 / 180)
                lines.set_xdata(m.append(lines.get_xdata(), X))
                lines.set_ydata(m.append(lines.get_ydata(), Y))
            #Need both of these in order to rescale
            ax.relim()
            ax.autoscale_view()
            #We need to draw *and* flush
            figure.canvas.draw()
            figure.canvas.flush_events()
        else:
            print('Nothing To Append')
    except:
        print('Error')
        pass

while 1:
    plot_data()
ser.close()
