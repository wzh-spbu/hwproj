#include<stdio.h>
  
int main(){
  for(int i = 0; i<50 ; i++){
    printf(" message ");
    fflush(stdout);
    fprintf(stderr," error ");
    fflush(stderr);
  }
  /*
  for(int i = 0; i<50 ; i++){
    printf(" message ");
    fprintf(stderr," error ");
  }
  */
  
  /*
  for(int i = 0; i<50 ; i++){
    printf(" message\n ");
    fprintf(stderr," error\n ");
  }
  */
  return 0;
}
  


