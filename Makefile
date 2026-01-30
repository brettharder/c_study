# Makefile — macOS + clang C project template (fixed main duplication)

CC      := clang
CSTD    := -std=c17
WARN    := -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion
INCS    := -Iinclude

# Build modes add to these.
CFLAGS  := $(CSTD) $(WARN) $(INCS)
LDFLAGS :=

BUILD_DIR := build
APP       := $(BUILD_DIR)/app
TEST_BIN  := $(BUILD_DIR)/tests
BENCH_BIN := $(BUILD_DIR)/bench

# --- Sources ---
APP_MAIN   := src/main.c
LIB_C      := $(filter-out $(APP_MAIN), $(wildcard src/*.c))

TEST_C     := $(wildcard tests/*.c)
BENCH_C    := $(wildcard bench/*.c)

# --- Objects ---
OBJ_LIB    := $(LIB_C:src/%.c=$(BUILD_DIR)/src_%.o)
OBJ_APP    := $(APP_MAIN:src/%.c=$(BUILD_DIR)/src_%.o) $(OBJ_LIB)

OBJ_TEST   := $(TEST_C:tests/%.c=$(BUILD_DIR)/tests_%.o) $(OBJ_LIB)
OBJ_BENCH  := $(BENCH_C:bench/%.c=$(BUILD_DIR)/bench_%.o) $(OBJ_LIB)

.PHONY: all debug release sanitize ubsan asan run test bench clean print-vars

all: debug

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# --- Compile rules ---
$(BUILD_DIR)/src_%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/tests_%.o: tests/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/bench_%.o: bench/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Build modes ---
debug: CFLAGS += -O0 -g
debug: $(APP)

release: CFLAGS += -O3 -DNDEBUG
release: $(APP)

sanitize: CFLAGS += -O0 -g -fsanitize=address,undefined -fno-omit-frame-pointer
sanitize: LDFLAGS += -fsanitize=address,undefined
sanitize: $(APP)

asan: CFLAGS += -O0 -g -fsanitize=address -fno-omit-frame-pointer
asan: LDFLAGS += -fsanitize=address
asan: $(APP)

ubsan: CFLAGS += -O0 -g -fsanitize=undefined -fno-omit-frame-pointer
ubsan: LDFLAGS += -fsanitize=undefined
ubsan: $(APP)

# --- Link targets ---
$(APP): $(OBJ_APP)
	$(CC) $^ -o $@ $(LDFLAGS)

$(TEST_BIN): CFLAGS += -O0 -g
$(TEST_BIN): $(OBJ_TEST)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BENCH_BIN): CFLAGS += -O3 -DNDEBUG
$(BENCH_BIN): $(OBJ_BENCH)
	$(CC) $^ -o $@ $(LDFLAGS)

# --- Convenience ---
run: debug
	$(APP)

test: $(TEST_BIN)
	$(TEST_BIN)

bench: $(BENCH_BIN)
	$(BENCH_BIN)

clean:
	rm -rf $(BUILD_DIR)

print-vars:
	@echo "CC=$(CC)"
	@echo "CFLAGS=$(CFLAGS)"
	@echo "APP_MAIN=$(APP_MAIN)"
	@echo "LIB_C=$(LIB_C)"
	@echo "OBJ_LIB=$(OBJ_LIB)"
