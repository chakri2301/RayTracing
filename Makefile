.PHONY: build run cmake all
build:
	make -C ./build
cmake:
	cmake -B build
run:
	./build/main >> out.ppm
clean:
	rm -rvf ./build/
all: clean cmake build run