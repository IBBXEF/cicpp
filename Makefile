
SOURCE_FILES = src/cpp/ast.cpp src/cpp/lexer.cpp src/cpp/main.cpp src/cpp/parser.cpp src/cpp/utils.cpp

TEMP_FILES = _build/test/lexer.c _build/test/clist.c _build/test/parser.c
TEMP_TEST_FILES = _build/test2/lexer.c _build/test2/clist.c _build/test2/parser.c

help:
	@echo "usage:"
	@echo " - make clean       : delete temporary files"
	@echo " - make build_first : build project without recompiling cicpp files, using aldready available files"
	@echo " - make build       : build project normally"
	@echo " - make tests       : tests that the project works correctly, notably that it can correctly compile itself"
	@echo " - make help        : display this message"
	@echo " - make replacelib  : replace the reference compiled cicpp files with the newly compiled ones"
	@echo " - make replace     : replace the main executable with the newly compiled one (also runs replacelib)"

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

build: $(TEMP_FILES)
	make build_test
	g++ -I_build/test -Isrc/cpp src/cpp/main.cpp -o _build/main
	cp _build/main test
	make $(TEMP_TEST_FILES)

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
	cp _build/test/parser.c _build/parser.c

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
