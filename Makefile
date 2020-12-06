ifeq ($(origin DEBUG), undefined)
	extra += -O3
else
	extra += -O0 -ggdb
endif

NUMBERS = 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
targets = $(foreach var,$(NUMBERS), task_$(var)a task_$(var)b)
runall = $(foreach var,$(NUMBERS), run$(var)a run$(var)b)

run: $(runall)
build: $(targets)

task_%:: %_task.cpp
	g++ -std=c++17 $(extra) -o $@ $^

run%: task_%
	@echo "running $< ####################################################"
	./$< < $(subst b,,$(subst a,,$*))_input

.PHONY: clean
clean:
	rm -fr $(targets)
