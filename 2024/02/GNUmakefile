.PHONY = exec fmt

exec: app
	./app

app: app.cpp ../util.hpp
	g++ -std=c++2b -o $@ $<

fmt: app.cpp
	clang-format-18 -i $?
