
#include <stdio.h>

int print_ebp_esp(){
	int * sp;
	int * bp;
	asm("movl %%esp, %0" : "=r" (sp)::);
	asm("movl %%ebp, %0" : "=r" (bp)::);
	printf("esp = %p et ebp = %p\n", bp, sp);
}

int rec(int depth){
	int var_local = 0xDEADBEEF;
	if (depth > 0){
		rec (depth -1);
	}
	else {
		print_ebp_esp();
		printf("addresse variable locale = %p\n", & var_local);
		printf("addresse paramettre = %p\n", & depth);
	}
}

