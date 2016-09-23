#!/bin/bash

function ComputeResults
{
    echo Midway equalization of the images $1 and $2

    # Arguments parsing
    is_colored_image=true
    options_histogram=""

    for ((i=4 ; i<=$#; i++))
    do
	if [[ ${!i} == "-cumulative" ]]; then
	    options_histogram+="-cumulative "
	fi
	if [[ ${!i} == "-gray" ]]; then
	    is_colored_image=false
	    options_histogram+="-gray "
	fi
	if [[ ${!i} == "-dithering" ]]; then
	    options="-dithering "${@:$((i+1)):1}
	fi
    done

    # Create the directory if it does not exit
    if [ ! -d $3 ] ; then mkdir $3 ; fi

    # Computation of the midway equalization
    bin/midway $1 $2 $3/1_out.png $3/2_out.png $options
    cp $1 $3/1_input.png
    cp $2 $3/2_input.png

    # Histogram Computation
    ./create_histogram.sh $3 $options_histogram
}

rm -rf output/*
mkdir -p output

# Gray samples
ComputeResults input/bat1.png input/bat2.png output/bat -cumulative -gray
ComputeResults input/danse1.png input/danse2.png output/danse -cumulative -gray
ComputeResults input/parot1.png input/parot2.png output/parot -cumulative -gray
ComputeResults input/nice1.png input/nice2.png output/nice -cumulative -gray
ComputeResults input/nice1.png input/nice2.png output/nice-dith -cumulative -gray -dithering 2

# Color samples
ComputeResults input/salta1.png input/salta2.png output/salta_diff -cumulative
ComputeResults input/fitzroy1.png input/fitzroy2.png output/fitzroy -cumulative
ComputeResults input/iguane1.png input/iguane2.png output/iguane -cumulative
ComputeResults input/strike1.png input/strike2.png output/strike/ -cumulative
ComputeResults input/cabo1.png input/cabo2.png output/cabo_red -cumulative
