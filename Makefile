
SOURCE_FILES = src/cpp/ast.cpp src/cpp/lexer.cpp src/cpp/main.cpp src/cpp/parser.cpp src/cpp/utils.cpp

TEMP_FILES = _build/test/lexer.c _build/test/clist.c
TEMP_TEST_FILES = _build/test2/lexer.c _build/test2/clist.c

hardclean:
	rm -fr _build

clean:
	rm -fr _build/test
	rm -fr _build/test2

_build/test/%.c: src/cicpp/%.cicpp main
	mkdir -p _build/test
	mkdir -p _build
	./main $< -o $@

_build/test2/%.c: src/cicpp/%.cicpp test
	mkdir -p _build
	mkdir -p _build/test2
	./test $< -o $@

build: build_first $(TEMP_FILES)

build_first: $(SOURCE_FILES)
	mkdir -p _build
	g++ -I_build -Isrc/cpp src/cpp/main.cpp -o _build/main

build_test: $(SOURCE_FILES) $(TEMP_TEST_FILES)
	mkdir -p _build
	mkdir -p _build/test
	mkdir -p _build/test2
	g++ -I_build/test -Isrc/cpp src/cpp/main.cpp -o _build/_test

replacelib: $(TEMP_FILES)
	cp _build/test/lexer.c _build/lexer.c
	cp _build/test/clist.c _build/clist.c

replace:
	cp _build/main main
	make replacelib

tests: build
	cp _build/main test
	
	./test tests/parsing/ex1.c
	./test tests/parsing/ex2.cpp
	./test tests/parsing/ex3.cpp
	./test tests/parsing/ex4.c
	./test tests/parsing/ex5.c
	./test tests/parsing/ex6.c
	./test tests/parsing/ex7.c
	./test tests/parsing/ex8.c

	make build_test
	diff test _build/_test
