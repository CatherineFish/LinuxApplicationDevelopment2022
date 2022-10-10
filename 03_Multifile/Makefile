PARAMETER = Hello
PARAMS = just three parameters
TRASH = *.o *.so *.a result* prog prog-so prog-a
CONST_FUNC = const.o fun.o

all:    test

test:	prog prog-a prog-so
	./prog > result 2> /dev/null
	./prog-a > result_a 2> /dev/null
	./prog-so > result_so 2> /dev/null
	./prog $(PARAMETER) > result_1
	./prog-a $(PARAMETER) > result_1_a
	./prog-so $(PARAMETER) > result_1_so
	./prog $(PARAMS) > result_2
	./prog-a $(PARAMS) > result_2_a
	./prog-so $(PARAMS) > result_2_so
	cmp result result_a
	cmp result result_so
	cmp result_1 result_1_a
	cmp result_1 result_1_so
	cmp result_2 result_2_a
	cmp result_2 result_2_so

prog:	$(CONST_FUNC) prog.o

prog-a:	prog.o liboutput_static.a
	cc -L. $< -loutput_static -o $@

prog-so:	prog.o liboutput.so  
	cc -L. $< -loutput -o $@

fun.o:  outlib.h

liboutput_static.a:	$(CONST_FUNC)
	ar -rcs $@ $^

liboutput.so:	$(CONST_FUNC)
	ar -rcs $@ $^

clean:
	rm -f $(TRASH)

