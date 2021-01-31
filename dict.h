#include<stdio.h>
int dict(char *word){
    char dicto[50][2][200] ={
        "analog" ,"Analogue is a conventional method of transmitting data",
        "bug","programming error",
        "cpu","Central Processing Unit",
        "domain","A domain is a set of computers on a network that are managed as a unit.",
        "encrpyption","Encryption is the process of converting electronic data to an unrecognisable or encrypted form",
        "ftp","File transfer protocol (FTP) is a common method of transferring files via the internet from one host to another host.",
        "gateway","A point within a network that interconnects with other networks.",
        "internet","A set of interconnected networks that allow computers in different locations to exchange information",
        "java"," Javais a programming language that is commonly used in the development of client-server web applications.",
        "malware","Malware is short for malicious software.",
        "modem","A modem is a device that allows computers to transmit information to each other via ordinary telephone lines.",
        "plugin","A software plug-in is a component that adds to a software program's functionality. ",
        "protocol","A protocol is a standard or set of rules that computers and other devices use when communicating with one another. ",
        "read-only","A read-only file cannot be edited, modified or deleted","Server","computer that handles requests for data, email, file transfers",
        "url","(unique resource locator)string of characters to access a particular website","viral","experinsing a sudden spike in popularity",
        "wpa","(Wi-Fi protected access)security protocol used in wi-fi networks","Zip","Compress files"
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
