ifeq ($(origin DEBUG), undefined)
else
	extra += -O0 -ggdb
endif

NUMBERS = 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
targets = $(foreach var,$(NUMBERS), $(var)a_task $(var)b_task)
runall = $(foreach var,$(NUMBERS), $(var)a_run $(var)b_run)

run: $(runall)

%::%.cpp
	g++ -std=c++17 $(extra) -o $@ $^

%_run: %_task
	@echo "running $^ ####################################################"
	./$^ < $(subst b_task,,$(subst a_task,,$^))_input

.PHONY: clean
clean:
	rm -fr $(targets)
