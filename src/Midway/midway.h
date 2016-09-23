/*
 * Copyright (c) 2015, Thierry Guillemot <thierry.guillemot.work@gmail.com>
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MIDWAY_MIDWAY_H_
#define MIDWAY_MIDWAY_H_

#include <stdio.h>
#include <stdlib.h>
#include "LibImages.h"

/**
 * @brief Launch the images midway equalizations
 *
 * @param imIn1: first image.
 * @param imIn2: second image.
 * @param imSize1: size of the first image.
 * @param imSize2: size of the first image.
 * @param histogram_size: numbers of bins used to compute the histogram.
 * @param verbose: TRUE to activate the verbose mode.
 * @param imOut1: image resulting of the midway equalization of the first image.
 * @param imOut2: image resulting of the midway equalization of the second image.
 *
 * @return EXIT_SUCCESS if the images have been equalized over each channel, EXIT_FAILURE otherwise.
 */
int Launch(
    const std::vector<float> &imIn1, 
    const std::vector<float> &imIn2,
    const ImageSize          &imSize1,
    const ImageSize          &imSize2,
    const size_t              histogram_size,
    const bool                verbose,
    std::vector<float>       *imOut1,
    std::vector<float>       *imOut2
    );

/**
 * @brief Compute the midway equalization between two different float tables. The function is designed to be used for differents uses than image processing. Thus, sizes of the two tables can be different.
 *
 * @param dataIn1_ptr: pointer of the first input table of values to equalize.
 * @param dataIn2_ptr: pointer of the second input table of values to equalize.
 * @param size1: number of elements in the first table.
 * @param size2: number of elements in the second table.
 * @param minimum_value: minimum value of the considered data. In the case of RGB images, this value equals 0.
 * @param maximum_value: maximum value of the considered data. In the case of RGB images, this value equals 255.
 * @param histogram_size: numbers of bins used to define the histogram.
 * @param dataOut1_ptr: pointer of the first equalized table. No space is allocated in this function. So, the user needs to allocate the necessary space before calling this function.
 * @param dataOut2_ptr: pointer of the second equalized table. No space is allocated in this function. So, the user needs to allocate the necessary space before calling this function.
 *
 * @return EXIT_SUCCESS if the tables have been equalized over each channel, EXIT_FAILURE otherwise.
 */
int ComputeMidwayEqualization(
    const float  *dataIn1_ptr,
    const float  *dataIn2_ptr,
    const size_t  size1,
    const size_t  size2,
    const float   minimum_value,
    const float   maximum_value,
    const size_t  histogram_size,
    float        *dataOut1_ptr,
    float        *dataOut2_ptr
    );

/**
 * @brief Compute the contrast function to apply to an image to obtain the equalized image
 * The function use a lookup table to compute norm(x) = 0.5*(x+ H2^{-1} o H1(x)
 *
 * @param  histogram1: vector containing the cumulative histogram of the 1st image
 * @param  histogram2: vector containing the cumulative histogram of the 2nd image
 *
 * @return The lookup table associating each bin of the histogram to their new values
 */
std::vector<size_t> ComputeContrastChangeFunction(
    const std::vector<float> &histogram1,
    const std::vector<float> &histogram2
    );

#endif // MIDWAY_MIDWAY_H_
