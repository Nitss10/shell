#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdbool.h>
#include "tree.h"
#include "dict.h"
#include "matrix.h"
#include "maxutil.h"
#include "interest.h"
#include <math.h>
void spaceRemover(char *buf)
{
	if (buf[strlen(buf) - 1] == ' ' || buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = '\0';
	if (buf[0] == ' ' || buf[0] == '\n')
		memcpy(buf, buf + 1, strlen(buf));
}

void parser(char **param, int *nr, char *buf, const char *c)
{
	char *token;
	token = strtok(buf, c);
	int pc = -1;
	int j = 0;
	char ch;
	while (token[j])
	{
		token[j] = tolower(token[j]);
		j++;
	}
	while (token)
	{
		param[++pc] = malloc(strlen(token) + 1); //param[2] = token_size; file2
		strcpy(param[pc], token);				 // param[2] =  token;   file2
		spaceRemover(param[pc]);
		token = strtok(NULL, c);
	}
	param[++pc] = NULL; //param[3] = NULL;   nr = 3
	*nr = pc;
}
/*void shellScript(char** argv,int nr,char* fname){
     FILE *fp1;
         printf("%s","hello");
         fp1 = fopen(fname, "a");
         int i =0;
         while(i<nr){
         fprintf(fp1, "%s",argv[i]);
         fprintf(fp1," ");
         i++;
         }
         fprintf(fp1,"\n");
}*/
//------------script file creation !!----------------
void scriptFile(char *buff, int nr, char *fname)
{
	FILE *fp1;
	fp1 = fopen(fname, "a+");
	fprintf(fp1, "%s", buff);
	fclose(fp1);
}
void undoPreCommand(char *fname)
{
	FILE *fp, *fp1, *fp2;
	char str[100], sub[100];
	char temp[] = "tempio.sh";
	fp1 = fopen(fname, "r");
	fp2 = fopen(temp, "w");
	int c = 0, ctr = 0;

	while (!feof(fp1))
	{
		fgets(str, 100, fp1);
		c++;
	}
	fp = fopen(fname, "r");
	while (!feof(fp))
	{
		strcpy(str, "\0");
		fgets(str, 100, fp);
		if (!feof(fp))
		{
			ctr++;
			if (ctr != c - 1)
			{
				fprintf(fp2, "%s", str);
			}
		}
	}
	fclose(fp);
	fclose(fp2);
	remove(fname);
	rename(temp, fname);
}
void print(char *fname)
{
	FILE *fp;
	fp = fopen(fname, "r");
	char c;
	c = fgetc(fp);

	while (c != EOF)
	{
		printf("%c", c);
		c = fgetc(fp);
	}
	printf("\n");

	fclose(fp);
}
//------simple command execution
void executeBasic(char **argv, int nr, bool flag, char *fname, char *buff)
{
	int result;
	//char source[] = "test.sh";
	if (fork() == 0)
	{
		result = execvp(argv[0], argv);
		printf("%s", argv[0]);
		printf("%s\n", ":  Command Not Found");
		exit(0);
	}
	else
		wait(NULL);
	if (result != -1 && flag)
	{
		//shellScript(argv,nr,fname);
		scriptFile(buff, nr, fname);
	}
}
//-----------piped command execution
void executePiped(char **buf, int nr, char *buff, char *fname, bool flag)
{
	if (nr > 10)
		return;
	int result;
	int fd[10][2], i, pc;
	char *argv[100];

	for (i = 0; i < nr; i++)
	{
		parser(argv, &pc, buf[i], " "); // cat helo.txt  pc = 2  nr = 2
		if (i != nr - 1)
			if (pipe(fd[i]) < 0)
				return;
		if (fork() == 0)
		{
			if (i != nr - 1) // i=0
			{
				dup2(fd[i][1], 1);
				close(fd[i][0]);
				close(fd[i][1]);
			}

			if (i != 0)
			{
				dup2(fd[i - 1][0], 0);
				close(fd[i - 1][1]);
				close(fd[i - 1][0]);
			}
			if (execvp(argv[0], argv) == -1)
				result = 0;
		}
		if (i != 0)
		{
			close(fd[i - 1][0]);
			close(fd[i - 1][1]);
		}
		wait(NULL);
	}
	if (result == 1 && flag)
		scriptFile(buff, nr, fname);
}
//---------- command with >,>>,< operator ----------
void executeRedirect(char **buf, int nr, int mode, char *buff, char *fname, bool flag)
{
	int pc, fd;
	char *argv[100];
	spaceRemover(buf[1]);
	int result;
	parser(argv, &pc, buf[0], " "); //echo
	if (fork() != 0)
		wait(NULL);
	else
	{
		switch (mode) //here 0644 is it says "I can read and write it; everyone else can only read it."
		{
		case 0:
		{
			fd = open(buf[1], O_RDONLY | O_CREAT, 0644);
			//opening the file for read only "<" if not exist then create       grep aksha t < hello.txt
			break;
		}
		case 1:
		{
			fd = open(buf[1], O_WRONLY | O_CREAT, 0644); // for writing in the file echo "Some text here." > myfile.txt erasing previous value
			break;
		}
		case 2:
		{
			fd = open(buf[1], O_WRONLY | O_APPEND | O_CREAT, 0644); //for writing or appending in the file echo "Some text here." >> myfile.txt
			break;
		}
		default:
			return;
		}

		switch (mode)
		{
		case 0:
		{
			dup2(fd, 0);
			break;
		}
		case 1:
		{
			dup2(fd, 1);
			break;
		}
		case 2:
		{
			dup2(fd, 1);
			break;
		}
		default:
			return;
		}

		result = execvp(argv[0], argv);
		if (result != -1 && flag)
			scriptFile(buff, nr, fname);
	}
}
//---------intial window display --------
void prompt()
{
	static int start = 1;
	if (start)
	{
		const char *clr_screen = "\033[H\033[J";
		printf("%s", clr_screen);
		start = 0;
	}
	char curr_dir[500];
	getcwd(curr_dir, sizeof(curr_dir));
	char *curr_user = getenv("USER");
	printf("[%s@localhost %s]$ ", curr_user, (curr_dir + 12)); // print after 12 char
}
//--------main function ------
int main(int tdi, char *tdir[])
{
	bool flag;
	flag = false;
	char buf[500], *buffer[100], *params1[100], command[500];
	int nr = 0;
	char fname[100];
	while (1)
	{
		prompt();
		fgets(buf, 500, stdin);
		if (flag)
			strcpy(command, buf);
		if (strchr(buf, '|'))
		{
			parser(buffer, &nr, buf, "|"); // cat hello.txt | grep akshat   // nr = 2
			executePiped(buffer, nr, buf, fname, flag);
		}
		else if (strstr(buf, ">>")) // >>   echo akshat >> hello.txt
		{
			parser(buffer, &nr, buf, ">>");
			if (nr == 2)
				executeRedirect(buffer, nr, 2, buf, fname, flag);
		}
		else if (strchr(buf, '>')) //   >>
		{
			parser(buffer, &nr, buf, ">");
			if (nr == 2)
				executeRedirect(buffer, nr, 1, buf, fname, flag);
		}
		else if (strchr(buf, '<'))
		{
			parser(buffer, &nr, buf, "<");
			if (nr == 2)
				executeRedirect(buffer, nr, 0, buf, fname, flag);
		}
		else
		{
			parser(params1, &nr, buf, " "); //nr = 3
			if (strstr(params1[0], "cd"))
				chdir(params1[1]);
			else if (strstr(params1[0], "script"))
			{
				if (!params1[1])
				{
					printf("%s\n", "script: missing file name");
					printf("%s\n", "try script --help");
				}
				else if (strstr(params1[1], "--help"))
				{
					print("scripthelp.txt");
				}
				else
				{
					flag = true;
					strcpy(fname, params1[1]);
					if (strstr(fname, ".sh"))
						scriptFile("#!/bin/bash \n", nr, fname);
					//strcpy(params1[0],"touch");
					//executeBasic(params1,nr,flag);
				}
			}
			else if (strstr(params1[0], "end"))
				flag = false;
			else if (strstr(params1[0], "undo"))
				undoPreCommand(fname);

			else if (strstr(params1[0], "maxutil"))
			{
				char line[100];
				int x;
				char response;
				if (nr != 2)
				{
					printf("%s", "Need argument -m ,-c \n");
					printf("%s\n", "try maxutil --help");
				}
				else if(strstr(params1[1],"--help")) {
					print("maxutil.txt");
				}

				else
				{
					char command[100];

					maxutil(params1, command);
					nr = 0;
					parser(buffer, &nr, command, "|");
					executePiped(buffer, nr, buf, fname, flag);
					if (fork() == 0)
					{
						printf("Do you want to kill any of the process? (y/n) ");
						scanf(" %c", &response);
						if (response == 'y')
						{
							printf("KILL PID: ");
							scanf("%d", &x);

							kill(x, SIGKILL);
						}
						exit(0);
					}
					else
					{
						wait(0);
					}
				}
			}
			else if (strstr(params1[0], "matrix"))
			{
				if (!params1[1])
				{
					printf("%s\n", "matrix: missing argument -a,-s,-m,");
					printf("%s\n", "try matrix --help");
				}

				else if(strstr(params1[1],"--help"))
					print("matrix.txt");
				else 
				matrix(params1, nr);
			}
			else if (strstr(params1[0], "tree"))
				tree(tdi, tdir);
			else if (strstr(params1[0], "dictionary"))
			{	if (!params1[1])
				{
					printf("%s\n", "dictionary: missing argument word");
					printf("%s\n", "enter dictionary - word");
				}
				else
				dict(params1[1]);
			}
			else if (strstr(params1[0], "interest"))
			{	if (!params1[1])
				{
					printf("%s\n", "interest: missing argument -s ,-m");
					printf("%s\n", "try script --help");
				}

				else if(strstr(params1[1],"--help"))
					print("interest.txt");
				else 
					interest(params1[1]);
			}
			else if (strstr(params1[0], "exit"))
				exit(0);
			else
				executeBasic(params1, nr, flag, fname, command);
		}
	}

	return 0;
}
