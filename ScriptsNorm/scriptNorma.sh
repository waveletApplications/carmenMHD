name=$1
dim=$2
level=$3
eps=$4
type1='.dat'
type2='.okc'

if [ $name = 'OT' ];then
	filename1='OrszagTang_'$dim'D_flash_L'$level
	filename2='OrszagTang_'$dim'D_L'$level'_eps'$eps
elif [ $name = 'KH' ];then
	filename1='KelvinHelmholtz_'$dim'D_flash_L'$level
	filename2='KelvinHelmholtz_'$dim'D_L'$level'_eps'$eps
elif [ $name = 'SC' ];then
	filename1='ShockCloud_'$dim'D_flash_L'$level
	filename2='ShockCloud_'$dim'D_L'$level'_eps'$eps
elif [ $name = 'R1' ];then
	filename1='Riemann1D_'$dim'D_flash_L'$level
	filename2='Riemann1D_'$dim'D_L'$level'_eps'$eps
elif [ $name = 'R2' ];then
	filename1='Riemann2D_'$dim'D_flash_L'$level
	filename2='Riemann2D_'$dim'D_L'$level'_eps'$eps
elif [ $name = 'MR' ];then
	filename1='MagneticReconnection_'$dim'D_flash_L'$level
	filename2='MagneticReconnection_'$dim'D_L'$level'_eps'$eps
fi

aux=$((level*dim))
N=$((2**aux))
N=$((N+17))
N2=$((N+23))
lines2='24,'$N2'p'
lines='18,'$N'p'

sed -n $lines2   $filename1$type2 > $filename1$type1
sed -n $lines2   $filename2$type2 > $filename2$type1

octave computeNorms.m $filename1$type1 $filename2$type1 $level $dim

rm *.dat

sed -i '1 i\Norms L1.......Linf........L2' norms.txt
	
normName='Norms_'$name'_'$dim'_L'$level'_eps'$eps'.txt'

mv norms.txt $normName
