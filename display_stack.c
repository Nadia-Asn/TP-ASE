#include <stdio.h>
#include <stdlib.h>

void funct_1(int a, int b);
void funct_2(int a, int b);

int main(void) {
  funct_1(65, 89);
  return 0;
}

void funct_1 (int a, int b) {
  unsigned int esp = 0;
  unsigned int ebp = 0;

  asm ("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
       : "=r"(esp),"=r"(ebp)
       :
       :);

  printf("esp => %u\n", esp);
  printf("ebp => %u\n", ebp);
  printf("&esp = %u\n", &esp);
  printf("&ebp = %u\n", &ebp);
  printf("&a = %u\n", &a);
  printf("&b = %u\n", &b);

  funct_2(45,72);
  
  return;
}

void funct_2 (int a, int b) {
  unsigned int esp = 0;
  unsigned int ebp = 0;
  
  asm ("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
       :"=r"(esp),"=r"(ebp)
       :
       :);
  printf("esp => %u\n", esp);
  printf("ebp => %u\n", ebp);
  printf("&esp = %u\n", &esp);
  printf("&ebp = %u\n", &ebp);
  printf("&a = %u\n", &a);
  printf("&b = %u\n", &b);

  return ;
}
