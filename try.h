#ifndef TRY_H
#define TRY_H

#include <stdio.h>
#include <stdlib.h>
//#include <sys/wait.h>

typedef int (func_t)(int); /* a function that returns an int from an int */

struct ctx_s {
  void * ctx_bp;
  void * ctx_sp;
  //unsigned int magic; // var to verify if the struct was initialised
};

int try (struct ctx_s *pctx, func_t *f, int arg);
int throw (struct ctx_s *pctx, int r);

#endif //TRY_H

