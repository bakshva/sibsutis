set terminal pngcairo size 900,600 enhanced font 'Arial,12'
set output 'quicksort_speedup.png'

set title "Ускорение параллельного QuickSort"
set xlabel "Размер массива (число элементов)"
set ylabel "Ускорение (Speedup)"
set grid
set logscale x 10
set key left top

# Время последовательной версии для разных размеров массива
seq_time(x) = (x == 100000) ? 0.009278 : \
              (x == 500000) ? 0.050018 : \
              (x == 1000000) ? 0.103415 : \
              (x == 5000000) ? 0.463549 : \
              (x == 10000000) ? 0.913700 : 1/0

# Стили для графиков
set style line 1 lc rgb '#FF00FF' lw 2 pt 7 ps 1.5  # фиолетовый
set style line 2 lc rgb '#FFA500' lw 2 pt 9 ps 1.5  # оранжевый
set style line 3 lc rgb '#D62728' lw 2 pt 5 ps 1.5  # красный
set style line 4 lc rgb '#1F77B4' lw 2 pt 13 ps 1.5 # синий

# Пороговые значения
thresholds = "100 1000 10000 50000"

plot for [i=1:4] \
     '< grep -E "^[0-9]+[ ]+'.word(thresholds, i).'[ ]+" quicksort_results.txt | sort -n' \
     using 1:(seq_time($1)/$3) with linespoints ls i \
     title sprintf("Порог = %s", word(thresholds, i))