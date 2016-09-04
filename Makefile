CPP := g++
CPPFLAGS :=-O3 -std=c++11 -Wall -Wextra #-DEBUG
OBJ = obj
LIB = lib
BUILD = build

DEPS = $(OBJ)/main.o $(OBJ)/ppm_image.o $(OBJ)/graphics.o

all: $(BUILD)/match

debug: $(DEPS)
	$(CPP) $(CPPFLAGS) -o $(BUILD)/match $^ -DEBUG

$(BUILD)/match: $(DEPS)
	$(CPP) $(CPPFLAGS) -o $@ $^

$(OBJ)/main.o: main.h main.cc
	$(CPP) $(CPPFLAGS) -o $@ -c main.cc

$(OBJ)/ppm_image.o: $(LIB)/ppm_image.h
	$(CPP) $(CPPFLAGS) -o $@ -c src/ppm_image.cc

$(OBJ)/graphics.o: $(LIB)/graphics.h $(OBJ)/ppm_image.o
	$(CPP) $(CPPFLAGS) -o $@ -c src/graphics.cc

.PHONY: clean all debug

clean:
	rm $(OBJ)/*.o $(BUILD)/*
