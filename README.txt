				━━━━━━━━━━
                         	 README.txt
				━━━━━━━━━━


Table of Contents
─────────────────

1 About
2 Overview
3 Requirement
4 Compilation
5 Usage
.. 5.1 midway
..... 5.1.1 Description
..... 5.1.2 Usage examples
.. 5.2 create_histogram.sh
..... 5.2.1 Description
..... 5.2.2 Usage example
.. 5.3 launch.sh
..... 5.3.1 Description
6 About this file


#+AUTHOR Thierry Guillemot and Julie Delon +DATE <2015-08-07 ven.>


1 About
═══════

  Author : Thierry Guillemot <thierry.guillemot.work@gmail.com> and
           Julie Delon <julie.delon@parisdescartes.fr>
  Copyright: (C) 2015 IPOL Image Processing On Line [http://www.ipol.im/]
  Licence : GPL V3+


2 Overview
══════════

  This source code provides an implementation of the "midway" image
  equalization, as described in IPOL, another program called
  'create_histogram.sh' used to generate the histogram of all PNG images
  contained in a directory and a 'launch.sh' file to generate all the
  results presented in the paper.

  The 'bin/midway' program reads two PNG images, then apply contrast
  changes to these images such that the output images have the same
  distributions (this is done channel by channel).  This common
  distribution is built as the midway between the two original ones.  If
  H1 and H2 are the cumulative histograms of the input images (for the
  considered channel), the midway histogram is defined as (0.5*(H1^{-1}
  + H2^{-1}))^{-1}. The contrast changes to be applied are thus
  respectively x -> 0.5*(x + H2^{-1} o H1 (x)) for the first image and x
  -> 0.5*(x + H1^{-1} o H2 (x)) for the second image. Both resulting
  images are written as PNG images.

  The 'create_histogram.sh' compute the histograms of all the PNG images
  of a specified directory.  Resulting histograms are written in SVG.

  Only 8bit GRAY/RGB PNG images are handled.


3 Requirement
═════════════

  The code is written in ANSI C, and should compile on any system with
  an ANSI C compiler.

  The libpng header and libraries and gnuplot programs are required on
  the system for compilation and execution. On Linux, just use your
  package manager to install it:
  ┌────
  │ sudo apt-get install libpng
  │ sudo apt-get install gnuplot
  └────

  For more information, see [http://www.libpng.org/pub/png/libpng.html]


4 Compilation
═════════════

  Simply use the provided makefile, with the command 'make'.  The
  makefile will produce two programs called : 'bin/midway' and
  'bin/histogram'.  The 'midway' program is used the midway equalization
  of two images.  The 'histogram' program is used by
  'create_histogram.sh' to compute the histogram of a directory.


5 Usage
═══════

5.1 midway
──────────

5.1.1 Description
╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌

  The 'bin/midway' program is used to apply the midway equalization over
  two images. It takes 4 parameters with other optional:
  ┌────
  │ bin/midway in1.png in2.png out1.png out2.png [options]
  └────
  in1.png : first input image.
  in2.png : second input image.
  out1.png: first output image.
  out2.png: second output image.

  Options :
  -dithering sigma: apply a Gaussian noise of standard deviation sigma
                    before applying the midway equalization.
  -verbose: activate the verbose mode


5.1.2 Usage examples
╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌

  If you want to compute the midway equalization between the files
  'input/bat1.png' and 'input/bat2.png' without dithering and save the
  resulting images into 'out1.png' and 'out2.png', you can use the
  command:
  ┌────
  │ bin/midway input/bat1.png input/bat2.png out1.png out2.png
  └────

  The command:
  ┌────
  │ bin/midway input/nice1.png input/nice2.png out1.png out2.png -dithering 2
  └────
  will compute the midway equalization of the files 'input/nice1.png'
  and 'input/nice2.png' with a dithering of sigma=2 and save the
  resulting images into 'out1.png' and 'out2.png'.


5.2 create_histogram.sh
───────────────────────

5.2.1 Description
╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌

  The 'create_histogram.sh' program is used to compute the histogram of
  all PNG images contained in a directory. It takes 1 parameter with
  other optional:
  ┌────
  │ ./create_histogram.sh directory out.svg [options]
  └────
  directory : directory containing PNG images

  Options :
  -cumulative: compute the normalized cumulative histogram


5.2.2 Usage example
╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌

  To compute the normalized histogram of the directory input, you can
  use:
  ┌────
  │ ./create_histogram.sh input
  └────

  To compute the normalized cumulative histogram of the directory input,
  you can use:
  ┌────
  │ ./create_histogram.sh input -cumulative
  └────


5.3 launch.sh
─────────────

5.3.1 Description
╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌

  The 'launch.sh' file is used to generate all the result presented in
  the paper. To launch it, just use the command To compute the
  normalized histogram of the directory input, you can use:
  ┌────
  │ ./launch.sh
  └────


6 About this file
═════════════════

  Copyright 2015 IPOL Image Processing On Line [http://www.ipol.im/]
  Author: Thierry Guillemot <thierry.guillemot@gmail.com> and Julie
  Delon <julie.delon@parisdescartes.fr>

  Copying and distribution of this file, with or without modification,
  are permitted in any medium without royalty provided the copyright
  notice and this notice are preserved.  This file is offered as-is,
  without any warranty.
