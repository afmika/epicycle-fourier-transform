INCLUDE_PATHS = -ID:\Libs\x86_64-w64-mingw32\include\SDL2
LIBRARY_PATHS = -LD:\Libs\x86_64-w64-mingw32\lib

LINKER_FLAGS = -std=c++14 -lmingw32 -lSDL2main -lSDL2
COMPILER_FLAGS = -w

OTHER_FILES = ./fourier/*.cpp

TEST_FILE = ./sandbox/dft.cpp
TEST_RESULT = bin/test

MAIN_FILE = ./main.cpp
MAIN_RESULT = bin/app

OPT_FILE = ./coef-compute.cpp
OPT_RESULT = bin/coef-compute

define compile_all
	echo $(3)
	g++ $(1) ${OTHER_FILES} ${INCLUDE_PATHS} ${LIBRARY_PATHS} ${COMPILER_FLAGS} ${LINKER_FLAGS} -o $(2)
endef

test:
	$(call compile_all,  ${TEST_FILE}, ${TEST_RESULT}, "Building tests...")
	$(TEST_RESULT)

build:
	$(call compile_all,  ${MAIN_FILE}, ${MAIN_RESULT}, "Building...")
	$(MAIN_RESULT)

optional:
	g++ ${OPT_FILE} ${OTHER_FILES} ${COMPILER_FLAGS} -o $(OPT_RESULT)
	$(OPT_RESULT)
