# makefile for lualib

LUA= ../..

include $(LUA)/config

EXTRA_DEFS= $(POPEN)

OBJS= liolib.o lmathlib.o lstrlib.o
SRCS= liolib.c lmathlib.c lstrlib.c

SLIB= $(LIB)/liblualib.a

# dynamic libraries only work for SunOs
DLIB= $(LIB)/liblualib.so.$(VERSION)

all: $(SLIB)

dynamic: $(DLIB)

$(SLIB): $(OBJS)
	ar rcu $@ $(OBJS)
	$(RANLIB) $(SLIB)

$(DLIB): $(OBJS)
	ld -o $@ $(OBJS)

clean:
	rm -f $(OBJS) $(SLIB) $(DLIB)

co:
	co -f -M $(SRCS)

klean:	clean
	rm -f $(SRCS)
