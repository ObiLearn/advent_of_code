ifeq ($(origin DEBUG), undefined)
else
	extra += -O0 -ggdb
endif

NUMBERS = 01 02 03 04 05 06
targets = $(foreach var,$(NUMBERS), $(var)a_task $(var)b_task)
runs = $(foreach var,$(NUMBERS), $(var)a_run $(var)b_run)

%:%.cpp
	g++ -std=c++17 $(extra) -o $@ $^

%_run: %_task
	@echo "running $^ ####################################"
	./$^ < $(subst b_task,,$(subst a_task,,$^))_input
	@echo "running $^ - end ##############################"

all: $(targets)
run: $(runs)

.PHONY: clean
clean:
	rm -fr $(targets)
