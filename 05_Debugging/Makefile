TRASH = range result*

all:    test

test:	range
	gdb -x fiveScenario.gdb range --batch --quiet | grep -o '{.*}' > result_1.txt
	gdb -x secondScenario.gdb range --batch --quiet	| grep -o '{.*}' > result_2.txt
	cmp result_1.txt etalon_1.txt
	cmp result_2.txt etalon_2.txt

range:	range.c
	cc -O0 -g $< -o $@

clean:
	rm -f $(TRASH)

