CPP = g++

INC_DIR = ../../../src/foundation
CPPFLAGS = -O0 -I ../../../src/foundation \
					 -I ../../../src/foundation/graphics \
					 -I ../../../src/foundation/third_party/agg/include \
					 -I $(INC_DIR)/third_party/agg/font_freetype \
					 -I $(INC_DIR)/third_party/freetype/include \
					 -L ../ \
					 -L usr/local/lib 

SRC_DIR=../../../src/application/linux

SRC_CPP=\
				$(SRC_DIR)/Gona.cpp

all:	
	$(CPP) $(CPPFLAGS) $(SRC_CPP) -DGONA_FOR_UNIX -lX11 -lGL -lgona_foundation -lagg -lpng -lz -lfreetype -o gona

clean:
	rm -f gona
