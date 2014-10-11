CC=g++-4.8
CFLAGS=-std=c++11 -lwiringPi
REC_BINARY=record.out
OUTFILE_PREFIX=test


all:
	$(CC) $(CFLAGS) record.cpp -o $(REC_BINARY)

threadTesting:
	$(CC) $(CFLAGS) threadTesting.cpp -o threadTesting.out


exec:
	raspivid -n -t 99999 -o - | sudo ./$(REC_BINARY) $(OUTFILE_PREFIX)

clean:
	rm $(REC_BINARY) *.out

delRecs:
	./delRecs.sh $(OUTFILE_PREFIX)
