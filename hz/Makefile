all: $(TARGET) install

include platform.conf
include make.conf.$(PLATFORM)
include make.depend

VIEW_OBJS = i_console.o i_draw.o i_video.o i_system.o i_sprtet.o i_view.o

COMN_OBJS = bmp.o concmd.o game.o image.o main.o map.o \
	misc.o net.o sprite.o spritet.o vconsole.o view.o # sound.o

ALL_OBJS = $(COMN_OBJS) $(PLATFORM_OBJS)
OBJS = $(ALL_OBJS:%=obj/%)
COMP_OBJS = $(ALL_OBJS:%=obj\%)


.c.o:
	$(CC) -ggdb -c $< $(CFLAGS)

obj/%.o : %.cpp
	$(CPP) -ggdb -c $< $(CFLAGS) -o $@


platform.conf: 
	@echo "**************************************************"
	@echo "Choose a platform!"
	@echo "Create a file platform.conf with a line like 'PLATFORM=win'"
	@echo ""
	@exit 1

$(TARGET): $(OBJS)
	$(CPP) -ggdb -o $(TARGET) $(OBJS) $(LIBS)	

# view: $(VIEW_OBJS) $(COMN_OBJS)
#	$(CPP) -o view $(VIEW_OBJS) $(COMN_OBJS) $(LIBS)	


install: $(TARGET) 
	cp $(TARGET) target

clean: 
	rm -f $(TARGET) obj/*.o Makefile.bak make.depend

# this make depend needs to include all source files, not just those
# in the current directory.... - jeske

# someday this depend stuff should depend on these files
# but right now it dosn't even include all .cpp files....
# Makefile make.conf.$(PLATFORM)

make.depend: 
	@echo "*****"
	@echo "***** Generating make.depend"
	@echo "*****"
	@echo "# auto-generated make.depend" > make.depend.tmp
	$(CPP) -MM *.cpp $(CFLAGS) >> make.depend.tmp
	rm -f make.depend
	mv make.depend.tmp make.depend
	@echo "*****"

