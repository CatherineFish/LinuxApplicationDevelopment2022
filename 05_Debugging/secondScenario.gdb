set pagination off

set $cnt = 1

b range.c:10 if ($cnt++ >= 28 && $cnt <= 36)
command 1
	p {M, N, S, i}
    p $cnt
    cont
end

run -100 100 3 > /dev/null
quit