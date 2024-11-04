import matplotlib.pyplot as plt
import numpy as np
import math

def plot_monte_carlo():
    data = np.genfromtxt(fname = "./results/montecarlo.txt", dtype = float, delimiter = ',').transpose()
    fig, ax = plt.subplots(2)
    ax[0].set_xscale('log')
    ax[0].plot(data[0], data[1], label='Monte Carlo estimate')
    ax[0].plot(data[0], np.ones_like(data[0])*math.pi, '--r', label='π from math.pi')
    ax[0].errorbar(data[0], data[1], np.sqrt(data[2]), alpha=0.3, label='1 s.t.d.')
    #ax.errorbar(data[0], data[1], data[2]*2, alpha=0.3, label='2 s.t.d.')
    #ax.errorbar(data[0], data[1], data[2]*3, alpha=0.3, label='3 s.t.d.')
    ax[0].legend()
    ax[0].title.set_text('Monte Carlo method for π estimate')

    pi = 3.1415926535897932
    c = .3
    pi_arr = np.ones_like(data[0]) * pi
    rel_err = np.abs((data[1] - pi_arr)) / pi_arr
    ax[1].set_xscale('log')
    ax[1].set_yscale('log')
    ax[1].plot(data[0], rel_err, label='Relative error: (estimate - π) / π')
    ax[1].plot(data[0], c*np.reciprocal((np.sqrt(data[0]))), '--g', label='1/sqrt(N)')
    ax[1].legend()
    
    fig.savefig("plot")
    plt.show()

if __name__ == "__main__":
    plot_monte_carlo()
    