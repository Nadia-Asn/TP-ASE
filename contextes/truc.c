
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

/* ex-contenu de lib_contexte */

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

/* Flag improbable pour vérifier que la structure a été initialisée */
#define CTX_MAGIC oxDEADBEEF

struct ctx_s {
	/* Pointeurs de la frame */
	int * esp;
	int * esb;
	
	/* Zone du flag */
	unsigned int magic;
	
	/* Point d'entrée de la fonction, elle asume de convertir les arguments */
	func_t * f;
	void * arg;
	
	/* Etat du contexte */
	enum state_e status;
	
	/* ***** A Commenter ****** */
	unsigned char * stack;
	
	/* Pour faire fonctionner le yield() */
	struct ctx_s * next;
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
	if(!pctx->stack){ /* Kernel panic serait illégitime */
		return 0;
	}
	pctx->ebp = & pctx->stack[stack_size -4];
	pctx->esp = pctx->ebp;
	pctx->f = f;
	pctx->arg = arg;
	pctx->status = CTX_READY;
	pctx->magic = CTX_MAGIC;
	return 1;
}


/* ***************************** */
/* TD3 */

// #include <stdlib.h> pour malloc

void yield(){
	/* Devrait faire un assert pour vérifier que le status du contexte n'est pas ctx_terminated */
	switch_ctx(current_ctx->next)
}

struct * ctx_s create_ctx (int stack_size, func_t f, void * args){
	/* Allocation et initialisation */
	struct * ctx_s ctx = malloc(sizeof(struct ctx_s));
	if (ctx == NULL || !init_ctx(ctx, f, args)){
		return NULL;
	}
	
	/* Ajout à la liste */
	struct * last_ctx = current_ctx;
	if (last_ctx == NULL){ /* Si seul contexte */
		ctx->next = ctx;
		current_ctx = ctx;
		return ctx;
	}
	
	/* Sinon */
	
	/* Recherche de la position */
	while(last_ctx->next != current_ctx){
		last_ctx = last_ctx->next;
	}
	
	/* Insertion */
	last_ctx->next = ctx;
	ctx->next = current_ctx;
	
	return ctx;
}


/* ***************************** */

if (ctx status == CTX_READY) {
	start_ctx();
	
	
	
}

/* ***************************** */

void start_ctx(){
	struct ctx_s * ctx = current_ctx;
	ctx->status = ACTIVABLE; /* ????????????? */
	ctx->f(ctx->args);
	ctx->status = CTX_TERMINATED;
}

