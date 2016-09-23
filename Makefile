# Copyright 2009, 2010 IPOL Image Processing On Line http://www.ipol.im/
# Author: Thierry Guillemot <thierry.guillemot.work@gmail.com> and Julie Delon <julie.delon@parisdescarte.fr>
#
# Copying and distribution of this file, with or without
# modification, are permitted in any medium without royalty provided
# the copyright notice and this notice are preserved.  This file is
# offered as-is, without any warranty.

LDFLAGS   = -lpng

CXXOPT    = -O3 -funroll-loops -fomit-frame-pointer
CXXFLAGS  = $(CXXOPT) -Wall -Wextra -I src/Utilities
CXXSTRICT = -Wall -Wextra -ansi

DIR    = bin obj 

all: $(DIR) bin/midway bin/histogram 
default: $(DIR) bin/midway bin/histogram
.PHONY : clean distclean

# -- Create Directory ---
$(DIR) :
	mkdir -p $(DIR)

# ------- C files -------
obj/mt19937ar.o	: src/Utilities/mt19937ar.c src/Utilities/mt19937ar.h
	$(CXX) -c -o $@ $(CXXFLAGS) $<
obj/io_png.o : src/Utilities/io_png.c src/Utilities/io_png.h
	$(CXX) -c -o $@ $(CXXFLAGS) $<

# ------- CPP files -------
obj/LibImages.o	: src/Utilities/LibImages.cpp src/Utilities/LibImages.h
	$(CXX) -c -o $@ $(CXXFLAGS) $<
obj/midway.o : src/Midway/midway.cpp src/Midway/midway.h src/Utilities/utils.h
	$(CXX) -c -o $@ $(CXXFLAGS) $<
obj/histogram.o	: src/histogram.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<
obj/main.o	: src/main.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

# ------- Mains -------
bin/histogram : obj/mt19937ar.o obj/LibImages.o obj/io_png.o obj/midway.o obj/histogram.o
	$(CXX) -o $@ $^ $(LDFLAGS)
bin/midway : obj/mt19937ar.o obj/LibImages.o obj/io_png.o obj/midway.o obj/main.o
	$(CXX) -o $@ $^ $(LDFLAGS)

# ---- Clean Rules ----
clean :
	$(RM) -r obj
distclean : clean
	$(RM) -r bin

