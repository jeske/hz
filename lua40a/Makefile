# makefile for Lua hierarchy
# see INSTALL for installation instructions
# see file "config" for customization instructions

LUA= .

include $(LUA)/config

all co clean klean:
	cd include; $(MAKE) $@
	cd src; $(MAKE) $@
	cd src/luac; $(MAKE) $@
	cd src/lib; $(MAKE) $@
	cd src/lua; $(MAKE) $@

strip:
	strip bin/lua*

install: all strip
	mkdir -p $(INSTALL_BIN) $(INSTALL_INC) $(INSTALL_LIB) $(INSTALL_MAN)
	$(INSTALL) bin/* $(INSTALL_BIN)
	$(INSTALL) include/*.h $(INSTALL_INC)
	$(INSTALL) lib/lib* $(INSTALL_LIB)
	$(INSTALL) doc/*.man $(INSTALL_MAN)

