#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <sound/initval.h>

static int my_init(void)
{
	struct pci_dev *dev;
	u8 pci_data;
    printk(KERN_INFO "Hello world.\n");
    //get pci device
    dev = pci_get_device(0x8086, 0x0a04, NULL);
    if (!dev)
    {
		printk(KERN_INFO "FAILED to get pci device\n");
		pci_dev_put(dev);
		return -ENODEV;
	}
	printk(KERN_INFO "Attached to the pci device\n");
	//read dword value from pci deevice
	
	pci_read_config_byte(dev, 0x88, &pci_data);
	printk(KERN_INFO "SMRAMC data recieved is 0x%x.\n", pci_data);
	

	// D_LCK bit is 4
	// pci_data = pci_data >> 4;
	//D_OPEN bit is 6
	// pci_data = pci_data >> 6;
	printk(KERN_INFO "D_LCK flag is set to %x.\n", (pci_data >> 4) & 1);
	printk(KERN_INFO "D_OPEN flag is set to %x.\n", (pci_data >> 6) & 1);

	//cleanup after use
	pci_dev_put(dev);

    
    return  0;
}
   
static void my_exit(void)
{
    printk(KERN_INFO "Goodbye world.\n");

    return;
}
   
module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shubham Dubey <shubham0d@protonmail.coms>");
MODULE_DESCRIPTION("SMRAM lock check");
