.PHONY: build clean test

build:
	mkdir -p build
	gcc src/main.c src/utils.c src/tokenizer.c -o build/kyucc

test:
	./build/kyucc ./test/test.txt

clean:
	rm -rf build