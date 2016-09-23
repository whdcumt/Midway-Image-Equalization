#!/bin/bash

# Arguments parsing
is_colored_image=true
options=""
for arg in $*
do
    if [[ $arg == "-cumulative" ]]; then
	options="-c"
    fi
    if [[ $arg == "-gray" ]]; then
	is_colored_image=false
    fi
done

# Extracting filenames
for filename in `ls $1 | grep .png`; do
		filename=$1/$(basename "$filename" .png)
		bin/histogram $options $filename.png $filename.dat
		echo `tail -n 255 $filename.dat | awk '{if(max==""){max=$2}; if($2>max) {max=$2};} END {print max}'` >> $1/maxi
		echo `tail -n 255 $filename.dat | awk '{if(max==""){max=$3}; if($3>max) {max=$3};} END {print max}'` >> $1/maxi
		echo `tail -n 255 $filename.dat | awk '{if(max==""){max=$4}; if($4>max) {max=$4};} END {print max}'` >> $1/maxi
done

# SVG computation
max_value_histogram=`awk '{if(max==""){max=$1}; if($1>max) {max=$1};} END {print max}' $1/maxi`
for filename in `ls $1/*.dat | grep 1_*`; do
    filename=$(basename "$filename" .dat | cut -c3-)
    if [ "$is_colored_image" = true ]; then
	gnuplot -e "data1='$1/1_$filename.dat';data2='$1/2_$filename.dat';maximum='$max_value_histogram';out='$1/${filename}_hist.svg" histogram_color.gp
    else
	gnuplot -e "data1='$1/1_$filename.dat';data2='$1/2_$filename.dat';maximum='$max_value_histogram';out='$1/${filename}_hist.svg" histogram_gray.gp
    fi
    rm $1/1_$filename.dat $1/2_$filename.dat
done

rm $1/maxi
