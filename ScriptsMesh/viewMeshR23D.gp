set terminal postscript monochrome portrait "Helvetica" 22
set output "R2_3D_L9_eps_xy.eps"

set xlabel "x"
set ylabel "y"
set xr [-1:1]
set yr [-1:1]
set size square
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh.dat" using 1:2 notitle pt 0

set output "R2_3D_L9_eps_yz.eps"

set xlabel "y"
set ylabel "z"
set xr [-1:1]
set yr [-1:1]
set size square
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh.dat" using 2:3 notitle pt 0

set output "R2_3D_L9_eps_zx.eps"

set xlabel "z"
set ylabel "x"
set xr [-1:1]
set yr [-1:1]
set size square
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh.dat" using 3:1 notitle pt 0

set output "R2_3D_L9_eps_xy_0.eps"

set xlabel "x"
set ylabel "y"
set xr [-1:1]
set yr [-1:1]
set size square
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh_0.dat" using 1:2 notitle pt 0 pointsize 0.01

set output "R2_3D_L9_eps_yz_0.eps"

set xlabel "y"
set ylabel "z"
set xr [-1:1]
set yr [-1:1]
set size square
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh_0.dat" using 2:3 notitle pt 0 pointsize 0.01

set output "R2_3D_L9_eps_zx_0.eps"

set xlabel "z"
set ylabel "x"
set xr [-1:1]
set yr [-1:1]
set size square
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh_0.dat" using 3:1 notitle pt 0 pointsize 0.01

set terminal png 
set output "R2_3D_L9_eps_xy.png"

set xlabel "x"
set ylabel "y"
set xr [-1:1]
set yr [-1:1]
set size square
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh.dat" using 1:2 notitle pt 0

set output "R2_3D_L9_eps_yz.png"

set xlabel "y"
set ylabel "z"
set xr [-1:1]
set yr [-1:1]
set size square
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh.dat" using 2:3 notitle pt 0

set output "R2_3D_L9_eps_zx.png"

set xlabel "z"
set ylabel "x"
set xr [-1:1]
set yr [-1:1]
set size square
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh.dat" using 3:1 notitle pt 0

set output "R2_3D_L9_eps_xy_0.png"

set xlabel "x"
set ylabel "y"
set xr [-1:1]
set yr [-1:1]
set size square
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh_0.dat" using 1:2 notitle pt 0 pointsize 0.01

set output "R2_3D_L9_eps_yz_0.png"

set xlabel "y"
set ylabel "z"
set xr [-1:1]
set yr [-1:1]
set size square
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh_0.dat" using 2:3 notitle pt 0 pointsize 0.01

set output "R2_3D_L9_eps_zx_0.png"

set xlabel "z"
set ylabel "x"
set xr [-1:1]
set yr [-1:1]
set size square
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically

plot "Mesh_0.dat" using 3:1 notitle pt 0 pointsize 0.01


