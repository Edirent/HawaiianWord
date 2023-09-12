CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -Wall -Wextra -Werror -O1 -gdwarf-4 -fsanitize=address,undefined,implicit-conversion,local-bounds -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize-address-use-after-return=always

exec: bin/exec
tests: bin/tests

bin/exec: ./src/hawaiian_words.cc ./includes/functions.hpp ./src/functions.cc 
	$(CXX) $(CXX_FLAGS) ./src/hawaiian_words.cc ./src/functions.cc -o $@

bin/tests: ./tests/tests.cc ./includes/functions.hpp ./src/functions.cc
	$(CXX) $(CXX_FLAGS) ./tests/tests.cc ./src/functions.cc -o $@

.DEFAULT_GOAL := exec
.PHONY: exec tests clean

clean:
	rm -rf bin/*
