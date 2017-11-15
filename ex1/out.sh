for f in input_output_files/FindString*.in
do 
	echo "prossesing $f file..."
	findstring < $f
done
