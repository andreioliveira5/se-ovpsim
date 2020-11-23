IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

# Build locally without using a VLNV library
NOVLNV=1

# Build using two passes so that each pass includes separate Makefiles
MAKEPASS?=0
ifeq ($(MAKEPASS),0)
all: application
application:
	$(MAKE) MAKEPASS=2
clean:
	$(MAKE) MAKEPASS=2 clean
endif

# Pass 2 build the Application
ifeq ($(MAKEPASS),2)

OPTIMISATION?=-O2

CROSS=OR1K
SRC?=application.c task0.c task1.c
SRCINC?=

INCOBJ=$(patsubst %.c,%.$(CROSS).o,$(SRCINC))
EXE=$(patsubst %.c,%.$(CROSS).elf,$(SRC))


-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Error : $(CROSS)_CC not set. Please check installation of toolchain for $(CROSS)")
endif

all: $(EXE)

%.$(CROSS).elf: %.$(CROSS).o $(INCOBJ)
	@    echo "# Linking $(CROSS) $@"
	$(V) $(IMPERAS_LINK) -o $@ $^ $(IMPERAS_LDFLAGS) -lm

%.$(CROSS).o: %.c
	@    echo "# Compiling $(CROSS) $<"
	$(V) $(IMPERAS_CC) -c -o $@ $< -D$(CROSS) $(OPTIMISATION)

%.dbg.$(CROSS).elf: %.dbg.$(CROSS).o $(INCOBJ)
	@    echo "# Linking $(CROSS) $@"
	$(V) $(IMPERAS_LINK) -o $@ $^ $(IMPERAS_LDFLAGS) -lm

%.dbg.$(CROSS).o: %.c
	@    echo "# Compiling $(CROSS) (Debug) $<"
	$(V) $(IMPERAS_CC) -c -o $@ $< -D$(CROSS) -O0 -g -gdwarf-2

clean::
	- rm -f *.$(CROSS).elf *.$(CROSS).o

endif

