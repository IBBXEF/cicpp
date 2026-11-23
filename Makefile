
SOURCE_CPP_FILES = src/cpp/ast.cpp src/cpp/main.cpp src/cpp/parser.cpp src/cpp/utils.cpp
SOURCE_FILES = src/cicpp/parser.cicpp

TEMP_FILES = _build/test/clist.c _build/test/set.c _build/test/anyptr.c _build/test/lexer.c _build/test/parser.c
TEMP_TEST_FILES = _build/test2/clist.c _build/test2/set.c _build/test2/anyptr.c _build/test2/lexer.c _build/test2/parser.c

ifdef FAST
TEMP_FILES = _build/test/parser.c
TEMP_TEST_FILES = _build/test2/parser.c
endif

ifdef DEBUG
GCC_ARGS = -Wall -Wpedantic -Wextra -g -std=c++20 -fsanitize=address
else
GCC_ARGS = -Wall -Wpedantic -Wextra -O3 -std=c++20
endif

help:
	@echo "usage:"
	@echo " - make clean            : delete temporary files"
	@echo " - make build_first      : build project without recompiling cicpp files, using aldready available files"
	@echo " - make build            : build project normally"
	@echo " - make tests            : tests that the project works correctly, notably that it can correctly compile itself"
	@echo " - make test_continuity  : tests that the new code does compiles to itself"
	@echo " - make help             : display this message"
	@echo " - make replacelib       : replace the reference compiled cicpp files with the newly compiled ones"
	@echo " - make replace          : replace the main executable with the newly compiled one (also runs replacelib)"

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

build: $(SOURCE_FILES) $(SOURCE_FILES)
	rm -fr _build/test
	make $(TEMP_FILES)
	g++ $(GCC_ARGS) -I_build/test -Isrc/cpp src/cpp/main.cpp -o _build/main
	cp _build/main test
	make $(TEMP_TEST_FILES)

build_first: $(SOURCE_CPP_FILES)
	mkdir -p _build
	g++ $(GCC_ARGS) -I_build -Isrc/cpp src/cpp/main.cpp -o _build/main
	cp _build/main main
	rm -fr _build/test
	make $(TEMP_FILES)

build_test: $(SOURCE_CPP_FILES)
	rm -fr _build/test2
	make $(TEMP_TEST_FILES)
	mkdir -p _build
	mkdir -p _build/test
	mkdir -p _build/test2
	g++ $(GCC_ARGS) -I_build/test2 -Isrc/cpp src/cpp/main.cpp -o _build/_test

replacelib: $(TEMP_FILES)
	cp _build/test/lexer.c _build/lexer.c
	cp _build/test/clist.c _build/clist.c
	cp _build/test/parser.c _build/parser.c
	cp _build/test/anyptr.c _build/anyptr.c
	cp _build/test/set.c _build/set.c

replace: $(SOURCE_FILES)
	cp _build/main main
	make replacelib

tests: build
	cp _build/main test
	
	./test tests/parsing/ex1.cicpp
	./test tests/parsing/ex2.cicpp
	./test tests/parsing/ex3.cicpp
	./test tests/parsing/ex4.cicpp
	./test tests/parsing/ex5.cicpp
	./test tests/parsing/ex6.cicpp
	./test tests/parsing/ex7.cicpp
	./test tests/parsing/ex8.cicpp
	./test tests/parsing/ex9.cicpp
	cd tests/runtime && make test_test

	make test_continuity

test_continuity:
	make build_test
	diff test _build/_test

