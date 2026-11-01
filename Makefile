
SOURCE_FILES = src/cpp/ast.cpp src/cpp/lexer.cpp src/cpp/main.cpp src/cpp/parser.cpp src/cpp/utils.cpp

clean:
	rm -fr _build


build: $(SOURCE_FILES)
	mkdir -p _build
	g++ src/cpp/main.cpp -o _build/main

	cp _build/main main

tests: build
	./main tests/parsing/ex1.c

run: build
	./_build/main
