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
	if (fork() == 0)
	{
		int i, j, k, x, arow, brow, acol, bcol;
		char *action;
		if (nr < 2)
		{
			printf("Command not found\n");
			return;
		}
		action = param[1];
		if (strstr(action, "-m") || strstr(action, "-a") || strstr(action, "-d") || strstr(action, "-s"))
		{
			printf("Enter the dimensions of first matrix: ");
			scanf("%d %d", &arow, &acol);
			printf("Enter the dimensions of second matrix: ");
			scanf("%d %d", &brow, &bcol);

			int a[arow][acol], b[brow][bcol], ans[arow][bcol];
			if (strstr(action, "-m"))
			{

				if (acol == brow)
				{
					printf("Enter the elements of first matrix:\n");
					for (i = 0; i < arow; i++)
					{
						for (j = 0; j < acol; j++)
						{
							scanf("%d", &a[i][j]);
						}
					}
					printf("Enter the elements of second matrix:\n");
					for (i = 0; i < brow; i++)
					{
						for (j = 0; j < bcol; j++)
						{
							scanf("%d", &b[i][j]);
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
							if (j == 0)
							{
								printf("|%4d", ans[i][j]);
							}
							else if (j == bcol - 1)
							{
								printf("%4d %2s", ans[i][j], "|");
							}
							else
								printf("%4d", ans[i][j]);
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
					printf("Enter the elements of first matrix:\n");
					for (i = 0; i < arow; i++)
					{
						for (j = 0; j < acol; j++)
						{
							scanf("%d", &a[i][j]);
						}
					}
					printf("Enter the elements of second matrix:\n");
					for (i = 0; i < brow; i++)
					{
						for (j = 0; j < bcol; j++)
						{
							scanf("%d", &b[i][j]);
						}
					}

					for (i = 0; i < arow; ++i)
						for (j = 0; j < acol; ++j)
						{
							ans[i][j] = a[i][j] + b[i][j];
						}

					printf("\nSum of two matrices: \n");
					for (i = 0; i < arow; i++)
					{
						for (j = 0; j < bcol; j++)
						{
							if (j == 0)
							{
								printf("|%4d", ans[i][j]);
							}
							else if (j == bcol - 1)
							{
								printf("%4d %2s", ans[i][j], "|");
							}
							else
								printf("%4d", ans[i][j]);
						}
						printf("\n");
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
					printf("Enter the elements of first matrix:\n");
					for (i = 0; i < arow; i++)
					{
						for (j = 0; j < acol; j++)
						{
							scanf("%d", &a[i][j]);
						}
					}
					printf("Enter the elements of second matrix:\n");
					for (i = 0; i < brow; i++)
					{
						for (j = 0; j < bcol; j++)
						{
							scanf("%d", &b[i][j]);
						}
					}
					for (i = 0; i < arow; ++i)
						for (j = 0; j < acol; ++j)
						{
							ans[i][j] = a[i][j] - b[i][j];
						}

					printf("\nDifference of two matrices: \n");
					for (i = 0; i < arow; i++)
					{
						for (j = 0; j < bcol; j++)
						{
							if (j == 0)
							{
								printf("|%4d", ans[i][j]);
							}
							else if (j == bcol - 1)
							{
								printf("%4d %2s", ans[i][j], "|");
							}
							else
								printf("%4d", ans[i][j]);
						}
						printf("\n");
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
					printf("Enter the elements of first matrix:\n");
					for (i = 0; i < arow; i++)
					{
						for (j = 0; j < acol; j++)
						{
							scanf("%d", &a[i][j]);
						}
					}
					printf("Enter the elements of second matrix:\n");
					for (i = 0; i < brow; i++)
					{
						for (j = 0; j < bcol; j++)
						{
							scanf("%d", &b[i][j]);
						}
					}
					for (i = 0; i < arow; ++i)
						for (j = 0; j < acol; ++j)
						{
							ans[i][j] = a[i][j] / b[i][j];
						}

					printf("\nDivision of two matrices: \n");
					for (i = 0; i < arow; i++)
					{
						for (j = 0; j < bcol; j++)
						{
							if (j == 0)
							{
								printf("|%4d", ans[i][j]);
							}
							else if (j == bcol - 1)
							{
								printf("%4d %2s", ans[i][j], "|");
							}
							else
								printf("%4d", ans[i][j]);
						}
						printf("\n");
					}
				}
				else
				{
					printf("%s", "These matrices cannot be divided\n");
				}
			}
		}
		else
		{
			printf("Command not found\n");
		}
		exit(0);
	}
	else
	{
		wait(0);
	}
}