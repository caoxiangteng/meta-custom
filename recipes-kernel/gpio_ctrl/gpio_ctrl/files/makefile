SOURCES = $(wildcard *.c) 
OBJS = $(patsubst %.c, %.o, $(SOURCES))
 
CFLAGS := -Wall -O3 
 
LIB = libgpioctrl.so
 
all: $(LIB)
 
$(OBJS): $(SOURCES)
	$(CC) $(CFLAGS)   -fpic -c $< -o $@ 
 
$(LIB): $(OBJS)
	rm -f $@ 
	$(CC) $(CFLAGS) -shared -o $@ $(OBJS) 
	rm -f $(OBJS)
 
tags:
	ctags -R * 
 
clean: 
	rm -f $(OBJS) $(TARGET) $(LIB)
