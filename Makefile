CC=gcc
CFLAGS=-std=c17 -Wall -Wextra -Wpedantic -MMD -MP
OUT=out
SOURCES=$(wildcard src/*.c)
OBJS=$(patsubst src/%.c,$(OUT)/%.o,$(SOURCES))
DEPS=$(patsubst $(OUT)/%.o,$(OUT)/%.d,$(OBJS))

$(OUT)/thex: $(OBJS) | $(OUT)
	$(CC) $^ -o $@

-include $(DEPS)

$(OUT)/%.o: src/%.c | $(OUT)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT):
	mkdir -p $(OUT)

# TESTS
TEST_OUT=test_out
FILTERED_OBJS=$(filter-out $(OUT)/thex.o,$(OBJS))

test: $(TEST_OUT)/thex_test
	$(TEST_OUT)/thex_test

$(TEST_OUT)/thex_test: $(FILTERED_OBJS) $(TEST_OUT)/thex_test.o | $(TEST_OUT)
	$(CC) $^ -o $@

$(TEST_OUT)/thex_test.o: ./tests/test_main.c | $(TEST_OUT)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OUT):
	mkdir -p $(TEST_OUT)

clean:
	rm -rf $(OUT) $(TEST_OUT)

.PHONY: clean
