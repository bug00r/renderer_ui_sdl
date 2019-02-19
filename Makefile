include ../make_config

#CFLAGS=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra -O0 -mwindows $(debug) $(analysis)
#-ggdb
#-pg for profiling 

INCLUDEDIR= -I./../_third_/SDL2-2.0.5/x86_64-w64-mingw32/include \
			-I./../math/algorithm/fractals/ \
			-I./../math/algorithm/noise/ \
			-I./../math/statistics \
			-I./../math/vec \
			-I./../math/mat \
			-I./../math/utils \
			-I./../collections/array \
			-I./../color \
			-I./../texture \
			-I./../shape \
			-I./../mesh \
			-I./../scene \
			-I./../renderer/include \
			-I.

TESTSRC=test_renderer_ui_sdl.c
TESTBIN=test_renderer_ui_sdl.exe
TESTLIB= -static -lrenderer -lscene -lmesh -lshape -ltexture -lnoise -lfractals \
		 -lcrgb_array -lfarray -larray -lcolor -lstatistics -lutilsmath -lmat -lvec \
		 -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lfreetype6 -lz -lm \
		 -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm \
		 -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -static-libgcc -mwindows

TESTLIBDIR=-L$(BUILDDIR) \
		   -L./../renderer/$(BUILDDIR) \
		   -L./../math/algorithm/fractals/$(BUILDDIR) \
		   -L./../math/algorithm/noise/$(BUILDDIR) \
		   -L./../scene/$(BUILDDIR) \
		   -L./../mesh/$(BUILDDIR) \
		   -L./../shape/$(BUILDDIR) \
		   -L./../color/$(BUILDDIR) \
		   -L./../texture/$(BUILDDIR) \
		   -L./../collections/array/$(BUILDDIR) \
		   -L./../math/statistics/$(BUILDDIR) \
		   -L./../math/utils/$(BUILDDIR) \
		   -L./../math/mat/$(BUILDDIR) \
		   -L./../math/vec/$(BUILDDIR) \
		   -L./../_third_/SDL2_env/SDL2_build_msys2/lib \
		   -L./../_third_/zlib-1.2.11

UI_FONT=font.o
		   
all: mkbuilddir $(BUILDPATH)$(UI_FONT) $(BUILDPATH)$(TESTBIN)

$(BUILDPATH)$(TESTBIN):
	$(CC) $(CFLAGS) $(TESTSRC) -o $(BUILDPATH)$(TESTBIN) $(INCLUDEDIR) $(BUILDPATH)$(UI_FONT) $(TESTLIBDIR) $(TESTLIB)

$(BUILDPATH)$(UI_FONT):
	cp ./../_third_/fonts/tele-marines/Telev2b.ttf $(BUILDPATH)sdluifont.ttf
	cd $(BUILDPATH); \
	ld -r -b binary sdluifont.ttf -o $(UI_FONT) 

.PHONY: clean mkbuilddir

mkbuilddir:
	mkdir -p $(BUILDDIR)

small:
	-strip $(BUILDPATH)$(TESTBIN)
	
clean:
	-rm -dr $(BUILDROOT)
	