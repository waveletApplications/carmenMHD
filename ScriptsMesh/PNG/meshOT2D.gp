set terminal png
set output "OT_2D_L9_eps.png"

set xlabel "x"
set ylabel "y"
set xr [0:2*pi]
set yr [0:2*pi]
set size square
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh.dat" using 1:2 notitle pt 0 lt -1

