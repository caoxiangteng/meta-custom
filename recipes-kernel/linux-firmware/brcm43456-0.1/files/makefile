#LIBS:= -L/usr/lib/ -lgpioctrl -ldl
LIBS:= -L${D}${libdir} -lgpioctrl -ldl

SOURCES = gpio_ctrl_test.c
OBJS = $(patsubst %.c, %.o, $(SOURCES))
TARGET = gpio_ctrl_test

all:
	$(CC) ${CFLAGS}  $(LIBS) $(SOURCES) -o $(TARGET) 

clean: 
	rm -f $(OBJS) $(TARGET) 
