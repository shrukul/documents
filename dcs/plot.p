set key outside
set yrange [1500:3500]
set xrange [1:2500]
set xlabel 'Rank'
set ylabel 'Minimal Tour Path'
set xtics 500
set ytics 500
set grid
set terminal png
set output 'Graph.png'
plot 'file.txt' using 35:38 with lines title "Distance Curve" lt rgb "#000000"
