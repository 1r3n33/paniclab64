RM = rm
TRANS = $(N64KITDIR)/niff/mtv/exe/trans

%.h: %.sgi
	$(TRANS) -s 16 -f RGBA -w 32 -h 32 -o $@ $<

SGIFILES = $(wildcard *.sgi)
HFILES = $(SGIFILES:.sgi=.h)

all: $(HFILES)

clean:
	$(RM) -f $(HFILES)
