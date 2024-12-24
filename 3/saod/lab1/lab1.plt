set title "Зависимость высоты BR-дерева от количества узлов"
set xlabel "Количество узлов"
set ylabel "Высота дерева"
set grid

# Настройка отображения точек и линий на графике
set style data linespoints
set pointsize 1
set term png
set output "tree_height_data.png"

# Чтение данных из файла и построение графика
plot "tree_height_data.txt" using 1:2 title "Высота дерева" with linespoints