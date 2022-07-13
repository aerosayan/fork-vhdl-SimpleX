
files := $(wildcard *.cpp *.hpp)
CFLAGS = -g
all:
	@echo "Compiling SimplX Compiler" $(files)
	$(CXX) *.cpp -o SimpleX -g

simplex:
	@echo "SimpleX Compiling..."
	./SimpleX file.sx
	cp memory.list ../memory.list