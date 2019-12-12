LIBS:= -lgpioctrl -ldl

SOURCES1 = gpio_ctrl_test.c
OBJS1 = $(patsubst %.c, %.o, $(SOURCES))
TARGET1 = gpio_ctrl_test

SOURCES2 = brcm_patchram_plus.c
OBJS1 = $(patsubst %.c, %.o, $(SOURCES))
TARGET2 = brcm_patchram_plus

all:
	$(CC) ${CFLAGS}  $(LIBS) $(SOURCES1) -o $(TARGET1) 
	$(CC) ${CFLAGS}  $(SOURCES2) -o $(TARGET2) 

clean: 
	rm -f $(OBJS) $(TARGET) 
