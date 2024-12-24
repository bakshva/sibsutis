set terminal png size 1000,800
set output 'add_operation_graph.png'
set title "Insert Time vs Tree Size"
set xlabel "Size of Tree (Number of Nodes)"
set ylabel "Insert Time (nanoseconds)"
set grid
plot "add_times.txt" using 1:2 with linespoints title "Insert Time"
