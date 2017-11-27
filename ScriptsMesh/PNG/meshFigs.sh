name=$1
dim=$2
level=$3
eps=$4
rate=$5
it=$6

if [ "$eps" -eq 0 ]; then
	echo "FV solver - Full mesh"
	echo "No mesh to plot! Bye :'("
	exit 0
fi

filename1='mesh'$name$dim'D.gp'
filename2=$name'_'$dim'D_L'$level'_eps'$eps

#mv Mesh.dat 'Mesh'$it'.dat'
	
sed -i 's/set output "'$name'_'$dim'D_L9_eps.png"/set output "'$filename2'.png"/g' $filename1

gnuplot $filename1

mv $filename2'.png' $filename2'_'$it'.png'

string=$filename2
#filename='Mesh'$it'.dat'    
filename='Mesh.dat' 


if [ "$rate" -eq 0 ]; then
	sed -i 's/set output "'$string'.png"/set output "'$filename2'_000.png"/g' $filename1
	sed -i 's/plot "'$filename'" using 1:2 notitle pt 0 lt -1/plot "Mesh_0.dat" using 1:2 notitle pt 0 lt -1/g' $filename1	
	gnuplot $filename1
	sed -i 's/set output "'$filename2'_000.png"/set output "'$name'_'$dim'D_L9_eps.png"/g' $filename1
	sed -i 's/plot "Mesh_0.dat" using 1:2 notitle pt 0 lt -1/plot "Mesh.dat" using 1:2 notitle pt 0 lt -1/g' $filename1	
	exit 0
fi	
   
if [ "$it" -lt 1000 ]; then
	for ((i="$rate"; i<"$it"+"$rate"; i=i+"$rate")) do
	
		if [ "$i" -lt 100 ]; then         	
			startString=$filename2'_0'
		  	startFile='Mesh0'
		else   
		  	startString=$filename2'_'
		  	startFile='Mesh'
		fi

		endFile='.dat'    

		replaceFor=$startString$i
		newFilename=$startFile$i$endFile
	
		if [ ! -f $newFilename ]; then
			echo "File not found!"
			sed -i 's/set output "'$string'.png"/set output "'$filename2'_000.png"/g' $filename1
			gnuplot $filename1
			sed -i 's/set output "'$filename2'_000.png"/set output "'$name'_'$dim'D_L9_eps.png"/g' $filename1
			sed -i 's/plot "'$filename'" using 1:2 notitle pt 0 lt -1/plot "Mesh.dat" using 1:2 notitle pt 0 lt -1/g' $filename1	
			exit 0
		fi
	
		sed -i 's/set output "'$string'.png"/set output "'$replaceFor'.png"/g' $filename1
		sed -i 's/plot "'$filename'" using 1:2 notitle pt 0 lt -1/plot "'$newFilename'" using 1:2 notitle pt 0 lt -1/g' $filename1
		#echo 's/u = load("'$string'");/u = load("'$replaceFor'");/g'
		gnuplot $filename1
	
		string=$replaceFor
		filename=$newFilename		  
	done
else
	for ((i="$rate"; i<"$it"+"$rate"; i=i+"$rate")) do
	
		  	if [ "$i" -lt 100 ]; then         	
		  		startString=$filename2'_0'
		  		startFile='Mesh0'
		  	else   
		  		startString=$filename2'_'
		  		startFile='Mesh'
		  	fi

		  	endFile='.dat'    

		  	replaceFor=$startString$i
		  	newFilename=$startFile$i$endFile
	
		if [ ! -f $newFilename ]; then
			echo "File not found!"
			sed -i 's/set output "'$string'.png"/set output "'$filename2'_000.png"/g' $filename1
			gnuplot $filename1
			sed -i 's/set output "'$filename2'_000.png"/set output "'$name'_'$dim'D_L9_eps.png"/g' $filename1
			sed -i 's/plot "'$filename'" using 1:2 notitle pt 0 lt -1/plot "Mesh.dat" using 1:2 notitle pt 0 lt -1/g' $filename1	
			exit 0
		fi
	
		sed -i 's/set output "'$string'.png"/set output "'$replaceFor'.png"/g' $filename1
		sed -i 's/plot "'$filename'" using 1:2 notitle pt 0 lt -1/plot "'$newFilename'" using 1:2 notitle pt 0 lt -1/g' $filename1
		#echo 's/u = load("'$string'");/u = load("'$replaceFor'");/g'
		gnuplot $filename1
	
		string=$replaceFor
		filename=$newFilename		  
	done
fi

