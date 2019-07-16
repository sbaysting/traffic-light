CC=gcc
INC= -I./include/common
SRC= ./src/common/heap_mgr.c \
	 ./src/common/linked_list.c

default:
	$(CC) $(INC) $(SRC) -o test

clean:
	rm -f test
