########### POSTSCRIPT
set terminal postscript monochrome portrait "Helvetica" 22
set output "R1_3D_L8_eps_x.eps"

set xlabel "x"
set ylabel "Level"
set xr [-0.5:0.5]
set yr [3:9]
set size square
set xtic auto                          # set xtics automatically
set ytics 4,1,8


plot "Mesh.dat" using 1:4 notitle pt 0
set output "R1_3D_L8_eps_y.eps"

set xlabel "y"
set ylabel "Level"
set xr [-0.5:0.5]
set yr [3:9]
set size square
set xtic auto                          # set xtics automatically
set ytics 4,1,8

plot "Mesh.dat" using 2:4 notitle pt 0
set output "R1_3D_L8_eps_z.eps"

set xlabel "z"
set ylabel "Level"
set xr [-0.5:0.5]
set yr [3:9]
set size square
set xtic auto                          # set xtics automatically
set ytics 4,1,8

plot "Mesh.dat" using 3:4 notitle pt 0

set output "R1_3D_L8_eps_x_0.eps"

set xlabel "x"
set ylabel "Level"
set xr [-0.5:0.5]
set yr [3:9]
set size square
set xtic auto                          # set xtics automatically
set ytics 4,1,8

plot "Mesh_0.dat" using 1:4 notitle pt 0 pointsize 0.01

set output "R1_3D_L8_eps_y_0.eps"

set xlabel "y"
set ylabel "Level"
set xr [-0.5:0.5]
set yr [3:9]
set size square
set xtic auto                          # set xtics automatically
set ytics 4,1,8

plot "Mesh_0.dat" using 2:4 notitle pt 0 pointsize 0.01

set output "R1_3D_L8_eps_z_0.eps"

set xlabel "z"
set ylabel "Level"
set xr [-0.5:0.5]
set yr [3:9]
set size square
set xtic auto                          # set xtics automatically
set ytics 4,1,8

plot "Mesh_0.dat" using 3:4 notitle pt 0 pointsize 0.01
##################### PNG
set terminal png 
set output "R1_3D_L8_eps_x.png"

set xlabel "x"
set ylabel "Level"
set xr [-0.5:0.5]
set yr [3:9]
set size square
set xtic auto                          # set xtics automatically
set ytics 4,1,8


plot "Mesh.dat" using 1:4 notitle pt 0
set output "R1_3D_L8_eps_y.png"

set xlabel "y"
set ylabel "Level"
set xr [-0.5:0.5]
set yr [3:9]
set size square
set xtic auto                          # set xtics automatically
set ytics 4,1,8

plot "Mesh.dat" using 2:4 notitle pt 0
set output "R1_3D_L8_eps_z.png"

set xlabel "z"
set ylabel "Level"
set xr [-0.5:0.5]
set yr [3:9]
set size square
set xtic auto                          # set xtics automatically
set ytics 4,1,8

plot "Mesh.dat" using 3:4 notitle pt 0

set output "R1_3D_L8_eps_x_0.png"

set xlabel "x"
set ylabel "Level"
set xr [-0.5:0.5]
set yr [3:9]
set size square
set xtic auto                          # set xtics automatically
set ytics 4,1,8

plot "Mesh_0.dat" using 1:4 notitle pt 0 pointsize 0.01

set output "R1_3D_L8_eps_y_0.png"

set xlabel "y"
set ylabel "Level"
set xr [-0.5:0.5]
set yr [3:9]
set size square
set xtic auto                          # set xtics automatically
set ytics 4,1,8

plot "Mesh_0.dat" using 2:4 notitle pt 0 pointsize 0.01

set output "R1_3D_L8_eps_z_0.png"

set xlabel "z"
set ylabel "Level"
set xr [-0.5:0.5]
set yr [3:9]
set size square
set xtic auto                          # set xtics automatically
set ytics 4,1,8

plot "Mesh_0.dat" using 3:4 notitle pt 0 pointsize 0.01
