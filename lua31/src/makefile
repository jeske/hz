# makefile for lua distribution (main library)

LUA= ..

include $(LUA)/config

OBJS=	\
	lapi.o \
	lauxlib.o \
	lbuffer.o \
	lbuiltin.o \
	ldo.o \
	lfunc.o \
	lgc.o \
	llex.o \
	lmem.o \
	lobject.o \
	lstate.o \
	lstring.o \
	lstx.o \
	ltable.o \
	ltm.o \
	lvm.o \
	lundump.o \
	lzio.o

SRCS=	\
	lapi.c \
	lauxlib.c \
	lbuffer.c \
	lbuiltin.c \
	ldo.c \
	lfunc.c \
	lgc.c \
	llex.c \
	lmem.c \
	lobject.c \
	lstate.c \
	lstring.c \
	lstx.c \
	ltable.c \
	ltm.c \
	lvm.c \
	lundump.c \
	lzio.c \
	lapi.h \
	lbuiltin.h \
	ldo.h \
	lfunc.h \
	lgc.h \
	llex.h \
	lmem.h \
	lobject.h \
	lopcodes.h \
	lparser.h \
	lstate.h \
	lstring.h \
	lstx.h \
	ltable.h \
	ltm.h \
	lundump.h \
	lvm.h \
	lzio.h

SLIB= $(LIB)/liblua.a

all: $(SLIB)

$(SLIB): $(OBJS)
	ar rcu $@ $(OBJS)
	$(RANLIB) $@

parser:
	#bison -o lstx.c -p luaY_ -d lua.stx
	yacc -d lua.stx
	rm -f lstx.c lstx.h
	sed -e 's/yy/luaY_/g' y.tab.c > lstx.c
	sed -e 's/yy/luaY_/g' y.tab.h > lstx.h
	rm -f y.tab.c y.tab.h

clean:
	rm -f $(OBJS) $(SLIB)

co:
	co -f -M $(SRCS)

klean:	clean
	rm -f $(SRCS)
