CFLAGS = -Wall -pedantic -Wextra -Wno-unused-variable
TRASH = move result* *.so
DIFF = diff result_find.txt result_real.txt; rm result_find.txt result_real.txt
FIND_RESULT_CODE = tail -n1 result_trace.txt | grep -Eo '[0-9]{1,4}' > result_code.txt; rm result_trace.txt; diff result_code.txt result_current.txt; rm result_code.txt result_current.txt

all:    move

move:	move.c
	cc $(CFLAGS) $< -o $@

extra_remove.so:	extra_remove.c
	cc -shared -fPIC -o $@ $< -ldl
	
tests: test_OK test_NO_FILE test_NO_OPEN test_NO_READ test_NO_CLOSE

test_preload: extra_remove.so move
	LD_PRELOAD=`pwd`/extra_remove.so ./move PROTECT_test_LD_PRELOAD.txt result_test_not_deleted.txt
	find ./ PROTECT_test_LD_PRELOAD.txt
	diff PROTECT_test_LD_PRELOAD.txt result_test_not_deleted.txt
	

test_OK: move
	echo "This file will be deleted" > result_test_1.txt
	strace ./move result_test_1.txt result.txt 2> result_trace.txt 
	echo 0 > result_current.txt ; $(FIND_RESULT_CODE)
	echo "find: ‘result_test_1.txt’: No such file or directory" 2> result_find.txt
	find result_test_1.txt > result_real.txt; $(DIFF)
	rm result.txt
	

test_NO_FILE: move
	echo "This file will not be deleted" > result_test_2.txt
	-strace ./move result_test_2.txt 2> result_trace.txt
	echo 1 > result_current.txt ; $(FIND_RESULT_CODE)
	
	echo "result_test_2.txt" > result_find.txt 
	find result_test_2.txt > result_real.txt; $(DIFF)
	
	echo "find: ‘result.txt’: No such file or directory" 2> result_find.txt 
	find result.txt > result_real.txt; $(DIFF)
	rm result_test_2.txt

test_NO_OPEN: move
	echo "This file will not be deleted" > result_test_3.txt
	-strace -P result.txt -eopenat -efault=openat:error=EPERM ./move result_test_3.txt result.txt 2> result_trace.txt 
	echo 3 > result_current.txt ; $(FIND_RESULT_CODE)
	
	echo "result_test_3.txt" > result_find.txt ; 
	find result_test_3.txt > result_real.txt; $(DIFF)
	
	echo "find: ‘result.txt’: No such file or directory" > result_find.txt
	find result.txt 2> result_real.txt; $(DIFF)
	rm result_test_3.txt

test_NO_READ: move
	echo "This file will not be deleted" > result_test_5.txt
	-strace -P result_test_5.txt -eread -efault=read:error=EPERM ./move result_test_5.txt result.txt 2> result_trace.txt 
	echo 5 > result_current.txt ; $(FIND_RESULT_CODE)

	echo "result_test_5.txt" > result_find.txt
	find result_test_5.txt > result_real.txt; $(DIFF)
	
	echo "find: ‘result.txt’: No such file or directory" > result_find.txt 
	find result.txt 2> result_real.txt; $(DIFF)
	rm result_test_5.txt

test_NO_CLOSE: move
	echo "This file will not be deleted" > result_test_7.txt
	-strace -eclose -efault=close:error=EPERM:when=4 ./move result_test_7.txt result.txt 2> result_trace.txt 
	echo 7 > result_current.txt ; $(FIND_RESULT_CODE)

	echo "result_test_7.txt" > result_find.txt
	find result_test_7.txt > result_real.txt; $(DIFF)
	
	echo "find: ‘result.txt’: No such file or directory" > result_find.txt 
	find result.txt 2> result_real.txt; $(DIFF)
	rm result_test_7.txt

clean:
	rm -f $(TRASH)



