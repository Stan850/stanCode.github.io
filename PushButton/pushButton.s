
.equ IRQ_PUSHBUTTONS, 0x02
.equ ADDR_PUSHBUTTONS, 0xff200050
.equ ADDR_LEDs, 0xff200000

.data

.global _start
.section .text
_start:

  movia r6, ADDR_LEDs	      # LEDs base address: DE1-SoC
  movia r2, ADDR_PUSHBUTTONS  # pushButtons' base address
  movia r3, 0x0001	              # Enable interrrupt mask = 0001
  stwio r0, 0(r6)             # turn LEDs off first
  stwio r3,8(r2)              # Enable interrupts on pushbutton 0
  stwio r3,12(r2)             # Clear edge capture register to prevent unexpected interrupt

  movia r2, IRQ_PUSHBUTTONS
  wrctl ctl3,r2   # Enable bit 1 - Pushbuttons use IRQ 1

  movia r2,1 
  wrctl ctl0,r2   # Enable global Interrupts on Processor (PIE = 1)

loop: 
    br loop

.section .exceptions, "ax" 

pushButton_ISR:
   rdctl et, ipending   # check to see if interrupt request is pending for pushbuttons
   andi et, et, 0x0002  # mask out bits
   beq et, r0, exit     # exit if not pending
 
   movia et, ADDR_LEDs 
   stwio r3, (et)       # turn LEDs on

exit:
   subi ea, ea, 4
   movia et, ADDR_PUSHBUTTONS
   stwio r3, 12(et)             # need to clear edge capture register before exiting interrupt handler 
   eret
   
 