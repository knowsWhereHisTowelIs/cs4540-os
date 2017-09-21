# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile
# https://stackoverflow.com/questions/3375697/useful-gcc-flags-for-c
appname := a2

CXX := gcc
CXXFLAGS := -std=c99 -Wall -Wstrict-prototypes -Wextra

OBJDIR := "objects"

srcfiles := $(shell find . -name "*.c")
objects  := $(patsubst %.c, %.o, $(srcfiles))

all: $(appname)

$(appname): $(objects)
	@mkdir -p $(OBJDIR) # make dir if doesn't exist
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)
	mv ./*.o $(OBJDIR)
	mv ./*.h.gch $(OBJDIR)

depend: .depend

.depend: $(srcfiles)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

cleanall: clean
	rm -f $(appname)
	@# @$(MAKE) clean

clean:
	@# remove object files and compiled headers
	rm -f $(objects) $(patsubst %.c, %.h.gch, $(srcfiles))

dist-clean: clean
	rm -f *~ .depend

include .depend
