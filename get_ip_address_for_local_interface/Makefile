# 用法：
#   make        編譯出 get_ip_address
#   make run    編譯後執行，預設查 eth0（可改：make run IFACE=lo）
#   make clean  刪掉編譯產物

CC      := gcc
CFLAGS  := -Wall -Wextra -g -O2
TARGET  := get_ip_address
SRCS    := get_ip_address.c
IFACE   ?= eth0

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: run clean
run: $(TARGET)
	./$(TARGET) $(IFACE)

clean:
	rm -f $(TARGET)
