for f in input_output_files/ChangeBase*.in
do 
	echo "prossesing $f file..."
	changebase < $f > $f.out
done
