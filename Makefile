MODULE_NAME ?= driver
CFLAGS = -Iinclude
CC = gcc
SRC = src/user_program.c src/user_functions.c
OBJ = src/user_program.o src/user_functions.o
obj-m += $(MODULE_NAME).o

$(MODULE_NAME)-objs := src/driver.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

device:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
user:$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o user_program

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -f user_program
