
SOURCE_FILES = src/cpp/ast.cpp src/cpp/lexer.cpp src/cpp/main.cpp src/cpp/parser.cpp src/cpp/utils.cpp

TEMP_FILES = _build/lexer.c

clean:
	rm -fr _build

_build/%.c: src/new/%.new
	./main $< -o $@

build: $(SOURCE_FILES) $(TEMP_FILES)
	mkdir -p _build
	g++ -I_build -Isrc/cpp src/cpp/main.cpp -o _build/main

	cp _build/main main

tests: build
	./main tests/parsing/ex1.c
	./main tests/parsing/ex2.cpp
	./main tests/parsing/ex3.cpp
	./main tests/parsing/ex4.c
	./main tests/parsing/ex5.c
	./main tests/parsing/ex6.c

run: build
	./_build/main
