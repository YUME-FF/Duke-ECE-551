CFLAGS = -Wall -Werror -pedantic -std=gnu99
maxSeq:maxSeq.c test-subseq.c
	gcc $(CFLAGS) -c maxSeq.c test-subseq.c
.PHONY:clean
clean:
	rm -f *~ *.o maxSeq
