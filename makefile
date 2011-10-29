#makefile skeleton from 
#https://gist.github.com/159461


PROJECT=CITS2230CpuSimulator
SOURCES=main.c fileToJobList.c jobScheduler.c printResults.c setup.c job.c \
	virtualCPU.c memory.c page.c htmloutput.c  \
	
LIBRARY=
INCPATHS=
LIBPATHS=
LDFLAGS=
CFLAGS=-c -Wall -std=c99 -ggdb
CC=gcc

# ------------ MAGIC BEGINS HERE -------------
#
#  # Automatic generation of some important lists
OBJECTS=$(SOURCES:.c=.o)
INCFLAGS=$(foreach TMP,$(INCPATHS),-I$(TMP))
LIBFLAGS=$(foreach TMP,$(LIBPATHS),-L$(TMP))

#Set up the output file names for the different output types
ifeq "$(LIBRARY)" "shared"
    BINARY=lib$(PROJECT).so
    LDFLAGS += -shared
else ifeq "$(LIBRARY)" "static"
    BINARY=lib$(PROJECT).a
else
    BINARY=$(PROJECT)
endif

all: $(SOURCES) $(BINARY)

$(BINARY): $(OBJECTS)
# Link the object files, or archive into a static library
ifeq "$(LIBRARY)" "static"
	ar rcs $(BINARY) $(OBJECTS)
else
	$(CC) $(LIBFLAGS) $(OBJECTS) $(LDFLAGS) -o $@
endif

.c.o:
	$(CC) $(INCFLAGS) $(CFLAGS) -fPIC $< -o $@

distclean: clean
	rm -f $(BINARY)

clean:
	rm -f $(OBJECTS)
