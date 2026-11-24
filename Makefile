N=./out
.PHONY: build run cmake all
build:
	make -C ./build
cmake:
	cmake -B build
run:
	rm -f $(N).ppm
	./build/main >> $(N).ppm
clean:
	rm -rvf ./build/
all: clean cmake build run
show:
	swayimg -F $(N).ppm
update: build run
	swayimg -F $(N).ppm