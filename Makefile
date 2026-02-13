.PHONY: build clean

build:
	mkdir -p build
	gcc src/main.c src/utils.c -o build/kyucc

clean:
	rm -rf build