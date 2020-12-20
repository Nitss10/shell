#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void spaceRemover(char* buf)
{
	if(buf[strlen(buf)-1]==' ' || buf[strlen(buf)-1]=='\n')
		buf[strlen(buf)-1]='\0';
	if(buf[0]==' ' || buf[0]=='\n')
		memcpy(buf, buf+1, strlen(buf));
}


void parser(char** param,int *nr,char *buf,const char *c)
{
	char *token;
	token=strtok(buf,c);
	int pc=-1;
	while(token)
	{
		param[++pc]=malloc(sizeof(token)+1);
		strcpy(param[pc],token);
	    spaceRemover(param[pc]);
		token=strtok(NULL,c);
	}
	param[++pc]=NULL;
	*nr=pc;
}

void executeBasic(char** argv)
{
	if(fork()==0)
		execvp(argv[0],argv);
	else
		wait(NULL);
}

void executePiped(char** buf,int nr)
{
	if(nr>10)
		return;
	
	int fd[10][2],i,pc;
	char *argv[100];

	for(i=0;i<nr;i++)
	{
		parser(argv,&pc,buf[i]," ");
		if(i!=nr-1)
			if(pipe(fd[i])<0)
				return;
		if(fork()==0)
		{
			if(i!=nr-1)
			{
				dup2(fd[i][1],1);
				close(fd[i][0]);
				close(fd[i][1]);
			}

			if(i!=0)
			{
				dup2(fd[i-1][0],0);
				close(fd[i-1][1]);
				close(fd[i-1][0]);
			}
			execvp(argv[0],argv);
		}
		if(i!=0)
		{
			close(fd[i-1][0]);
			close(fd[i-1][1]);
		}
		wait(NULL);
	}
}

void executeRedirect(char** buf,int nr,int mode)
{
	int pc,fd;
	char *argv[100];
 	spaceRemover(buf[1]);
	parser(argv,&pc,buf[0]," ");
	if(fork()!=0)
		wait(NULL);
	else
	{
		switch(mode)
		{
			case 0: {
				fd=open(buf[1],O_RDONLY | O_CREAT, 0644); 
				break;
			}
			case 1: {
				fd=open(buf[1],O_WRONLY | O_CREAT, 0644); 
				break;
			}
			case 2: {
				fd=open(buf[1],O_WRONLY | O_APPEND | O_CREAT, 0644); 
				break;
			}
			default: 
				return;
		}

		switch(mode)
		{
			case 0:  {
				dup2(fd,0); 
				break;
			}
			case 1:  {
				dup2(fd,1); 
				break;
			}
			case 2: {
				dup2(fd,1); 
				break;
			}
			default: 
				return;
		}
		execvp(argv[0],argv);
	}
}

void prompt(){
	static int start=1;
	if(start){
		const char *clr_screen = "\033[H\033[J";
		printf("%s", clr_screen);
		start=0;
	}
	char curr_dir[500];
	getcwd(curr_dir, sizeof(curr_dir));
	char *curr_user = getenv("USER"); 
	printf("[%s@localhost %s]$ ", curr_user, (curr_dir+12));
}


int main()
{
	char buf[500],*buffer[100], *params1[100];
	int nr=0;
	while(1)
	{
		prompt();
		fgets(buf, 500, stdin);
		if(strchr(buf,'|'))
		{
			parser(buffer,&nr,buf,"|"); // top | grep chrome 
			executePiped(buffer,nr);
		}
		else if(strstr(buf,">>"))
		{
			parser(buffer,&nr,buf,">>");
			if(nr==2)
				executeRedirect(buffer,nr,2);
		}
		else if(strchr(buf,'>'))
		{
			parser(buffer,&nr,buf,">");
			if(nr==2)
				executeRedirect(buffer,nr, 1);
		}
		else if(strchr(buf,'<'))
		{
			parser(buffer,&nr,buf,"<");
			if(nr==2)
				executeRedirect(buffer,nr, 0);
		}
		else
		{
			parser(params1,&nr,buf," ");
			if(strstr(params1[0],"cd"))
				chdir(params1[1]);
			else if(strstr(params1[0],"exit"))
				exit(0);
			else if(strstr(params1[0],"maxcpu"))
			    {
				  char command[100]="ps ahux --sort=-c | awk 'NR<=5{printf"%s %6d %s\n",$3,$2,$11}'";
				  parser(buffer,&nr,command,'|');
				  executePiped(buffer,nr);
				}
			else 
				executeBasic(params1);
		}
	}

	return 0;
}
