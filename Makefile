obj-m += led_blink.o

all:
	$(make) -C $(KERNEL_SRC) M=$(SRC)

modules_install:
	$(make) -C $(KERNEL_SRC) M=$(SRC) modules_install
	
