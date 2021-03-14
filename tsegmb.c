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
	u32 pci_data;
	u32 stolen_data;
	u32 tseg_size;
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
	
	pci_read_config_dword(dev, 0xb8, &pci_data);
	printk(KERN_INFO "TSEGMB register data recieved is 0x%x.\n", pci_data);
	printk(KERN_INFO "TSEGMB is set to 0x%x.\n", (pci_data >> 1) << 1);
	
	
	//check base of GTT stolen memory
	pci_read_config_dword(dev, 0xb4, &stolen_data);
	printk(KERN_INFO "BGSM register data recieved is 0x%x.\n", stolen_data);
	printk(KERN_INFO "BGSM is set to 0x%x.\n", (stolen_data >> 1) << 1);
	
	tseg_size = ((stolen_data >> 1) << 1) - ((pci_data >> 1) << 1);
	printk(KERN_INFO "TSEG size is 0x%x.\n", tseg_size);

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
MODULE_DESCRIPTION("Get TSEG base address and size");
