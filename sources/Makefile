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
LDFLAGS = $(MKDEPOPT) -L$(LIB) -L$(NUSYSLIBDIR) -L$(NUSTDLIBDIR) -lnusys_d -lgultra_d -L$(GCCDIR)/MIPSE/LIB -lkmc

OPTIMIZER =	-g

APP = paniclab.out

TARGETS = paniclab.n64

CODEFILES = $(wildcard *.c)

CODEOBJECTS = $(CODEFILES:.c=.o)

DATAFILES =

DATAOBJECTS = $(DATAFILES:.c=.o)

CODESEGMENT = codesegment.o

OBJECTS = $(CODESEGMENT) $(DATAOBJECTS)

default: $(TARGETS)

include $(COMMONRULES)
clean:
	$(RM) -f $(OBJECTS) $(CODEOBJECTS) $(APP) $(TARGETS) a.out

$(CODESEGMENT):	$(CODEOBJECTS)
	$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(NUSYSLIBDIR)/nusys.o $(LDFLAGS)

$(TARGETS):	$(OBJECTS)
	$(MAKEROM) -s16 spec -I$(NUSYSINCDIR) -r $(TARGETS) -e $(APP)
	$(MAKEMASK) $(TARGETS)
