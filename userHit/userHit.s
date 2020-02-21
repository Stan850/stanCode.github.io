.data

.align 2
audioHit: .incbin "userHit1.wav"
audioHitEnd: .word 0x0
loseStart: .incbin "Sad-Violin-MLG1.wav"
loseEnd: .word 0x0

.text

.global _start
_start:
    movia r6, 0xff203040	# Audio device base address: DE1-SoC
    movia r7, audioHit        # get the address to the start of the wav data
    addi r7, r7, 44             # skip 44 bytes (the header)
    movia r8, audioHitEnd          # keep the address to the end of the wav data
    movia r9, loseStart         # do the same above but for the sad song as well
    movia r10, loseEnd
    addi r9, r9, 44            

mainLoop: 
    bgt r7, r8, sadSong   # if we have finished playing the first sound, start playing the sad song
    ldw r4, 0(r7)         # load in a sample from userHit if not done
    addi r7, r7, 4        # otherwise go to the next sample of userHit, each is 32 bits in memory
    call insertCodec1
    br mainLoop           # go back to check if we are done, after this instruction you could do vga drawing 
sadSong:
    bgt r9, r10, loop1     # if sadSong is done playing then we're done here, kick out
    ldw r4, 0(r9)         # load in a sample from sad song
    addi r9, r9, 4
    call insertCodec1
    br sadSong            # first sound effect is done already, no need to start at mainLoop

insertCodec1:
 
WaitForWriteSpace1:
    ldwio r2, 4(r6)             # check write space for the left channel
    andhi r3, r2, 0xff00        
    beq r3, r0, WaitForWriteSpace1  # if no space check from the beginning again
    andhi r3, r2, 0xff             # verify that there is space for writing in the right channel as well
    beq r3, r0, WaitForWriteSpace1  # if there is none start checking all over again (both left and right should be free)
   
WriteTwoSamples1:
    slli r4, r4, 16    # shift left by 16 bits bc Codec takes in 32, want LSBs to represent smaller frequencies
    stwio r4, 8(r6)    # write to LINEOUT FIFO for left data
    stwio r4, 12(r6)   # write to LINEOUT FIFO for right data
    ret

loop1:
    movia r9, loseStart
    br sadSong  