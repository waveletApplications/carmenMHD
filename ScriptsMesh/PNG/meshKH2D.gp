set terminal png 
set output "KH_2D_L9_eps.png"

set xlabel "x"
set ylabel "y"
set xr [0:1]
set yr [-1:1]
set size ratio 2
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh.dat" using 1:2 notitle pt 0 lt -1
