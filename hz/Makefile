
all: $(TARGET) install

include platform.conf
include make.conf.$(PLATFORM)
include make.depend

VIEW_OBJS = i_console.o i_draw.o i_video.o i_system.o i_sprtet.o i_view.o

COMN_OBJS = bmp.o concmd.o donuts.o game.o image.o luabase.o main.o map.o \
	misc.o net.o sprite.o spritet.o vconsole.o view.o # sound.o

ALL_OBJS = $(COMN_OBJS) $(PLATFORM_OBJS)
OBJS = $(ALL_OBJS:%=obj/%)
COMP_OBJS = $(ALL_OBJS:%=obj\%)


.c.o:
	$(CC) -c $(CFLAGS) $<

obj/%.o : %.cpp
	$(CPP) -c $(CFLAGS) $< -o $@


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
	rm -f $(TARGET) obj/*.o Makefile.bak

# this make depend needs to include all source files, not just those
# in the current directory.... - jeske

make.depend: Makefile make.conf.$(PLATFORM)
	@echo "*****"
	@echo "***** Generating make.depend"
	@echo "*****"
	@echo "# auto-generated make.depend" > make.depend.tmp
	$(CPP) -MM $(CFLAGS) *.cpp >> make.depend.tmp
	rm -f make.depend
	mv make.depend.tmp make.depend
	@echo "*****"

