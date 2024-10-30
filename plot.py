import matplotlib.pyplot as plt
import numpy as np
import math

def plot_monte_carlo():
    data = np.genfromtxt(fname = "file.txt", dtype = float, delimiter = ',').transpose()
    fig, ax = plt.subplots()
    ax.set_xscale('log')
    ax.plot(data[0], data[1], label='Monte Carlo estimate')
    ax.plot(data[0], np.ones_like(data[0])*math.pi, label='π from math.pi')
    ax.errorbar(data[0], data[1], data[2], alpha=0.3, label='1 s.t.d.')
    #ax.errorbar(data[0], data[1], data[2]*2, alpha=0.3, label='2 s.t.d.')
    #ax.errorbar(data[0], data[1], data[2]*3, alpha=0.3, label='3 s.t.d.')
    ax.legend()
    fig.savefig("plot")
    plt.show()

if __name__ == "__main__":
    plot_monte_carlo()
    