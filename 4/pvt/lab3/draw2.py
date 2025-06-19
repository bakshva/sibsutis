#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

def draw():
    plt.rcParams["legend.markerscale"] = 2.0
    plt.rcParams['font.family'] = 'DejaVu Sans'
    plt.rcParams['font.size'] = '12'
    plt.rcParams["legend.loc"] = "upper left"
    plt.rcParams["legend.fontsize"] = "8"
    cm = 1/2.54  
    fig = plt.figure(figsize=(10*cm, 7*cm))
    ax = fig.add_subplot(111)
    ax.set_title(" время от кол-ва потоков")
    ax.set(xlabel="Количество потоков", ylabel="Время выполнения")
    ax.xaxis.set_tick_params(direction='in', which='both')
    ax.yaxis.set_tick_params(direction='in', which='both')

    try:
        # Чтение данных из res1.txt (первый столбец - потоки, второй - время)
        data = np.loadtxt('res2.txt')
        threads = data[:, 0]
        times = data[:, 1]
        
        # Построение графика
        ax.plot(threads, times, '-o', markersize=3, linewidth=1, 
                label="n=10^7")
        
        # Настройка осей
        ax.set_xticks(threads)
        ax.grid(True, linestyle='--', alpha=0.5)
        
        plt.tight_layout()
        ax.legend()
        fig.savefig('time2.png', dpi=300)
        print("График сохранен")
        
    except Exception as e:
        print(f"Ошибка при обработке файла: {e}")

if __name__ == "__main__":
    draw()