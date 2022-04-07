#
#   DKU Operating System Lab
#           Lab2 (Hash Queue Lock Problem)
#           Student id : 
#           Student name : 
#
#   Makfeile :
#       - Makefile for lab2 compilation.
#

CC = gcc
INC = -I${CURDIR}/include/
CFLAGS = -g $(INC)
LDFLAGS = -lpthread

OBJS_LAB2 = lab2_sync.o lab2_sync_test.o include/lab2_timeval.o
OBJS_THREAD = lab2_thread_example.o
OBJS_TIME = lab2_time_example.o

SRCS = $(OBJS_LAB2:.o=.c) $(OBJS_THREAD: .o=.c) $(OBJS_TIME: .o=.c)

TARGET_LAB2 = lab2_sync
TARGET_THREAD = lab2_thread_example
TARGET_TIME = lab2_time_example

.SUFFIXES : .c .o

.c.o:
	@echo "Compiling lab2 Hash Queue Lock Problem $< ..."
	$(CC) -c $(CFLAGS) -o $@ $<

$(TARGET_LAB2) : $(OBJS_LAB2)
	$(CC) -o $(TARGET_LAB2) $(OBJS_LAB2) $(LDFLAGS)

$(TARGET_THREAD) : $(OBJS_THREAD)
	$(CC) -o $(TARGET_THREAD) $(OBJS_THREAD) $(LDFLAGS)

$(TARGET_TIME) : $(OBJS_TIME)
	$(CC) -o $(TARGET_TIME) $(OBJS_TIME) $(LDFLAGS)

all : $(TARGET_LAB2) $(TARGET_THREAD) $(TARGET_TIME)

dep : 
	gccmaedep $(INC) $(SRCS)

clean :
	@echo "Cleaning lab2 Hash Queue Lock Problem $< ..."
	rm -rf $(OBJS_LAB2) $(TARGET_LAB2) $(OBJS_THREAD) $(TARGET_THREAD) $(OBJS_TIME) $(TARGET_TIME)

new :
	$(MAKE) clean
	$(MAKE)


