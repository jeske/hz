# makefile for lua distribution (compiler)

LUA= ../..

include $(LUA)/config

INCS= -I$(INC) $(EXTRA_INCS) -I..
OBJS= dump.o luac.o print.o stubs.o
SRCS= dump.c luac.c print.c luac.h print.h stubs.c
T=$(BIN)/luac

all: $T

$T: $(OBJS) $(LIB)/liblua.a
	$(CC) -o $@ $(OBJS) -L$(LIB) -llua

clean:
	rm -f $(OBJS) $T

co:
	co -f -M $(SRCS)

klean:	clean
	rm -f $(SRCS)
