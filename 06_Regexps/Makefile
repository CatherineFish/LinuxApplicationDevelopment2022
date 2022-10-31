CFLAGS = -Wall -pedantic -Wextra -Wno-unused-variable
TRASH = esub result*

all:    test

test:	esub
	echo 'string' | sed -E 's/regexp/substitution/' > result_etalon_1
	./esub 'regexp' 'substitution' 'string' > result_1
	diff result_1 result_etalon_1

	echo 'MyTest7String' | sed -E 's/(yT)(.*)([0-9])(.*ing)/\\\3-#\2##g\\\1 \0/' > result_etalon_2
	./esub '(yT)(.*)([0-9])(.*ing)' '\\\3-#\2##g\\\1 \0' 'MyTest7String' > result_2
	diff result_2 result_etalon_2

	./esub '(st)(ri)' '\2##\3' 'string' 2> result_3
	echo "Wrong pocket count" > result_etalon_3
	diff result_etalon_3 result_3


range:	esub.c
	cc $(CFLAGS) $< -o $@

clean:
	rm -f $(TRASH)

