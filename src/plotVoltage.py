import numpy as np
import matplotlib.pylab as plt


def plotVoltage(t, y):
    fig = plt.figure(figsize=(10, 10))
    ax = fig.add_subplot(111)
    ax.plot(t, y, 'k', lw=2)


if __name__ == '__main__':
    t = np.genfromtxt('time.dat')
    y = np.genfromtxt('solution.dat')
    s = np.genfromtxt('stimuli.dat')
    n = 10

    if 0:
        plotVoltage(t[n:], y[0, n:])
        plotVoltage(t[n:], y[1, n:])
    if 1:
        fig = plt.figure()
        ax = fig.add_subplot(111)
        ax.plot(t[n:], y[0, n:], 'r', lw=1.5)
        ax.plot(t[n:], y[1, n:], 'b', lw=1.5)
        ax.plot(t[n:], s[0, n:] - 28, 'k')

    plt.show()
