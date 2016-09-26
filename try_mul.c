#include "try.h"

static struct ctx_s *pctx;

int mul(int depth)
{
    int i;

    switch (scanf("%d", &i)) 
	{
    case EOF :
      return 1;
    case 0 :
      return mul(depth+1); 
    case 1 :
      if (i) 
	return i * mul(depth+1);
      else
	throw(pctx, 0);
    }
    return 0;
}

int main ()
{
    int product;

    printf("Une liste d'entiers est lue a partir d'un fichier ! \n"); 
	product = mul(0);
    printf("Le produit de ces entiers :  %d\n", product);

}




