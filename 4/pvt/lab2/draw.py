#!/usr/bin/env python3

import os
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np

def draw(filenames, labels):
    plt.rcParams["legend.markerscale"] = 2.0
    plt.rcParams['font.family'] = 'DejaVu Sans'
    plt.rcParams['font.size'] = '12'
    plt.rcParams["legend.loc"] = "upper left"
    plt.rcParams["legend.fontsize"] = "8"
    cm = 1/2.54  
    fig = plt.figure(figsize=(10*cm, 7*cm))
    ax = fig.add_subplot(111)
    ax.set_title("")
    ax.set(xlabel="Количество $p$ процессов", ylabel="Ускорение")
    ax.label_outer()
    ax.xaxis.set_tick_params(direction='in', which='both')
    ax.yaxis.set_tick_params(direction='in', which='both')

    i = 0
    for (fname, datalabel) in zip(filenames, labels):
        data = np.loadtxt(fname)
        x = data[:, 1]  
        y = data[:, 2] / data[:, 3]  
        
        ax.plot(x, y, '-o', markersize=3, linewidth=1, label=datalabel)

    
    max_proc = max([np.max(np.loadtxt(fname)[:, 1]) for fname in filenames])
    ax.plot(range(2, int(max_proc)+1), range(2, int(max_proc)+1), 
            '-', c="blue", linewidth=0.5, label="Linear speedup")

    plt.tight_layout()
    ax.legend()
    fig.savefig('chart.png', dpi=300)

if __name__ == "__main__":
    draw(["pr1.dat", "pr2.dat", "pr3.dat"], ["N=15000", "N=20000", "N=25000"])