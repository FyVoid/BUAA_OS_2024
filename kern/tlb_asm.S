#include <asm/asm.h>

LEAF(tlb_out)
.set noreorder
	mfc0    t0, CP0_ENTRYHI		# save ENTRYHI
	mtc0    a0, CP0_ENTRYHI		# write tlb key into ENTRYHI
	nop							# nop
	/* Step 1: Use 'tlbp' to probe TLB entry */
	/* Exercise 2.8: Your code here. (1/2) */
	tlbp						# find tlb, save index into INDEX

	nop							# nop
	/* Step 2: Fetch the probe result from CP0.Index */
	mfc0    t1, CP0_INDEX		# load INDEX into t1
.set reorder
	bltz    t1, NO_SUCH_ENTRY	# jump to NO_SUCH_ENTRY if t1 < 0
.set noreorder
	mtc0    zero, CP0_ENTRYHI	# write 0 to ENTRYHI
	mtc0    zero, CP0_ENTRYLO0	# write 0 to ENTRYLO0
	mtc0    zero, CP0_ENTRYLO1	# write 0 to ENTRYLO1
	nop
	/* Step 3: Use 'tlbwi' to write CP0.EntryHi/Lo into TLB at CP0.Index  */
	/* Exercise 2.8: Your code here. (2/2) */
	tlbwi						# write ENTRYHI, ENTRYLO0, ENTRYLO1 to tbl according to INDEX

.set reorder

NO_SUCH_ENTRY:					# restore ENTRYHI, jump to return address
	mtc0    t0, CP0_ENTRYHI
	j       ra
END(tlb_out)

NESTED(do_tlb_refill, 24, zero)
	mfc0    a1, CP0_BADVADDR
	mfc0    a2, CP0_ENTRYHI
	andi    a2, a2, 0xff /* ASID is stored in the lower 8 bits of CP0_ENTRYHI */
.globl do_tlb_refill_call;
do_tlb_refill_call:
	addi    sp, sp, -24 /* Allocate stack for arguments(3), return value(2), and return address(1) */
	sw      ra, 20(sp) /* [sp + 20] - [sp + 23] store the return address */
	addi    a0, sp, 12 /* [sp + 12] - [sp + 19] store the return value */
	jal     _do_tlb_refill /* (Pte *, u_int, u_int) [sp + 0] - [sp + 11] reserved for 3 args */
	lw      a0, 12(sp) /* Return value 0 - Even page table entry */
	lw      a1, 16(sp) /* Return value 1 - Odd page table entry */
	lw      ra, 20(sp) /* Return address */
	addi    sp, sp, 24 /* Deallocate stack */
	mtc0    a0, CP0_ENTRYLO0 /* Even page table entry */
	mtc0    a1, CP0_ENTRYLO1 /* Odd page table entry */
	nop
	/* Hint: use 'tlbwr' to write CP0.EntryHi/Lo into a random tlb entry. */
	/* Exercise 2.10: Your code here. */
	tlbwr
	
	jr      ra
END(do_tlb_refill)
