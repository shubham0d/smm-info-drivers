#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <sound/initval.h>
#include <asm/io.h>


#define MSR_MTRRcap			0x000000fe

#define IA32_MTRR_PHYBASE0		0x200
#define IA32_MTRR_PHYMASK0		0x201
#define IA32_MTRR_PHYBASE1		0x202
#define IA32_MTRR_PHYMASK1		0x203
static int my_init(void)
{

	

	uint64_t mtrr_base = 0x0;
	uint64_t mtrr_mask = 0x0;
	uint64_t mtrr_cap = 0x0;
	uint8_t  mtrr_supported = 0x0;
	uint8_t  fix_range_mtrr = 0x0;
	uint8_t  wc_support = 0x0;
	uint8_t smrr_support = 0x0;
    printk(KERN_INFO "Hello world.\n");
    rdmsrl(MSR_MTRRcap, mtrr_cap);
    // check the defined fields inside IA32_MTRRCAP
    // bit 7:0 MTRR_PHYBASEX can be used
	// bit 8 Fixed Range MTRR are supported
	// bit 10 WC supported
	// bit 11 SMRR supported
	// bit 11 PRMMR supported
    mtrr_supported = mtrr_cap & 0xFF;
    fix_range_mtrr = (mtrr_cap >> 8) & 0x1;
    wc_support = (mtrr_cap >> 10) & 0x1;
    smrr_support = (mtrr_cap >> 11) & 0x1;
    printk(KERN_INFO "MTRRCAP is %llx.\n", mtrr_cap);
    printk(KERN_INFO "Number of MTRR is %d.\n", mtrr_supported);
    printk(KERN_INFO "Fixed range MTRR support is %x.\n", fix_range_mtrr);
    printk(KERN_INFO "WC support is %x.\n", wc_support);
    printk(KERN_INFO "SMRR support is %x.\n", smrr_support);
    // check MTRRs value
    rdmsrl(IA32_MTRR_PHYBASE0, mtrr_base);
	rdmsrl(IA32_MTRR_PHYMASK0, mtrr_mask);
    printk(KERN_INFO "MTRR Physical base 0 is %llx.\n", mtrr_base);
    printk(KERN_INFO "MTRR Physical Mask 0 is %llx.\n", mtrr_mask);

	
    
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
MODULE_DESCRIPTION("MTRR info retrieve");
