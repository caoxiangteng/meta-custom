
SOURCES = $(wildcard *.c) 
OBJS = $(patsubst %.c, %.o, $(SOURCES))
 
LIBS:=  -lbluetooth-internal -lbluetooth
 
TARGET = ble_demo

all:
	$(CC) ${CFLAGS}  $(LIBS) $(SOURCES) -o $(TARGET) 

clean: 
	rm -f $(OBJS) $(TARGET) 
