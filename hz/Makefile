
include make.conf

COMN_OBJS = bmp.o concmd.o donuts.o game.o image.o luabase.o main.o map.o \
	misc.o net.o sprite.o spritet.o vconsole.o view.o # sound.o

UNIX_OBJS = i_console.o i_draw.o i_video.o i_system.o i_sprtet.o i_main.o
VIEW_OBJS = i_console.o i_draw.o i_video.o i_system.o i_sprtet.o i_view.o
OBJS = $(COMN_OBJS) $(UNIX_OBJS)

.c.o:
	$(CC) -c $(CFLAGS) $<

%.o : %.cpp
	$(CPP) -c $(CFLAGS) $<

all: xhz install

make.conf:
	@echo "Choose a platform!"
	@echo "Create a file 'make.conf' which includes the appropriate make.conf.\* file"
	@exit 1


xhz: $(OBJS)
	$(CC) -o xhz $(OBJS) $(LIBS)	

view: $(VIEW_OBJS) $(COMN_OBJS)
	$(CC) -o view $(VIEW_OBJS) $(COMN_OBJS) $(LIBS)	


install: xhz
	cp xhz target

clean: 
	rm -f xhz *.o Makefile.bak

dep:
	mv Makefile Makefile.bak
	awk -f depend.awk < Makefile.bak > Makefile
	echo '# DO NOT REMOVE THIS LINE' >> Makefile
	$(CC) -MM $(CFLAGS) *.cpp os_unix/*.cpp >> Makefile
