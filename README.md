# smm-info-drivers
Sample linux modules to retrieve SMM related information. <br/>
Used for blog: https://nixhacker.com/digging-into-smm/ <br/>
<br/>
**Files Description**

`cause_smi.c` - Cause SMI and check SMI count. <br/>
`d_lck.c` - check the D_LCK and D_OPEN bit which defines if the SMM is protected or not. <br/>
`tsegmb.c` - find the TSEG area base address and size. <br/>
`smrr.c` - check SMRR base and mask. <br/>
`mtrr.c` - check MTRR base and mask. <br/>

