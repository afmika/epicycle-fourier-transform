INCLUDE_PATHS = -ID:\Bibliotheques\SDL2-2.0.20\x86_64-w64-mingw32\include\SDL2
LIBRARY_PATHS = -LD:\Bibliotheques\SDL2-2.0.20\x86_64-w64-mingw32\lib

LINKER_FLAGS = -std=c++14 -lmingw32 -lSDL2main -lSDL2
COMPILER_FLAGS = -w

OTHER_FILES = ./fourier/*.cpp

TEST_FILE = ./sandbox/complex.cpp
TEST_RESULT = bin/test

define compile_all
	echo $(3)
	g++ $(1) ${OTHER_FILES} ${INCLUDE_PATHS} ${LIBRARY_PATHS} ${COMPILER_FLAGS} ${LINKER_FLAGS} -o $(2)
endef

test:
	$(call compile_all,  ${TEST_FILE}, ${TEST_RESULT}, "Building tests...")
	$(TEST_RESULT)