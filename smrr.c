#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <sound/initval.h>
#include <asm/io.h>


#define MSR_MTRRcap			0x000000fe

#define IA32_SMRR_PHYBASE		0x1F2
#define IA32_SMRR_PHYMASK		0x1F3
static int my_init(void)
{

	

	uint64_t smrr_base = 0x0;
	uint64_t smrr_mask = 0x0;
	uint64_t mtrr_cap = 0x0;
	uint8_t smrr_support = 0x0;
    printk(KERN_INFO "Hello world.\n");
    rdmsrl(MSR_MTRRcap, mtrr_cap);

	// bit 11 SMRR supported
    smrr_support = (mtrr_cap >> 11) & 0x1;
    printk(KERN_INFO "SMRR support is %x.\n", smrr_support);
    // check SMRRs value
    rdmsrl(IA32_SMRR_PHYBASE, smrr_base);
	rdmsrl(IA32_SMRR_PHYMASK, smrr_mask);
    printk(KERN_INFO "SMRR base is %llx.\n", (smrr_base >> 8) << 8);
    printk(KERN_INFO "SMRR mask is %llx.\n", smrr_mask);

	
    
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
MODULE_DESCRIPTION("Check SMRR");
