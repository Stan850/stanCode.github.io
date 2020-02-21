.data

.align 2
audioStart: .incbin "shotSound.wav"
audioEnd: .word 0x0

.text

.global _start
_start:
    movia r6, 0xff203040	# Audio device base address: DE1-SoC
    movia r7, audioStart        # get the address to the start of the wav data
    addi r7, r7, 44             # skip 44 bytes (the header)
    movia r8, audioEnd          # keep the address to the end of the wav data

WaitForWriteSpace:
    ldwio r2, 4(r6)             # check write space for the left channel
    andhi r3, r2, 0xff00        
    beq r3, r0, WaitForWriteSpace  # if no space check from the beginning again
    andhi r3, r2, 0xff             # verify that there is space for writing in the right channel as well
    beq r3, r0, WaitForWriteSpace  # if there is none start checking all over again (both left and right should be free)
   
WriteTwoSamples:
    beq r7, r8, loop   # if true means we have reached the end of the data, I've set up to then loop infinitely 
    ldw r5, 0(r7)      # read a sample at the address r7 holds
    slli r5, r5, 16    # shift left by 16 bits bc Codec takes in 32, want LSBs to represent smaller frequencies
    stwio r5, 8(r6)    # write to LINEOUT FIFO for left data
    stwio r5, 12(r6)   # write to LINEOUT FIFO for right data
    addi r7, r7, 4     # go to the next sample, each is 32 bits in memory
    br WaitForWriteSpace

loop: br loop   