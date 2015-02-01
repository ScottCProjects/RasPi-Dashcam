CC=g++-4.8
CFLAGS=-std=c++11 -lwiringPi
SRC_DIR=

REC_BINARY=record.out
OUTFILE_PREFIX=test
NUM_FILES=100

EXEC_ARGS=$(OUTFILE_PREFIX) $(NUM_FILES)


all:
	$(CC) $(CFLAGS) record.cpp -o $(REC_BINARY)

threadTesting:
	$(CC) $(CFLAGS) threadTesting.cpp -o threadTesting.out


exec:
	raspivid -n -t 0 -b 10000 -g 1 -o - | tee test.h264 | sudo ./$(REC_BINARY) $(EXEC_ARGS)

concat:
	./concatAll.sh $(OUTFILE_PREFIX) $(NUM_FILES)

clean:
	rm $(REC_BINARY) *.out

delRecs:
	./delRecs.sh $(OUTFILE_PREFIX)
