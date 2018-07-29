IDIR =./
CC=g++
CFLAGS=-I$(IDIR)

ODIR =./bin
SDIR =./
BDIR =./build

_DEPS = Classes.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Vehicle.o Main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_BUILDS = main
BUILDS = $(patsubst %,$(BDIR)/%,$(_BUILDS))

MKDIR = mkdir -p

OUT_DIR = bin build

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: directories $(BUILDS)

directories: 
	$(MKDIR) $(OUT_DIR)

$(BDIR)/main: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) 