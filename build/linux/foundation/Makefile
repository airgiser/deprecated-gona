CXX = g++
LIB = ar cr

CXXFLAGS = -O3 -DGONA_FOR_UNIX -I../../../src/foundation \
		-I../../../src/foundation/graphics \
		-I../../../src/foundation/third_party/agg/include \
		-I../../../src/foundation/third_party/agg/font_freetype \
		-I../../../src/foundation/third_party/freetype/include \
		-I../../../src/foundation/third_party/png \
		-L../

SRC_DIR=../../../src/foundation

SRC_CXX=\
$(SRC_DIR)/graphics/GnCanvas.cpp \
$(SRC_DIR)/graphics/GnImageLoader_png.cpp \
$(SRC_DIR)/graphics/GnImage.cpp \
$(SRC_DIR)/graphics/agg/GnAggRenderer.cpp \
$(SRC_DIR)/graphics/agg/GnBitmap.cpp \
$(SRC_DIR)/graphics/gl/GnGLRenderer.cpp \
$(SRC_DIR)/graphics/gl/GnGLFontManager.cpp \
$(SRC_DIR)/third_party/agg/font_freetype/agg_font_freetype.cpp

OBJ=$(SRC_CXX:.cpp=.o)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $*.cpp -o $@

all:	$(OBJ)
	$(LIB) libgona_foundation.a $(OBJ)

clean:
	rm -f *.a
	rm -f $(SRC_DIR)/*.o
	rm -f $(SRC_DIR)/graphics/*.o
	rm -f $(SRC_DIR)/graphics/agg/*.o
	rm -f $(SRC_DIR)/graphics/gl/*.o

