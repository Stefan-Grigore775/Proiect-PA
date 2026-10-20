CC := cc
CFLAGS := -std=c11 -O2 -Wall -Wextra -Werror -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700
CHECKER_DIR := checker
CHECKER_SRC := $(CHECKER_DIR)/src
CHECKER_INC := $(CHECKER_DIR)/include
BUILD_DIR := build

COMMON_SRCS := $(CHECKER_SRC)/common.c

.PHONY: all clean

STUDENT_SRCS := \
	src/entity.c \
	src/graph.c \
	src/bst.c \
	src/queue.c \
	src/heap.c \
	src/query.c \
	src/main.c

PUBLIC_HARNESS_SRCS := \
	tests/public/harness/pas1_harness.c \
	tests/public/harness/pas2_harness.c \
	tests/public/harness/pas3_harness.c \
	tests/public/harness/pas4_harness.c

.PHONY: all clean public-test private-test

all: \
	$(BUILD_DIR)/check_pas1 \
	$(BUILD_DIR)/check_pas2 \
	$(BUILD_DIR)/check_pas3 \
	$(BUILD_DIR)/check_pas4

$(BUILD_DIR)/student_kg: $(STUDENT_SRCS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -Iinclude $^ -o $@

$(BUILD_DIR)/public_pas1: tests/public/harness/pas1_harness.c src/entity.c src/graph.c src/bst.c src/queue.c src/heap.c src/query.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -Iinclude $^ -o $@

$(BUILD_DIR)/public_pas2: tests/public/harness/pas2_harness.c src/entity.c src/graph.c src/bst.c src/queue.c src/heap.c src/query.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -Iinclude $^ -o $@

$(BUILD_DIR)/public_pas3: tests/public/harness/pas3_harness.c src/entity.c src/graph.c src/bst.c src/queue.c src/heap.c src/query.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -Iinclude $^ -o $@

$(BUILD_DIR)/public_pas4: tests/public/harness/pas4_harness.c src/entity.c src/graph.c src/bst.c src/queue.c src/heap.c src/query.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -Iinclude $^ -o $@

public-test: \
	$(BUILD_DIR)/public_pas1 \
	$(BUILD_DIR)/public_pas2 \
	$(BUILD_DIR)/public_pas3 \
	$(BUILD_DIR)/public_pas4
	./tests/public/run_public_tests.sh

private-test:
	@echo "Testele private nu sunt disponibile in acest repository."

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/check_pas1: $(CHECKER_SRC)/check_pas1.c $(COMMON_SRCS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(CHECKER_INC) $^ -o $@

$(BUILD_DIR)/check_pas2: $(CHECKER_SRC)/check_pas2.c $(COMMON_SRCS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(CHECKER_INC) $^ -o $@

$(BUILD_DIR)/check_pas3: $(CHECKER_SRC)/check_pas3.c $(COMMON_SRCS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(CHECKER_INC) $^ -o $@

$(BUILD_DIR)/check_pas4: $(CHECKER_SRC)/check_pas4.c $(COMMON_SRCS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(CHECKER_INC) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)
