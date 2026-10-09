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

clean:
	rm -rf $(OUT)

.PHONY: clean
