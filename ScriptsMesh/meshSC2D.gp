set terminal png
set output "SC_2D_L9_eps.png"

set xlabel "x"
set ylabel "y"
set xr [0:1]
set yr [0:1]
set size square
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh.dat" using 1:2 notitle pt 0 lt -1

