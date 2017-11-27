
gnuplot viewMesh2DMR.gp

sed -i 's/set output "Mesh2DMR.png"/set output "Mesh2DMR0000.png"/g' viewMesh2DMR.gp
sed -i 's/plot "Mesh.dat" using 1:2 notitle pt 0/plot "Mesh00000.dat" using 1:2 notitle pt 0/g' viewMesh2DMR.gp
gnuplot viewMesh2DMR.gp

sed -i 's/set output "Mesh2DMR0000.png"/set output "Mesh2DMR0030.png"/g' viewMesh2DMR.gp
sed -i 's/plot "Mesh00000.dat" using 1:2 notitle pt 0/plot "Mesh0030.dat" using 1:2 notitle pt 0/g' viewMesh2DMR.gp
gnuplot viewMesh2DMR.gp

sed -i 's/set output "Mesh2DMR0030.png"/set output "Mesh2DMR0060.png"/g' viewMesh2DMR.gp
sed -i 's/plot "Mesh0030.dat" using 1:2 notitle pt 0/plot "Mesh0060.dat" using 1:2 notitle pt 0/g' viewMesh2DMR.gp
gnuplot viewMesh2DMR.gp

sed -i 's/set output "Mesh2DMR0060.png"/set output "Mesh2DMR0090.png"/g' viewMesh2DMR.gp
sed -i 's/plot "Mesh0060.dat" using 1:2 notitle pt 0/plot "Mesh0090.dat" using 1:2 notitle pt 0/g' viewMesh2DMR.gp
gnuplot viewMesh2DMR.gp 

string='Mesh0090.dat'
filename='Mesh2DMR0090.png'    
for ((i=120; i<10000; i=i+30)) do
	
      	if [ "$i" -lt 1000 ]; then         	
      		startString='Mesh0'
      		startFile='Mesh2DMR0'
      	else
      		startString='Mesh'
      		startFile='Mesh2DMR'
      	fi
   
      
      	endString='.dat' 
      	endFile='.png'    

      	replaceFor=$startString$i$endString
      	newFilename=$startFile$i$endFile
	
	if [ ! -f $replaceFor ]; then
    	echo "File not found!"
    	exit 0
	fi
	
	sed -i 's/set output "'$string'"/set output "'$replaceFor'"/g' viewMesh2DMR.gp
	sed -i 's/plot "'$filename'" using 1:2 notitle pt 0/plot "'$newFilename'" using 1:2 notitle pt 0/g' viewMesh2DMR.gp
	#echo 's/u = load("'$string'");/u = load("'$replaceFor'");/g'
    gnuplot viewMesh2DMR.gp 
	
	string=$replaceFor
	filename=$newFilename
      
done

