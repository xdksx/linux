ifeq ($(KERNELRELEASE),)
   KERNELDIR?=/lib/modules/$(shell uname -r)/build
   PWD:=$(shell pwd)
modules: 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
clean:
	rm -rf *.o *~core .depend .*.cmd *.mod.c .tmp_versions
else
    obj-m:=testsyscall.o
endif
