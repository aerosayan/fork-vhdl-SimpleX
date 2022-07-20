
files := $(wildcard *.cpp *.hpp)
sxFiles:= bootloader.sx Main.sx Memory.sx Math.sx Array.sx
CFLAGS = -g
all:
	@echo "Compiling SimplX Compiler" $(files)
	$(CXX) *.cpp -o SimpleX -g

simplex:
	@echo "SimpleX Compiling..."
	./SimpleX $(FILES)
	cp memory.list ../memory.list

os:	
	./SimpleX $(sxFiles)
	cp memory.list ../memory.list