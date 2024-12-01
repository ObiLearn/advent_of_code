ifeq ($(origin DEBUG), undefined)
	extra += -O3
	buildtype = .debug
	buildtype_inactive = .release
else
	extra += -O0 -ggdb -fsanitize=address
	buildtype = .release
	buildtype_inactive = .debug
endif

includes = -I./lib/basics/include \
           -I./lib/math/include

NUMBERS = 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
targets = $(foreach var,$(NUMBERS), task_$(var)a task_$(var)b)
runall = $(foreach var,$(NUMBERS), run$(var)a run$(var)b)

run: $(runall)
build: $(targets)

.deps: lib/basics lib/math
	echo $^ > $@
lib:
	mkdir lib
lib/basics: lib
	git clone https://github.com/extcpp/basics lib/basics
lib/math: lib
	git clone https://github.com/extcpp/math lib/math

$(buildtype):
	rm -fr $(buildtype_inactive)
	touch $(buildtype)

task_%:: %_task.cpp .deps $(buildtype)
	g++ -std=c++17 $(CXXFLAGS) $(includes) $(extra) -o $@ $<

run%: task_%
	@echo "running $< ####################################################"
	./$< < $(subst b,,$(subst a,,$*))_input

.PHONY: clean
clean:
	rm -fr $(targets)
