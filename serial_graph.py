import serial
from matplotlib import pyplot as plt
from matplotlib import animation
import numpy as np

arduino = serial.Serial('/dev/tty.usbmodem14401', 115200)

fig = plt.figure()
ax = plt.axes(xlim=(0, 50), ylim=(0, 30))
line, = ax.plot([], [], lw=2)

max_points = 50
line, = ax.plot(np.arange(max_points), 
                np.ones(max_points, dtype=np.float)*np.nan, lw=2)

def init():
    return line,

def animate(i):
    y = arduino.readline()
    y = y.decode()[:-2]
    y = float(y)

    old_y = line.get_ydata()
    new_y = np.r_[old_y[1:], y]
    line.set_ydata(new_y)
    return line,

anim = animation.FuncAnimation(fig, animate, init_func=init, frames=200, interval=20, blit=False)

plt.show()
