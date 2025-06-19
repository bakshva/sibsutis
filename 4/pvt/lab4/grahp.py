#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
from collections import defaultdict

def draw():
    plt.rcParams["legend.markerscale"] = 2.0
    plt.rcParams['font.family'] = 'DejaVu Sans'
    plt.rcParams['font.size'] = '12'
    plt.rcParams["legend.loc"] = "upper left"
    plt.rcParams["legend.fontsize"] = "8"
    cm = 1/2.54  
    fig = plt.figure(figsize=(15*cm, 10*cm))
    ax = fig.add_subplot(111)
    ax.set_title("Ускорение относительно последовательной версии")
    ax.set(xlabel="Количество потоков", ylabel="Коэффициент ускорения")
    ax.xaxis.set_tick_params(direction='in', which='both')
    ax.yaxis.set_tick_params(direction='in', which='both')

    try:
        # Чтение данных и обработка
        data = np.genfromtxt('res.txt', delimiter=',', dtype=str)
        
        # Извлечение времени последовательной версии
        serial_time = float(data[0][3])
        print(f"Базовое время Serial: {serial_time}")
        
        # Группировка данных по версиям
        versions = defaultdict(list)
        for row in data[1:]:  # пропускаем первую строку (Serial)
            ver = row[0]
            threads = int(row[1])
            speedup = serial_time / float(row[3])  # Исправленное вычисление
            versions[ver].append((threads, speedup))
        
        # Сортировка и построение графиков
        markers = ['o', 's', 'D', '^', 'v', '>']  # разные маркеры для версий
        for idx, (ver, values) in enumerate(versions.items()):
            values.sort()  # сортировка по потокам
            threads = [x[0] for x in values]
            speedups = [x[1] for x in values]
            
            ax.plot(threads, speedups, 
                     marker=markers[idx%len(markers)], 
                     linestyle='-',
                     linewidth=1,
                     markersize=4,
                     label=ver)

        # Настройка осей и сетки
        ax.set_xticks(np.unique(data[1:, 1].astype(int)))
        ax.grid(True, linestyle='--', alpha=0.5)
        ax.legend()
        
        plt.tight_layout()
        fig.savefig('speedup_corrected.png', dpi=300)
        print("График сохранен в speedup_corrected.png")
        
    except Exception as e:
        print(f"Ошибка: {e}")

if __name__ == "__main__":
    draw()