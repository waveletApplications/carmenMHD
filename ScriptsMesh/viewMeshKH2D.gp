set terminal postscript monochrome portrait "Helvetica" 22
set output "KH_2D_L9_eps.eps"

set xlabel "x"
set ylabel "y"
set xr [0:1]
set yr [-1:1]
set size ratio 2
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh.dat" using 1:2 notitle pt 0
set output "KH_2D_L9_eps_0.eps"

set xlabel "x"
set ylabel "y"
set xr [0:1]
set yr [-1:1]
set size ratio 2
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh_0.dat" using 1:2 notitle pt 0 pointsize 0.01

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
set output "KH_2D_L9_eps_0.png"

set xlabel "x"
set ylabel "y"
set xr [0:1]
set yr [-1:1]
set size ratio 2
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh_0.dat" using 1:2 notitle pt 0 lt -1


