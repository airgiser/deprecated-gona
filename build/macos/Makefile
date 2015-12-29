all:	lib

libagg.a:
	cd ../../src/foundation/third_party/agg/src; \
	make; \
	cp libagg.a ../../../../../build/macos

libpng.a:
	cd ../../src/foundation/third_party/png; \
	cp scripts/makefile.darwin Makefile; \
	make; \
	cp libpng.a ../../../../build/macos

libz.a:
	cd ../../src/foundation/third_party/zlib; \
	sh ./configure; make; \
	cp libz.a ../../../../build/macos 

libfreetype.a:
	cd ../../src/foundation/third_party/freetype; \
	sh ./configure --without-png; make; \
	cp objs/.libs/libfreetype.a ../../../../build/macos

libgona_foundation.a:
	cd foundation; \
	make; \
	cp libgona_foundation.a ../
	
lib:	libagg.a \
	libpng.a \
	libz.a \
	libfreetype.a \
	libgona_foundation.a 

clean:	clean_agg \
	clean_png \
	clean_zlib \
	clean_freetype \
	clean_gona_foundation

clean_agg:
	rm libagg.a; \
	cd ../../src/foundation/third_party/agg/src; \
	make clean;

clean_png:
	rm libpng.a; \
	cd ../../src/foundation/third_party/png; \
	make clean;

clean_zlib:
	rm libz.a; \
	cd ../../src/foundation/third_party/zlib; \
	make clean;

clean_freetype:
	rm libfreetype.a; \
	cd ../../src/foundation/third_party/freetype; \
	make clean;
	
clean_gona_foundation:
	rm libgona_foundation.a; \
	cd foundation; \
	make clean;
