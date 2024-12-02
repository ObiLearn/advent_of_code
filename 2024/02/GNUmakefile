.PHONY = exec fmt
CPPFILES := app.cpp
CXXFLAGS := -Wall -Wextra -fno-omit-frame-pointer -ggdb -O0 -fsanitize=address

exec: app
	./app

app: $(CPPFILES)
	g++ -std=c++2b $(CXXFLAGS) -o $@ $?

fmt: $(CPPFILES)
	clang-format-18 -i $?
