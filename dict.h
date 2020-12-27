#include<stdio.h>
int dict(char *word){
    char dicto[50][2][15] ={
        "Word1","Meaning",
        "Word2","Meaning"
        
    };
    int c=0;
for(int i=0;i<50;i++){
    if(strcmp(word,dicto[i][0])==0)
        printf("%s\n",dicto[i][1]);
    else
        c++;
    
}
if(c>=10)
    printf("%s\n","Not Found");

}