include $(ROOT)/usr/include/make/PRdefs

RM = rm
MAKEMASK = makemask

NUSYSINCDIR = $(N64KITDIR)/nusys/include
NUSYSLIBDIR = $(N64KITDIR)/nusys/lib

NUSTDINCDIR = $(N64KITDIR)/nustd/include
NUSTDLIBDIR = $(N64KITDIR)/nustd/lib

LIB = $(ROOT)/usr/lib
LPR = $(LIB)/PR
INC = $(ROOT)/usr/include

LCDEFS = -DNU_DEBUG -DF3DEX_GBI_2
LCINCS = -I. -I$(NUSYSINCDIR) -I$(NUSTDINCDIR) -I$(ROOT)/usr/include/PR
LCOPTS = -G 0
LDFLAGS = $(MKDEPOPT) -L$(LIB) -L$(NUSYSLIBDIR) -lnusys_d -L$(NUSTDLIBDIR) -lnustd_d -lgultra_d -L$(GCCDIR)/MIPSE/LIB -lkmc

OPTIMIZER = -g

APP = paniclab.out

TARGET = paniclab.n64

CODEFILES = $(wildcard *.c) $(wildcard game/*.c) $(wildcard graphics/*.c) $(wildcard controls/*.c)

CODEOBJECTS = $(CODEFILES:.c=.o)

CODESEGMENT = codesegment.o

default: $(TARGET)

clean:
	$(RM) -f $(CODESEGMENT) $(CODEOBJECTS) $(APP) $(TARGET) a.out

.c.o:
	$(CC) $(CFLAGS) $< -o $@

$(CODESEGMENT): $(CODEOBJECTS)
	$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(NUSYSLIBDIR)/nusys.o $(LDFLAGS)

$(TARGET): $(CODESEGMENT)
	$(MAKEROM) -s16 spec -I$(NUSYSINCDIR) -r $(TARGET) -e $(APP)
	$(MAKEMASK) $(TARGET)
