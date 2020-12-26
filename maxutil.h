#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdbool.h>
void maxutil(char **params1, char *command)
{
	char *action;
	action = params1[1];
	if (strstr(action, "-m"))
	{
		printf("%6s%10s%20s", "Mem%", "PID", "Process");
		printf("\n\n");
		strncpy(command, "ps ahux --sort=-c | awk NR<=3{printf\"%6s%10s%28s\\n\",$4,$2,$11}", 100);
	}
	else if (strstr(action, "-c"))
	{
		printf("%6s%10s%20s", "CPU%", "PID", "Process");
		printf("\n\n");
		strncpy(command, "ps ahux --sort=-c | awk NR<=3{printf\"%6s%10s%28s\\n\",$3,$2,$11}", 100);
	}
	else
	{
		printf("%s", "Command not found\n");
		return;
	}
}