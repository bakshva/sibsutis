set terminal png size 1000,800
set output 'remove_operation_graph.png'
set title "Delete Time vs Tree Size"
set xlabel "Size of Tree (Number of Nodes)"
set ylabel "Delete Time (nanoseconds)"
set grid
plot "remove_times.txt" using 1:2 with linespoints title "Delete Time"
