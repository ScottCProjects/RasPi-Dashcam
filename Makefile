CC=g++-4.8
CFLAGS=-std=c++11 -lwiringPi

SRC_DIR=src
REC_DIR=recordings
BIN_DIR=bin

REC_BINARY=$(BIN_DIR)/record.out
OUTFILE_PREFIX=recordings/test
NUM_FILES=100


EXEC_ARGS=$(OUTFILE_PREFIX) $(NUM_FILES)


all:
	$(CC) $(CFLAGS) $(SRC_DIR)/record.cpp -o $(REC_BINARY)

exec:
	raspivid -n -t 0 -b 10000 -g 1 -o - | sudo $(REC_BINARY) $(EXEC_ARGS)

concat:
	$(SRC_DIR)/concatAll.sh $(OUTFILE_PREFIX) $(NUM_FILES)

clean:
	rm $(REC_BINARY)

delRecs:
	$(SRC_DIR)/delRecs.sh $(OUTFILE_PREFIX)
