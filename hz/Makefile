
include platform.conf

include make.conf.$(PLATFORM)

VIEW_OBJS = i_console.o i_draw.o i_video.o i_system.o i_sprtet.o i_view.o

COMN_OBJS = bmp.o concmd.o donuts.o game.o image.o luabase.o main.o map.o \
	misc.o net.o sprite.o spritet.o vconsole.o view.o # sound.o

OBJS = $(COMN_OBJS) $(PLATFORM_OBJS)

.c.o:
	$(CC) -c $(CFLAGS) $<

%.o : %.cpp
	$(CPP) -c $(CFLAGS) $<

all: $(TARGET) install

platform.conf: 
	@echo "**************************************************"
	@echo "Choose a platform!"
	@echo "Create a file platform.conf with a line like 'PLATFORM=win'"
	@echo ""
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

ifeq ($(PLATFORM),linux)
# depend does not work right on Windows right now...
dep:
	mv Makefile Makefile.bak
	awk -f depend.awk < Makefile.bak > Makefile
	echo '# DO NOT REMOVE THIS LINE' >> Makefile
	$(CPP) -MM $(CFLAGS) *.cpp os_unix/*.cpp >> Makefile
endif
