set key outside
set yrange [250:700]
set xrange [1:2500]
set xlabel 'Rank'
set ylabel 'Minimal Tour Path'
set xtics 500
set ytics 100
set grid
set terminal png
set output 'Graph.png'
plot 'new1.txt' using 35:38 with lines title "Distance Curve" lt rgb "#000000"
