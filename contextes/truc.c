
/* TP1 */

int * top_stack;

void dump_stack(){
	/* int i=0;
	top_stack = &i */
	asm("movl %%esp, %0" : "=r" (top_stack)::);
}

int rec(int depth){
	int var_local = 0x DEADBEEF;
	if (depth > 0)
		{rec (depth -1);}
	else
		{dump_stack();}
}

/* ***************************** */

int main(int argc, char ** argv){
	int i;
	struct ctx_s actx;
	current_ctx = & actx;
	i = try(& actx, afct, 5);
	printf("i=%d\n", i);
}

int afct(int p){
	if (p>0)
		return afct(p-1);
	else
		return -1; /* throw((current_ctx) -2) */
}


/* ***************************** */
/* TP2 */

void switch_to_ctx(struct ctx_s * newctx){
	static struct ctx_s * ctx_current = NULL;
	assert(newctx->magic == CTX_MAGIC && newctx->status != CTX_TERMINATED); /* Kernel panic légitime */
	if (ctx_current)
		asm("movl %%esp, %0" : "=r" (ctx_current->sp)::);
		asm("movl %%ebp, %0" : "=r" (ctx_current->bp)::);
	}
	ctx_current = newctx;
	asm("movl %0, %%esp" :: "r" (ctx_current->sp):); /* ne plus utiliser de variables locales */
	asm("movl %0, %%ebp" :: "r" (ctx_current->bp):);
	if (ctx_current->status == CTX_READY){
		ctx_current->status = CTX_ACTIVATED;
		ctx_current->f(ctx_current->arg);
		ctx_current->status = CTX_TERMINATED; /* Liberer la mémoire ? */
		exit(0);
	}
	return;
}


/* ***************************** */
/* TD2 */

#define CTX_MAGIC oxDEADBEEF

struct ctx_s {
	int * esp;
	int * esb;
	unsigned int magic;
	func_t * f;
	void * arg;
	enum state_e status;
	unsigned char * stack
}

volatile try(struct ctx_s * pctx, funct_t * f, int arg){
 pctx-> = CTX_MAGIC;
		asm("movl %%esp, %0" : "=r" (ctx_current->sp)::);
		asm("movl %%ebp, %0" : "=r" (ctx_current->bp)::);
		return f(arg);
}

volatile throw(struct ctx_s * pctx, int r){
	assert(pctx->magic = CTX_MAGIC);
	static ctx_s * spctx;
	static int res;
	res = r;
	asm("movl %0, %%esp" :: "r" (spctx->sp):);
	asm("movl %0, %%ebp" :: "r" (spctx->bp):);
	return res;
}

enum state_e {
	CTX_READY, CTX_ACTIVATED, CTX_TERMINATED;
}

int init_ctx(struct ctx_s * pctx, int stack_size, func_t f, vois * arg){
	pctx->stack = malloc(stack_size);
	if(!pctx->stack){ /* Kernel panic srait illégitime */
		return 0;
	}
	pctx->ebp = & pctx->stack[stack_size -4];
	pctx->esp = pctx->ebp;
	pctx-> f = f;
	pctx-> arg = arg;
	pctx-> status = CTX_READY;
	pctx-> magic = CTX_MAGIC;
	return 1;
}

