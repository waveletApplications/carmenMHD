set terminal postscript monochrome portrait "Helvetica" 22
set output "R1_2D_L9_eps.eps"

set xlabel "x"
set ylabel "Level"
set xr [-0.5:0.5]
set yr [3:10]
set size square
set xtic auto                          # set xtics automatically
set ytics 4,1,9

plot "Mesh.dat" using 1:3 notitle pt 0
set output "R1_2D_L9_eps_0.eps"

set xlabel "x"
set ylabel "Level"
set xr [-0.5:0.5]
set yr [3:10]
set size square
set xtic auto                          # set xtics automatically
set ytics 4,1,9

plot "Mesh_0.dat" using 1:3 notitle pt 0 pointsize 0.01

set terminal png 
set output "R1_2D_L9_eps.png"

set xlabel "x"
set ylabel "Level"
set xr [-0.5:0.5]
set yr [3:10]
set size square
set xtic auto                          # set xtics automatically
set ytics 4,1,9

plot "Mesh.dat" using 1:3 notitle pt 0 lt -1
set output "R1_2D_L9_eps_0.png"

set xlabel "x"
set ylabel "Level"
set xr [-0.5:0.5]
set yr [3:10]
set size square
set xtic auto                          # set xtics automatically
set ytics 4,1,9

plot "Mesh_0.dat" using 1:3 notitle pt 0 lt -1


