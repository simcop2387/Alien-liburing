CFLAGS := -O2 -fpie -fpic
INC_FLAGS := 
INSTALL_PREFIX :=

LIBURING_LIBS = $(shell PKG_CONFIG_PATH=$(STAGE_DIR)/lib/pkgconfig pkg-config liburing --libs)
LIBURING_INC  = $(shell PKG_CONFIG_PATH=$(STAGE_DIR)/lib/pkgconfig pkg-config liburing --cflags)

SO_FILE = liburingsup.so
C_FILES = library.c

all: $(SO_FILE)

install: $(SO_FILE)
	cp $(SO_FILE) $(INSTALL_PREFIX)/lib

$(SO_FILE): $(C_FILES)
	# We setup a few -rpaths for linking so that we ensure we get the one we just built early in the process
	$(CC) -Wall -Wextra -Wnull-dereference -Werror -shared -Wl,-rpath,$(RUNTIME_DIR)/lib/dynamic -Wl,-rpath,$(STAGE_DIR)/lib/ -L$(STAGE_DIR)/lib/ -luring $(CFLAGS) $(LIBURING_INC) -fpic -fpie -o $@ $^

test: $(SO_FILE) library_test.c
	$(CC) -Wall -Wextra -Wnull-dereference -Werror -Wl,-rpath,./ -Wl,-rpath,$(RUNTIME_DIR)/lib/dynamic -Wl,-rpath,$(STAGE_DIR)/lib/ -L$(STAGE_DIR)/lib/ -L. -Wl,--no-as-needed -luring -luringsup $(CFLAGS) $(LIBURING_INC) -fpic -fpie -o library_test library_test.c
	./library_test

xtest:
	echo TODO check objdump for undefined instructions and ldd and other things

clean:
	rm -f $(SO_FILE)
