CC=g++-4.8
CFLAGS=-std=c++11 -lwiringPi

REC_BINARY=record.out
OUTFILE_PREFIX=test
NUM_FILES=100

EXEC_ARGS=$(OUTFILE_PREFIX) $(NUM_FILES)


all:
	$(CC) $(CFLAGS) record.cpp -o $(REC_BINARY)

threadTesting:
	$(CC) $(CFLAGS) threadTesting.cpp -o threadTesting.out


exec:
	raspivid -n -t 0 -o - | sudo ./$(REC_BINARY) $(EXEC_ARGS)

clean:
	rm $(REC_BINARY) *.out

delRecs:
	./delRecs.sh $(OUTFILE_PREFIX)
