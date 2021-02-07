RM = rm
TRANS = $(N64KITDIR)/niff/mtv/exe/trans

%32x32_CI_4b.h: %32x32_CI_4b.sgi
	$(TRANS) -s 4 -f CI -w 32 -h 32 -o $@ $<

%32x32_RGBA_16b.h: %32x32_RGBA_16b.sgi
	$(TRANS) -s 16 -f RGBA -w 32 -h 32 -o $@ $<

%64x64_I_4b.h: %64x64_I_4b.sgi
	$(TRANS) -s 4 -f I -w 64 -h 64 -o $@ $<

SGIFILES = $(wildcard *.sgi)
HFILES = $(SGIFILES:.sgi=.h)

all: $(HFILES)

clean:
	$(RM) -f $(HFILES)
