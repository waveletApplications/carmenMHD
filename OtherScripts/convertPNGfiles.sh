convert  MR_214.png Mesh_6396.png  +append result_214.png
    
    
for ((i=1; i<215; i=i+1)) do	
		k=$((i*30))
      	if [ "$i" -lt 10 ]; then         
      		if	[ "$k" -lt 100 ]; then
      			convert  MR_00$i.png Mesh_00$k.png  +append result_$i.png
      		else
      			convert  MR_00$i.png Mesh_0$k.png   +append result_$i.png
      		fi
      	elif [ "$i" -lt 100 ]; then
      		if	[ "$k" -lt 1000 ]; then
      			convert  MR_0$i.png Mesh_0$k.png  +append result_$i.png
      		else
      			convert  MR_0$i.png Mesh_$k.png   +append result_$i.png
      		fi
      	else 
      		if	[ "$k" -lt 1000 ]; then
      			convert  MR_$i.png Mesh_0$k.png  +append result_$i.png
      		else
      			convert  MR_$i.png Mesh_$k.png   +append result_$i.png
      		fi
      	fi
      	
      	
      	echo $k
done


