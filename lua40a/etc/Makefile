# makefile for etc

LUA= ..

include $(LUA)/config

LIBLUA=$(LIB)/liblua.a
ALL= bin2c min trace ldbug.o lfback.o

x:
	@echo 'choose a target:' all $(ALL)

all: $(ALL)

bin2c: bin2c.c
	$(CC) $(CFLAGS) -o $@ $<

min: min.c $(LIBLUA)
	$(CC) $(CFLAGS) -o $@ $< -L$(LIB) -llua

trace: trace.c $(LIBLUA)
	$(CC) $(CFLAGS) -o $@ $< -L$(LIB) -llua -llualib -lm

ldbug.o: ldbug.c
	$(CC) $(CFLAGS) -c $<
	$(AR) $(LIBLUA) $@
	$(RANLIB) $(LIBLUA)
	@echo ''
	@echo To use $<, include ldbug.h instead of luadebug.h
	@echo ''

lfback.o: lfback.c
	$(CC) $(CFLAGS) -I../src -c $<
	$(AR) $(LIBLUA) $@
	$(RANLIB) $(LIBLUA)
	@echo ''
	@grep 'To use' $<
	@echo ''

$(LIBLUA):
	cd ../src; $(MAKE)

clean:
	rm -f $(ALL)
