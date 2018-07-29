# all:
# 	g++ -o main Main.cpp Vehicle.cpp -I.

CC=g++
CFLAGS = -I.

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

all: directories $(BUILDS)

directories: 
	$(MKDIR) $(OUT_DIR)

$(BDIR)/main: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) 

bin/Vehicle.o: Vehicle.cpp $(_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/Main.o: Main.cpp $(_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)