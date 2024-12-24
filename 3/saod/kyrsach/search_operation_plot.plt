set terminal png size 1000,800
set output 'search_operation_graph.png'
set title "Search Time vs Tree Size"
set xlabel "Size of Tree (Number of Nodes)"
set ylabel "Search Time (nanoseconds)"
set grid
plot "search_times.txt" using 1:2 with linespoints title "Search Time"
