#########################################################
##
## Makefile for HZ
##


# ---
# These four targets need to be above include lines

all: $(TARGET) install

clean: 
	rm -f obj/*.o Makefile.bak 

clobber: clean
	rm -f make.depend $(TARGET)

platform.conf: 
	@echo "**************************************************"
	@echo "Choose a platform!"
	@echo "Create a file platform.conf with a line like 'PLATFORM=win'"
	@echo ""
	@exit 1

# ---
# Include for a more modular makefile

include platform.conf
include make.conf.$(PLATFORM)
# include make.depend

VIEW_OBJS = i_console.o i_draw.o i_video.o i_system.o i_sprtet.o i_view.o

# vconsole overrides printf() so it should be first!

COMN_OBJS = vconsole.o bmp.o concmd.o game.o image.o main.o map.o \
	misc.o net.o sprite.o spritet.o s_lua.o s_hz.o view.o # sound.o

ALL_OBJS = $(COMN_OBJS) $(PLATFORM_OBJS)
OBJS = $(ALL_OBJS:%=obj/%)
COMP_OBJS = $(ALL_OBJS:%=obj\%)


obj/%.o : %.c
	$(CC) -ggdb -c $< $(CFLAGS) -o $@

obj/%.o : %.cpp
	$(CPP) -ggdb -c $< $(CFLAGS) -o $@



$(TARGET): $(OBJS)
	$(CPP) -ggdb -o $(TARGET) $(OBJS) $(LIBS)	

# view: $(VIEW_OBJS) $(COMN_OBJS)
#	$(CPP) -o view $(VIEW_OBJS) $(COMN_OBJS) $(LIBS)	


install: $(TARGET) 
	cp $(TARGET) target


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

