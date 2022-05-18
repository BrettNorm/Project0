
CC = gcc
CFLAGS = -g -Wall
OBJS = main.o tree.o
DEPS = tree.h node.h
TARGET = P0

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS): %.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
	find . \( -name "*.preorder" -o -name "*.postorder" -o -name "*.inorder" \) -delete