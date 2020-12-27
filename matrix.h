#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdbool.h>
void matrix(char **param, int nr)
{
	int i, j, k, x, arow, brow, acol, bcol;
	char *action;
	x = 1;
	action = param[x++];
	arow = atoi(param[x++]);
	acol = atoi(param[x++]);
	brow = atoi(param[x++]);
	bcol = atoi(param[x++]);
	printf("%d", nr);
	if (arow * acol + brow * bcol + 6 != nr)
	{
		printf("%s", "Wrong number of arguments\n");
		return;
	}
	int a[arow][acol], b[brow][bcol], ans[arow][bcol];
	if (strstr(action, "-m"))
	{
		if (acol == brow)
		{
			for (i = 0; i < arow; i++)
			{
				for (j = 0; j < acol; j++)
				{
					a[i][j] = atoi(param[x++]);
				}
			}

			for (i = 0; i < brow; i++)
			{
				for (j = 0; j < bcol; j++)
				{
					b[i][j] = atoi(param[x++]);
				}
			}

			for (i = 0; i < arow; i++)
			{
				for (j = 0; j < bcol; j++)
				{
					ans[i][j] = 0;
					for (k = 0; k < acol; k++)
					{
						ans[i][j] += a[i][k] * b[k][j];
					}
				}
			}
			printf("\nProduct of two matrices: \n");
			for (i = 0; i < arow; i++)
			{
				for (j = 0; j < bcol; j++)
				{
					printf("%d\t", ans[i][j]);
				}
				printf("\n");
			}
		}
		else
		{
			printf("%s", "These matrices cannot be multiplied\n");
		}
	}
	else if (strstr(action, "-a"))
	{

		if (acol == bcol && arow == brow)
		{
			for (i = 0; i < arow; i++)
			{
				for (j = 0; j < acol; j++)
				{
					a[i][j] = atoi(param[x++]);
				}
			}

			for (i = 0; i < brow; i++)
			{
				for (j = 0; j < bcol; j++)
				{
					b[i][j] = atoi(param[x++]);
				}
			}

			for (i = 0; i < arow; ++i)
				for (j = 0; j < acol; ++j)
				{
					ans[i][j] = a[i][j] + b[i][j];
				}

			printf("\nSum of two matrices: \n");
			for (i = 0; i < arow; ++i)
				for (j = 0; j < acol; ++j)
				{
					printf("%d   ", ans[i][j]);
					if (j == acol - 1)
					{
						printf("\n\n");
					}
				}
		}
		else
		{
			printf("%s", "These matrices cannot be added\n");
		}
	}
	else if (strstr(action, "-s"))
	{

		if (acol == bcol && arow == brow)
		{
			for (i = 0; i < arow; i++)
			{
				for (j = 0; j < acol; j++)
				{
					a[i][j] = atoi(param[x++]);
				}
			}

			for (i = 0; i < brow; i++)
			{
				for (j = 0; j < bcol; j++)
				{
					b[i][j] = atoi(param[x++]);
				}
			}
			for (i = 0; i < arow; ++i)
				for (j = 0; j < acol; ++j)
				{
					ans[i][j] = a[i][j] - b[i][j];
				}

			printf("\nDifference of two matrices: \n");
			for (i = 0; i < arow; ++i)
				for (j = 0; j < acol; ++j)
				{
					printf("%d   ", ans[i][j]);
					if (j == acol - 1)
					{
						printf("\n\n");
					}
				}
		}
		else
		{
			printf("%s", "These matrices cannot be substracted\n");
		}
	}
	else if (strstr(action, "-d"))
	{

		if (acol == bcol && arow == brow)
		{
			for (i = 0; i < arow; i++)
			{
				for (j = 0; j < acol; j++)
				{
					a[i][j] = atoi(param[x++]);
				}
			}

			for (i = 0; i < brow; i++)
			{
				for (j = 0; j < bcol; j++)
				{
					b[i][j] = atoi(param[x++]);
				}
			}
			for (i = 0; i < arow; ++i)
				for (j = 0; j < acol; ++j)
				{
					ans[i][j] = a[i][j] / b[i][j];
				}

			printf("\nDivision of two matrices: \n");
			for (i = 0; i < arow; ++i)
				for (j = 0; j < acol; ++j)
				{
					printf("%d   ", ans[i][j]);
					if (j == acol - 1)
					{
						printf("\n\n");
					}
				}
		}
		else
		{
			printf("%s", "These matrices cannot be divided\n");
		}
	}
	else
	{
		printf("%s", "Command not found\n");
	}
	return;
}