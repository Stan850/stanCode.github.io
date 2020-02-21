
.equ IRQ, 0x042
.equ ADDR_PUSHBUTTONS, 0xff200050
.equ ADDR_AUDIO, 0xff203040

.data
 
.align 2
audioStart: .incbin "Darude - Sandstorm2.wav"
audioEnd: .word 0x0
zeroSpace: .space 4
effectStart: .incbin "shotSound.wav"
effectEnd: .word 0x0
zeroSpace2: .space 4
hitStart: .incbin "laserHitSound1.wav"
hitEnd: .word 0x0
check: .word 0x0

.global _start
.section .text
_start:
  movia sp, 0x7ffffffc
  movia r6, ADDR_AUDIO	      # LEDs base address: DE1-SoC
  movia r2, ADDR_PUSHBUTTONS  # pushButtons' base address
  movia r3, 0x0009	      # Enable interrupt mask = 1001
  movi r16, 0x01              # will be used for checking push button 0
  movi r17, 0x08              # will be used for checking push button 3
  movia r8, audioStart
  addi r8, r8, 44             # skip 44 bytes (header)
  movia r9, audioEnd
  movia r10, effectStart
  addi r10, r10, 44           # skip 44 bytes (header)
  movia r11, effectEnd
  movia r14, hitStart
  addi r14, r14, 44           # skip 44 bytes (header)
  movia r15, hitEnd

  stwio r3, 8(r2)             # Enable interrupts on pushbuttons 0 and 3
  stwio r3, 12(r2)            # Clear edge capture register to prevent unexpected interrupt
  ldwio r7, 0(r6)             # read in stream of bits from control register
  ori r7, r7, 0x02                
  stwio r7, 0(r6)             # enable write interrupt

  movia r2, IRQ
  wrctl ctl3,r2   # Enable bits 1 and 6 - Pushbuttons use IRQ 1 and Audio uses IRQ 6

  movia r2,1 
  wrctl ctl0,r2   # Enable global Interrupts on Processor (PIE = 1)
  
loop: 
    movia r12, 0x1
    wrctl ctl0, r12
    br loop

.section .exceptions, "ax"
.global audio_ISR 

audio_ISR:              # nested interrupt
   subi sp, sp, 12      # push back the stack
   stw et, (sp)         # push et to the stack
   rdctl et, estatus 
   stw et, 4(sp)        # push estatus to the stack
   stw ea, 8(sp)        # push ea (return address) to the stack

   rdctl et, ipending   # check to see if interrupt request is pending for audio first
   andi et, et, 0x040       # mask out bits (look for bit 6)
   bne et, r0, Serve_Audio # Serve audio interrupt if requested

checkButton:
   rdctl et, ipending   # if not requested for audio, check the interrupt request for pushButtons
   andi et, et, 0x0002  # mask out bits  (look for bit 1)
   bne et, r0, Serve_Buttons 
   br exit              # exit if none are pending
 
Serve_Audio:
   ldwio et, 0(r6)     # need to check which type of interrupt is active, read or write
   andi et, et, 0x200
   beq et, r0, checkButton  # if we don't have a write interrupt, then check the pending status for the button
   movia et, check     # this location will contain like a bool variable to determine which samples should be played
   ldw et, (et)
   beq et, r0, playBackground         # if the value at check == 0, then play background music only
   beq et, r16, playBackgrdShotSound  # if the value at check == 0001, then play shot music only
   br playBackgrdHitSound             # otherwise play Hit sound

playBackground:
   bgt r8, r9, audioOff  # if we reached the end of background music, stop audio completely
   ldw r4, 0(r8)
   call insertCodec      # otherwise play background music
   addi r8, r8, 4        # move to the next sample, then exit
   br exit 

