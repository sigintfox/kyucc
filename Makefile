
build:
	mkdir -p build
	gcc src/main.c -o build/kyucc

clean:
	rm -rf build