# Andrew Jackson
# V00768505


CXX = gcc
CXXFLAGS = -g -O3 -Wall

all: Color

Color: Color.o 
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f Color *.o

.PHONY: all clean