audioOff:
   ldwio et, 0(r6)       # get the stream of bits
   xori et, et, 0x02     # turn bit 1 from control reg from 1 to 0        
   stwio et, 0(r6)       # disable write interrupts
   movia r2, ADDR_PUSHBUTTONS
   ldwio et, 8(r2)    
   andi et, et, 0x0
   stwio et, 8(r2)       # disable all pushButtons
   br exit

playBackgrdShotSound:
   bgt r10, r11, resetEffect  # if we reached the end of the sound effect, start it over
   ldw et, 0(r8)              # load current sample from background music
   ldw r4, 0(r10)             # load current sample from sound effect
   add r4, et, r4             # add them together to have multiple sounds
   call insertCodec
   addi r8, r8, 4              # move to the next background music sample
   addi r10, r10, 4            # move to the next sound effect sample
   br exit

playBackgrdHitSound:
   bgt r14, r15, resetHitEffect  # if we reached the end of the hit sound effect, start it over
   ldw et, 0(r8)              # load current sample from background music
   ldw r4, 0(r14)             # load current sample from hit sound effect
   add r4, et, r4             # add them together to have multiple sounds
   call insertCodec
   addi r8, r8, 4              # move to the next background music sample
   addi r14, r14, 4            # move to the next hit sound effect sample
   br exit

resetEffect: 
   movia r10, effectStart      # start at the beginning of the sound effect if done playing
   movia et, check            
   stw r0, (et)               # set the value in the check address to 0 so no sound effects are played till push button is pushed
   br exit

resetHitEffect:
   movia r14, hitStart       # start at the beginning of the hit sound effect if done playing
   movia et, check            
   stw r0, (et)               # set the value in the check address to 0 so no sound effects are played till push button is pushed
   br exit

Serve_Buttons:
   #movi et, 0x1              # re-enable interrupts (set PIE == 1 again for nested interrupts)
   #wrctl status, et

   movia r2, ADDR_PUSHBUTTONS   
   ldwio et, 12(r2)            # read in the bits from the edge capture reg to know which button is pressed
   andi et, et, 0x09           # mask out to check which ones are high 
   beq et, r16, enabShot       # if push button 0 is pressed load shot sound
   br enabHit                  # otherwise load hit sound
enabShot:
   movia et, check      
   stw r16, 0(et)
   br exit
enabHit:
   movia et, check           # setting check to 0001, now shot sounds can be played with background
   stw r17, 0(et)            # setting check to 1000, now hit sounds can be played with background
   br exit
   
exit:
   wrctl status, zero        # disable interrupts while restoring
   movia et, ADDR_PUSHBUTTONS
   addi r12, r0, 0x09
   stwio r12, 12(et)             # need to clear edge capture register before exiting interrupt handler 
   ldw et, (sp)
   wrctl estatus, et            # restore everything from stack
   ldw et, 4(sp)
   ldw ea, 8(sp)
   addi sp, sp, 12
   subi ea, ea, 4 
   eret                         # return from ISR
   
insertCodec:
    subi sp, sp, 8  # need to push r2 and r3 onto the stack so that they aren't overwritten
    stw r2, (sp)
    stw r3, 4(sp)

WaitForWriteSpace:
    ldwio r2, 4(r6)             # check write space for the left channel
    andhi r3, r2, 0xff00        
    beq r3, r0, WaitForWriteSpace  # if no space check from the beginning again
    andhi r3, r2, 0xff             # verify that there is space for writing in the right channel as well
    beq r3, r0, WaitForWriteSpace  # if there is none start checking all over again (both left and right should be free)
   
WriteTwoSamples:
    slli r4, r4, 16    # shift left by 16 bits bc Codec takes in 32, want LSBs to represent smaller frequencies
    stwio r4, 8(r6)    # write to LINEOUT FIFO for left data
    stwio r4, 12(r6)   # write to LINEOUT FIFO for right data

    ldw r2, (sp)       # restore r2, r3 and the stack
    ldw r3, 4(sp)
    addi sp, sp, 8
    ret                # return
