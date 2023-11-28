/* TODO: cambiar printf por write*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "../libft/libft.h"

void	first_command(char *filename, int fd)
{
	/* Funcion del hijo */
	(void)filename, (void)fd;
	for (int i = 0; i < 10000; i++)
		printf("%d\n", i);
	exit(0);
}

int manage(char **argv)
{
	(void) argv;
	int	pid;
	int fd[2];

	if (pipe(fd))
		return printf("Error\n");

	pid = fork();
	if (pid == 0)
		first_command(argv[1], fd[1]);
	
	/* Padre */
	wait(NULL);
	printf("Alo\n");
	
	return 0;
}

int	main(int argc, char *argv[], char *env[])
{
	(void) argc, (void)argv, (void)env;

	/*int	index = 0;*/
	
	if (argc != 5)
		return (printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]));

	return (manage(argv));

	/*while (env[index])
		printf("%s\n", env[index++]);*/

	/*
		char **test = malloc(5 * sizeof(char *));
		int fd = open("res.txt", O_WRONLY | O_CREAT, 0777);
		dup2(fd, STDOUT_FILENO);
		close(fd);

		test[0] = strdup("ping");
		test[1] = strdup("8.8.8.8");
		test[2] = strdup("-c 2");
		test[3] = NULL;
		execve("/sbin/ping", test, env);
	*/


	return (0);
}