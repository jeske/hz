
include make.conf

COMN_OBJS = bmp.o concmd.o donuts.o game.o image.o luabase.o main.o map.o \
	misc.o net.o sprite.o spritet.o vconsole.o view.o # sound.o


UNIX_OBJS = i_console.o i_draw.o i_video.o i_system.o i_sprtet.o i_main.o

WIN_OBJS = hzres.o i_console.o i_draw.o i_video.o i_system.o i_sprtet.o \
           i_main.o hndlmgr.o drawhndl.o ddutil.o control.o platform.o

VIEW_OBJS = i_console.o i_draw.o i_video.o i_system.o i_sprtet.o i_view.o



# OBJS = $(COMN_OBJS) $(UNIX_OBJS)         # UNIX
# TARGET = xhz

OBJS = $(COMN_OBJS) $(WIN_OBJS)           # WINDOWS
TARGET = hz.exe


.c.o:
	$(CC) -c $(CFLAGS) $<

%.o : %.cpp
	$(CPP) -c $(CFLAGS) $<

all: $(TARGET) install

make.conf:
	@echo "Choose a platform!"
	@echo "Create a file 'make.conf' which includes the appropriate make.conf.\* file"
	@exit 1


$(TARGET): $(OBJS)
	$(CPP) -o $(TARGET) $(OBJS) $(LIBS)	

view: $(VIEW_OBJS) $(COMN_OBJS)
	$(CPP) -o view $(VIEW_OBJS) $(COMN_OBJS) $(LIBS)	


install: $(TARGET) 
	cp $(TARGET) target

clean: 
	rm -f $(TARGET) *.o Makefile.bak

hzres.o:
	windres os_win/hz.res hzres.o

dep:
	mv Makefile Makefile.bak
	awk -f depend.awk < Makefile.bak > Makefile
	echo '# DO NOT REMOVE THIS LINE' >> Makefile
	$(CPP) -MM $(CFLAGS) *.cpp os_unix/*.cpp >> Makefile
