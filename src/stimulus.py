import numpy as np


def pulse(duration, numNeurons, amplitude, t_init=0, t_final=1,
          targets=[]):
    x = np.zeros((numNeurons, duration))

    x[targets, t_init:t_final] = amplitude
    return x


if __name__ == '__main__':
    # import matplotlib.pylab as plt

    # p = pulse(2000, 2, 11.0/3.0, 0, 1500, [0])
    p = np.zeros((2, 5000))
    p[0, :3000] = 6.0
    # p[:800] = 5.0
    # p[1500:] = 5.0

    np.savetxt('stimuli.dat', p)
