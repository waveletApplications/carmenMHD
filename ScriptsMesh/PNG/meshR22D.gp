set terminal png 
set output "R2_2D_L9_eps.png"

set xlabel "x"
set ylabel "y"
set xr [-1:1]
set yr [-1:1]
set size square
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh.dat" using 1:2 notitle pt 0 lt -1
