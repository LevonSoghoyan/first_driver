MODULE_NAME ?= driver

obj-m += $(MODULE_NAME).o

$(MODULE_NAME)-objs := src/driver.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc src/user_program.c src/user_functions.c -o user_program

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -f user_program
