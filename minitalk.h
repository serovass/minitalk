
#ifndef MINITALK_H
# define MINITALK_H

# include "./libft/libft.h"
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_server
{
	char c;
	int cnt;
	int pid;
} t_server;

typedef struct s_client
{
    char *str;
    //int i;
    int cnt;
    int pid;
} t_client;

#endif