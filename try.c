#include "try.h"

int try (struct ctx_s *pctx, func_t *f, int arg) 
{ 	
	asm ("movl %%ebp, %0" "\n" "movl %%esp, %1"
		  : "=r"(pctx->ctx_bp), "=r"(pctx->ctx_sp)
		  :
		  :);
  
  return f(arg);
}

int throw (struct ctx_s *pctx, int r) 
{
	  static int val_res;
	  val_res = r;

	  asm ("movl %0, %%ebp" "\n" "movl %1, %%esp" 
		   :
		   : "r"(pctx->ctx_bp),"r"(pctx->ctx_sp)
		   :);

	  return val_res;
}


