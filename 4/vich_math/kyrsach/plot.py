#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt

def plot_seird():
    # Читаем данные, пропуская строку разделителей
    data = np.loadtxt('output.txt', skiprows=2)
    days = data[:, 0]
    S    = data[:, 1]
    E    = data[:, 2]
    I    = data[:, 3]
    R    = data[:, 4]
    D    = data[:, 5]
    Det  = E + I

    # Создаём сетку 3x2
    fig, axs = plt.subplots(3, 2, figsize=(12, 10), sharex=True)
    axs = axs.flatten()

    # Заголовки и серии для каждой панели
    titles = [
        "S – Восприимчивое население (Susceptible)",
        "E – Зараженные в инкубационном периоде (Exposed)",
        "I – Инфицированные с симптомами (Infectious)",
        "R – Выздоровевшие (Recovered)",
        "D – Умершие (Dead)",
        "Detected – Выявленные случаи (E + I)"
    ]
    series = [S, E, I, R, D, Det]

    # Параметры линий
    marker = 'o'
    msize  = 3
    lw     = 1

    for ax, y, title in zip(axs, series, titles):
        ax.plot(days, y, marker=marker, markersize=msize, linewidth=lw)
        ax.set_title(title)
        ax.set_xlabel("Время (дни)")
        ax.set_ylabel("Численность")
        ax.grid(True, linestyle='--', alpha=0.5)
        ax.xaxis.set_tick_params(direction='in', which='both')
        ax.yaxis.set_tick_params(direction='in', which='both')

    plt.tight_layout()
    fig.savefig('seird_dynamics.png', dpi=300)
    plt.show()

if __name__ == "__main__":
    plot_seird()
