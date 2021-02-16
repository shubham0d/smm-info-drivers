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
	//Offset 0x88 in DRAM controller
	pci_read_config_byte(dev, 0x88, &pci_data);
	printk(KERN_INFO "SMRAMC data recieved is 0x%x.\n", pci_data);
	
	
	// Bit 3 in SMRAMC is G_SMRAME
	pci_data = pci_data >> 3;
	pci_data = pci_data & 0x1;
	printk(KERN_INFO "G_SMRAME is set to %x.\n", pci_data);

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
MODULE_DESCRIPTION("SMRAMC check");
