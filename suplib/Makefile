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
	# We also include -Wl,--no-as-needed since gcc is deciding we don't need libraries sometimes.  This appears to be the result of stupid issues with null pointers and gcc going "lul, you don't have any code anymore"
	$(CC) -Wall -Wextra -Wnull-dereference -Werror -shared -Wl,-rpath,$(RUNTIME_DIR)/lib/dynamic -Wl,-rpath,$(STAGE_DIR)/dynamic/ -L$(STAGE_DIR)/dynamic/ -Wl,--no-as-needed -luring $(CFLAGS) $(LIBURING_INC) -fpic -fpie -o $@ $^

clean:
	rm -f $(SO_FILE)
