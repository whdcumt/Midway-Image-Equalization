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

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LibImages.h"

using namespace std;

/**
 * @brief function to write the data of the computed histogram.
 * These data will be used then by a gnuplot sript to create an SVG
 *
 * @param filename: name of the histogram data
 * @histogram: vector containing the value of the histogram
 * @nchannel: number of channel of the histogram. Two value possible: 1 for gray images and 3 for rgb images
 *
 * @return EXIT_SUCCESS if the computation of the histogram has been done, EXIT_FAILURE otherwise
 */
int WriteHistogram(
    const char          *filename,
    const vector<float>  histogram,
    const size_t         nChannels
    )
{
  ofstream out(filename, ios::out | ios::trunc);
  if(!out)
  {
    cerr << "Writing file problem" << endl;
    return EXIT_FAILURE;
  }

  out << "# Pos\tR\tG\tB\tRG\tGB\tRB\tRGB" << endl;
  for(size_t pos=0; pos<256; ++pos)
  {
    if(nChannels==1)
    {
      out << pos;
      for(size_t i=0;i<7; ++i)
        out << '\t' << histogram[pos];
      out << endl;
    }
    else
      out << pos << '\t'
	  << histogram[pos] << '\t'
	  << histogram[pos+256] << '\t'
	  << histogram[pos+512] << '\t'
	  << min(histogram[pos], histogram[pos+256]) << '\t'
	  << min(histogram[pos+256], histogram[pos+512]) << '\t'
	  << min(histogram[pos], histogram[pos+512]) << '\t'
	  << min(min(histogram[pos], histogram[pos+256]), histogram[pos+512]) << endl;
  }
  out.close();

  return EXIT_SUCCESS;
}

/**
 * @brief launch function to compute the histogram
 *
 * @param filename_image_png: filename of the input image
 * @param filename_histogram: filename of the output histogram data
 * @param cumulative: TRUE to compute the cumulative histogram, FALSE otherwise
 *
 * @return EXIT_SUCCESS if the computation of the histogram has been done, EXIT_FAILURE otherwise
 */
int Launch(
    const char *filename_image_png,
    const char *filename_histogram,
    bool        cumulative
    )
{
  std::vector<float> image;
  ImageSize          imSize;
  std::vector<float> histogram;

  //! Load images
  if(loadImage(filename_image_png, image, imSize, false) != EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }

  //! extraction de l'histogramme
  if(cumulative)
  {
    histogram.reserve(256*imSize.nChannels);
    for (size_t channel = 0; channel < imSize.nChannels; ++channel)
    {
      const float   *data_ptr          = image.data() + channel*imSize.wh;
      vector<float>  channel_histogram = ComputeNormalizedCumulativeHistogram(data_ptr, imSize.wh, 0, 255, 256);
      histogram.insert(histogram.end(), channel_histogram.begin(), channel_histogram.end());
    }
  }
  else
  {
    histogram.reserve(256*imSize.nChannels);
    for (size_t channel = 0; channel < imSize.nChannels; ++channel)
    {
      const float   *data_ptr          = image.data() + channel*imSize.wh;
      vector<float>  channel_histogram = ComputeNormalizedHistogram(data_ptr, imSize.wh, 0, 255, 256);
      histogram.insert(histogram.end(), channel_histogram.begin(), channel_histogram.end());
    }
  }

  //! Save histogram
  if(WriteHistogram(filename_histogram, histogram, imSize.nChannels) != EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/**
 * @brief print usage function
 */
void PrintUsage()
{
  cerr << "usage: histogram [options] in.png hist.out" << endl
       << "options:" << endl
       << "--version: show the program version" << endl
       << "-c: compute cumulative histogram" << endl
       << endl;
}

/**
 * @brief main function call
 */
int main(int argc, char *const *argv)
{
  if (argc > 4)
  {
    PrintUsage();
    return EXIT_FAILURE;
  }

  const char *filename_image_png;
  const char *filename_histogram;
  bool        cumulative;

  if(strcmp("-c", argv[1]) == 0)
  {
    cumulative = true;
    filename_image_png = argv[2];
    filename_histogram = argv[3];
  }
  else
  {
    cumulative = false;
    filename_image_png = argv[1];
    filename_histogram = argv[2];
  }

  return Launch(filename_image_png, filename_histogram, cumulative);
}
