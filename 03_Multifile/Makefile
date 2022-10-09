PARAMETR = Hello
PARAMS = just three parametrs
TRASH = *.o *.so *.a result* prog prog-so prog-a
CONST_FUNC = const.o fun.o

all:    test

test:	prog prog-a prog-so
	./prog 2> result
	./prog-a 2> result_a
	./prog-so 2> result_so
	./prog $(PARAMETR) > result_1
	./prog-a $(PARAMETR) > result_1_a
	./prog-so $(PARAMETR) > result_1_so
	./prog $(PARAMS) > result_2
	./prog-a $(PARAMS) > result_2_a
	./prog-so $(PARAMS) > result_2_so
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

