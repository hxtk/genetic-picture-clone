CPP := g++
CPPFLAGS += -O3 -std=c++11 -Wall -Wextra
OBJ = obj
LIB = lib
BUILD = build

$(BUILD)/match: $(OBJ)/main.o $(OBJ)/ppm_image.o
	$(CPP) $(CPPFLAGS) -o $@ $^

$(OBJ)/main.o: main.h main.cc
	$(CPP) $(CPPFLAGS) -o $@ -c main.cc

$(OBJ)/ppm_image.o: $(LIB)/ppm_image.h
	$(CPP) $(CPPFLAGS) -o $@ -c src/ppm_image.cc

.PHONY: clean

clean:
	rm $(OBJ)/*.o $(BUILD)/*
