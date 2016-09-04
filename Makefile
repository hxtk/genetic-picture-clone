GPP = g++ -O3 -std=c++11 -Wall -Wextra
OBJ = obj
LIB = lib
BUILD = build

$(BUILD)/match: $(OBJ)/main.o $(OBJ)/ppm_image.o
	$(GPP) -o $@ $^

$(OBJ)/main.o: main.h main.cc
	$(GPP) -o $@ -c main.cc

$(OBJ)/ppm_image.o: $(LIB)/ppm_image.h
	$(GPP) -o $@ -c src/ppm_image.cc

.PHONY: clean

clean:
	rm $(OBJ)/*.o
