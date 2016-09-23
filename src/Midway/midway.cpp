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

#include "midway.h"

#include <math.h>
#include <limits.h>
#include <iostream>
#include "utils.h"

using namespace std;

int Launch(
    const vector<float> &imIn1, 
    const vector<float> &imIn2,
    const ImageSize     &imSize1,
    const ImageSize     &imSize2,
    const size_t         histogram_size,
    const bool           verbose,
    vector<float>       *imOut1,
    vector<float>       *imOut2
    )
{
  //! Check if two images have the same number of channels
  if (imSize1.nChannels != imSize2.nChannels)
  {
    cerr << "Different number of channel for the two images" << endl;
    return EXIT_FAILURE;
  }

  //! Apply midway equalization over each channel independantly
  if (verbose)
  {
    cout << "Apply Midway equalization...";
  }
  
  for (size_t channel = 0; channel < imSize1.nChannels; ++channel)
  {
    const float *dataIn1_ptr  = imIn1.data()   + channel*imSize1.wh;
    const float *dataIn2_ptr  = imIn2.data()   + channel*imSize2.wh;
    float       *dataOut1_ptr = imOut1->data() + channel*imSize1.wh;
    float       *dataOut2_ptr = imOut2->data() + channel*imSize2.wh;
    
    if (ComputeMidwayEqualization(dataIn1_ptr, dataIn2_ptr, imSize1.wh, imSize2.wh,
                                  0.f, 255.f, histogram_size,
                                  dataOut1_ptr, dataOut2_ptr) == EXIT_FAILURE)
    {
      return EXIT_FAILURE;
    }
  }
  
  if (verbose)
  {
    cout << "done." << endl;
  }
  
  return EXIT_SUCCESS;
}

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
    )
{
  //! Check the number of bins of the histogram is not 0
  if(!histogram_size)
  {
    cerr << "Histogram size must be at least equal to 1" << endl;
    return EXIT_FAILURE;
  }

  //! Compute the cumulative histograms
  vector<float> cumulative_histogram_1 = ComputeNormalizedCumulativeHistogram(dataIn1_ptr, size1, minimum_value, maximum_value, histogram_size);
  vector<float> cumulative_histogram_2 = ComputeNormalizedCumulativeHistogram(dataIn2_ptr, size2, minimum_value, maximum_value, histogram_size);

  //! Compute the contrast change function using a lookup table
  vector<size_t> f_12 = ComputeContrastChangeFunction(cumulative_histogram_1, cumulative_histogram_2);
  vector<size_t> f_21 = ComputeContrastChangeFunction(cumulative_histogram_2, cumulative_histogram_1);

  //! Apply contrast changes to the data
  float scale = (histogram_size-1) / (maximum_value - minimum_value);
  for (size_t pos = 0; pos < size1; ++pos)
  {
    size_t histogram_bin = static_cast<size_t> (Crop(scale*(dataIn1_ptr[pos] - minimum_value), 0, histogram_size-1)); 
    float  x             = static_cast<float> (f_12[histogram_bin]) / (histogram_size);
    dataOut1_ptr[pos]    = Crop(x*(maximum_value-minimum_value) + minimum_value, minimum_value, maximum_value);
  }

  for (size_t pos = 0; pos < size2; ++pos)
  {
    size_t histogram_bin = static_cast<size_t> (Crop(scale*(dataIn2_ptr[pos] - minimum_value), 0, histogram_size-1)); 
    float  x             = static_cast<float> (f_21[histogram_bin]) / (histogram_size);
    dataOut2_ptr[pos]    = Crop(x*(maximum_value-minimum_value) + minimum_value, minimum_value, maximum_value);
  }

  return EXIT_SUCCESS;
}

vector<size_t> ComputeContrastChangeFunction(
    const vector<float> &histogram1,
    const vector<float> &histogram2
    )
{
  //! We use a lookup table to compute all the contrast changes values at once
  vector<size_t> contrast_function(histogram1.size());

  //! For each position on the 1st histogram we find the position in the 2nd histogram
  //! with the same cumulative value
  for (size_t pos1 = 0; pos1<histogram1.size(); ++pos1)
  {
    size_t pos2;
    for(pos2 = 0; pos2<histogram2.size() && histogram2[pos2]<histogram1[pos1]; ++pos2);
    
    contrast_function[pos1] = static_cast<size_t>(0.5*static_cast<float>(pos1 + pos2));
  }
  
  return contrast_function;
}
