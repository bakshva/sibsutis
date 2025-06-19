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
    ax.set_title("Время от кол-ва потоков")
    ax.set(xlabel="Количество потоков", ylabel="Время выполнения")
    ax.xaxis.set_tick_params(direction='in', which='both')
    ax.yaxis.set_tick_params(direction='in', which='both')

    try:
        # Чтение данных из первого файла (res1.txt)
        data1 = np.loadtxt('res1.txt')
        threads1 = data1[:, 0]
        times1 = data1[:, 1]
        
        # Чтение данных из второго файла (res2.txt)
        data2 = np.loadtxt('res2.txt')
        threads2 = data2[:, 0]
        times2 = data2[:, 1]
        
        # Построение графиков
        ax.plot(threads1, times1, '-o', markersize=3, linewidth=1, label="n=10^8")
        ax.plot(threads2, times2, '-s', markersize=3, linewidth=1, label="n=10^7")
        
        # Настройка осей
        ax.set_xticks(np.unique(np.concatenate((threads1, threads2))))
        ax.grid(True, linestyle='--', alpha=0.5)
        
        plt.tight_layout()
        ax.legend()
        fig.savefig('time_combined.png', dpi=300)
        print("График сохранен")
        
    except Exception as e:
        print(f"Ошибка при обработке файлов: {e}")

if __name__ == "__main__":
    draw()
