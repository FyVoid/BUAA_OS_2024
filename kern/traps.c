#include <env.h>
#include <pmap.h>
#include <printk.h>
#include <trap.h>

extern void handle_int(void);
extern void handle_tlb(void);
extern void handle_sys(void);
extern void handle_mod(void);
extern void handle_reserved(void);
extern void handle_ri(void);

void (*exception_handlers[32])(void) = {
    [0 ... 31] = handle_reserved,
    [0] = handle_int,
    [2 ... 3] = handle_tlb,
#if !defined(LAB) || LAB >= 4
    [1] = handle_mod,
    [8] = handle_sys,
#endif
	[10] = handle_ri
};

/* Overview:
 *   The fallback handler when an unknown exception code is encountered.
 *   'genex.S' wraps this function in 'handle_reserved'.
 */
void do_reserved(struct Trapframe *tf) {
	print_tf(tf);
	panic("Unknown ExcCode %2d", (tf->cp0_cause >> 2) & 0x1f);
}

void do_ri(struct Trapframe *tf) {
	u_long instruct = *((u_long*) tf->cp0_epc);
	// printk("%b\n", instruct);
	u_int rs = (instruct >> 21) & 0x1f;
	u_int rt = (instruct >> 16) & 0x1f;
	u_int rd = (instruct >> 11) & 0x1f;
	if (((instruct >> 26) == 0) && ((instruct & 0x3ff) == 0x3f)) {
		// printk("pmaxub\n");
		tf->regs[rd] = 0;
		for (int i = 0; i < 32; i += 8) {
			u_int rs_i = tf->regs[rs] & (0xff << i);
			u_int rt_i = tf->regs[rt] & (0xff << i);
			if (rs_i < rt_i) {
				tf->regs[rd] = tf->regs[rd] | rt_i;
			} else {
				tf->regs[rd] = tf->regs[rd] | rs_i;
			}
		}
	}
	else if (((instruct >> 26) == 0) && ((instruct & 0x3ff) == 0x3e)) {
		// printk("cas\n");
		long* rsp = (long*) tf->regs[rs];
		long tmp = *rsp;
		if (tmp == tf->regs[rt]) {
			*rsp = tf->regs[rd];
		}
		tf->regs[rd] = tmp;
	}
	tf->cp0_epc += 4;
}
