#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <sound/initval.h>
#include <asm/io.h>


#define MSR_SMI_COUNT			0x00000034


static int my_init(void)
{

	
    uint8_t smm_response  = 0x0;
	uint32_t smi_count = 0x0;
    printk(KERN_INFO "Hello world.\n");
    
    // check smi count
    rdmsrl(MSR_SMI_COUNT, smi_count);
    printk(KERN_INFO "SMI count earlier is %x.\n", smi_count);
    //check the initial value recieve from 0xB3 port
	smm_response = inb(0xb2);
	
	printk(KERN_INFO "data recieved from port 0xb2 is %x.\n", smm_response);
	//write to 0xB2 port to cause SMI
	outb(0x80, 0xb2);
	// Check the respose in port 0xB3
	smm_response = inb(0xb2);
	
	printk(KERN_INFO "data recieved after is %x.\n", smm_response);
	
	//smi_count = x86_get_msr(0x34);
	//smi_count = __rdmsr1(0x34);
	rdmsrl(MSR_SMI_COUNT, smi_count);
    printk(KERN_INFO "SMI count later is- %x.\n", smi_count);
    
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
MODULE_DESCRIPTION("SMM interaction");
