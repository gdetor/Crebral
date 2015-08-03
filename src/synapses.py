import numpy as np


def synapticWeights(numNeurons):
    e, i = numNeurons*80/100, numNeurons*20/100
    exc = np.random.randint(0, 2, (e, numNeurons))
    inh = np.random.randint(-1.0, 0, (i, numNeurons))
    W = np.vstack([exc, inh])
    np.fill_diagonal(W, 0)
    return W


if __name__ == '__main__':
    W = synapticWeights(10)
    print W
    np.savetxt('synapses.dat', W)
