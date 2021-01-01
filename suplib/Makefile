CFLAGS := -O2 -fpie -fpic
INC_FLAGS := 
INSTALL_PREFIX :=

LIBURING_LIBS = $(shell PKG_CONFIG_PATH=$(STAGE_DIR)/lib/pkgconfig pkg-config liburing --libs)
LIBURING_INC  = $(shell PKG_CONFIG_PATH=$(STAGE_DIR)/lib/pkgconfig pkg-config liburing --cflags)

SO_FILE = liburingsup.so
C_FILES = library.c
TEST_FILE = library_test

all: $(SO_FILE)

install: $(SO_FILE)
	cp $(SO_FILE) $(INSTALL_PREFIX)/lib

$(SO_FILE): $(C_FILES)
	# We setup a few -rpaths for linking so that we ensure we get the one we just built early in the process
	$(CC) -Wall -Wextra -Wnull-dereference -Werror -shared -Wl,-rpath,$(RUNTIME_DIR)/lib/dynamic -Wl,-rpath,$(STAGE_DIR)/lib/ -Wl,-rpath,$(STAGE_DIR)/dynamic/ -L$(STAGE_DIR)/lib/ -L$(STAGE_DIR)/dynamic/ $(CFLAGS) $(LIBURING_INC) -o $@ $^ -luring

test: $(TEST_FILE)
	./$(TEST_FILE)

$(TEST_FILE): $(SO_FILE) $(TEST_FILE).c
	mkdir -p $(STAGE_DIR)/dynamic
	$(CC) -Wall -Wextra -Wnull-dereference -Werror -Wl,-rpath,./ -Wl,-rpath,$(RUNTIME_DIR)/lib/dynamic -Wl,-rpath,$(STAGE_DIR)/lib/ -L$(STAGE_DIR)/lib/ -L$(STAGE_DIR)/dynamic -L. $(CFLAGS) $(LIBURING_INC) -o $(TEST_FILE) $(TEST_FILE).c -luring -luringsup

xtest:
	echo TODO check objdump for undefined instructions and ldd and other things

clean:
	rm -f $(SO_FILE) $(TEST_FILE)
