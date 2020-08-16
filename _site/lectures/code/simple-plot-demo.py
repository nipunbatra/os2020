from datetime import datetime
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from random import randrange
import psutil

x_data, y_data = [], []

figure = plt.figure()
line, = plt.plot_date(x_data, y_data, '-')

def update(frame):
    x_data.append(datetime.now())
    y_data.append(psutil.cpu_percent())
    
    line.set_data(x_data, y_data)
    figure.gca().relim()
    figure.gca().set_ylabel("CPU %")
    figure.gca().set_xlabel("Time")
    figure.gca().autoscale_view()
    #x_data = x_data[:100]
    #y_data = y_data[:100]
    return line,

animation = FuncAnimation(figure, update, interval=200)

plt.show()
