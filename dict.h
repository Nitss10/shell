#include<stdio.h>
int dict(char *word){
    char dicto[50][2][15] ={
        "word1","Meaning1",
        "word2","Meaning2"
        
    };
    int c=0;
for(int i=0;i<50;i++){
    if(strcmp(word,dicto[i][0])==0)
      {  printf("%s\n",dicto[i][1]); 
      c=1;
      break;
      }
    
}
if(c==0)
    printf("%s\n","Not Found");

}
