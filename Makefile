CC=gpp
DJDIR=C:\devel\djgpp
BIN=smol3d.exe

SRCDIR=source

LIBS=-lm -lalleg -L$(DJDIR)\lib

_DEPS=math.hpp renderer.hpp video.hpp input.hpp
DEPS=$(patsubst %,$(SRCDIR)/%,$(_DEPS))

OBJDIR=build
_OBJS=main.o
OBJS=$(patsubst %,$(OBJDIR)/%,$(_OBJS))

CFLAGS=-I$(DJDIR)\include \
       -DGLM_FORCE_CXX98 \
       -DGLM_FORCE_PLATFORM_UNKNOWN \
       -DGLM_FORCE_LEFT_HANDED \
       -DALLEGRO_HAVE_STDINT_H \
       -w -O3

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS) $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: clean

clean:
	deltree /Y $(OBJDIR)
	del $(BIN)