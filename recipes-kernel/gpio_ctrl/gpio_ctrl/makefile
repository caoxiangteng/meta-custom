SOURCES = $(wildcard *.c) 
OBJS = $(patsubst %.c, %.o, $(SOURCES))
 
CFLAGS := -Wall -O3 
# INC_PATH =
# LIB_PATH =
 
LIB = libgpioctrl.so
 
all: $(LIB)
 
$(OBJS): $(SOURCES)
	$(CC) $(CFLAGS)  -g -fpic -c $< -o $@ $(INC_PATH) $(LIB_PATH)
 
$(LIB): $(OBJS)
	rm -f $@ 
	$(CC) $(CFLAGS) -shared -o $@ $(OBJS) 
	rm -f $(OBJS)
 
tags:
	ctags -R * 
 
clean: 
	rm -f $(OBJS) $(TARGET) $(LIB)
