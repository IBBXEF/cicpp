
SOURCE_FILES = src/cpp/ast.cpp src/cpp/lexer.cpp src/cpp/main.cpp src/cpp/parser.cpp src/cpp/utils.cpp

TEMP_FILES = _build/lexer.c
TEMP_TEST_FILES = _build/test/lexer.c

clean:
	rm -fr _build

_build/%.c: src/new/%.new main
	./main $< -o $@

_build/test/%.c: src/new/%.new main
	mkdir -p _build/test
	./test $< -o $@

build: $(SOURCE_FILES) $(TEMP_FILES)
	mkdir -p _build
	g++ -I_build -Isrc/cpp src/cpp/main.cpp -o _build/main

build_test: $(SOURCE_FILES) $(TEMP_TEST_FILES)
	mkdir -p _build
	mkdir -p _build/test
	g++ -I_build/test -Isrc/cpp src/cpp/main.cpp -o _build/main

replace: tests
	cp _build/main main

tests: build
	cp _build/main test
	
	./test tests/parsing/ex1.c
	./test tests/parsing/ex2.cpp
	./test tests/parsing/ex3.cpp
	./test tests/parsing/ex4.c
	./test tests/parsing/ex5.c
	./test tests/parsing/ex6.c
	./test tests/parsing/ex7.c

	make build_test
	diff test _build/main
	

run: build
	./_build/main
