/* TODO: cambiar printf por write*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "../libft/libft.h"
#include <limits.h>

char *find_path(char *command, char *paths)
{
	char	*slash;
	char	*full_path;
	char	**splited;
	int		index = 0;
	char	*res = NULL;

	splited = ft_split(paths, ':');
	while (splited[index])
	{
		slash = ft_strjoin(splited[index++], "/");
		if (!slash)
			return free_split(splited);
		full_path = ft_strjoin(slash, command);
		free(slash);
		if (!full_path)
			return free_split(splited);
		if (access(full_path, X_OK) == 0)
		{
			res = full_path;
			break;
		}
		free(full_path);
	}
	free_split(splited);
	return res;
}

static void	child_error(int fd)
{
	write(fd, "0", 1);
	exit(1);
}

int	split_length(char **spl)
{
	int	index;

	index = 0;
	while (spl[index])
		index++;
	return (index);
}

char	**get_arguments(char *filename, char **args)
{
	int		index;
	char	**res;

	(void)filename, (void)args, (void)index, (void)res;
	return NULL;

}

void	first_command(char *filename, char *command, char **env, int fd)
{
	/* Funcion del hijo */
	char	**splitted;
	char	*path;
	char	**arguments;

	/* Dividimos el comando --> [comando] [argumento 1] [...] [NULL] */
	splitted = ft_split(command, ' ');
	if (!splitted)
		child_error(fd); /* Error malloc */
	
	/* Buscamos la ruta absoluta del primer comando --> x/x/comando o NULL */
	path = find_path(splitted[0], env[2]);
	if (!path)
		child_error(fd); /* No existe ruta */
	printf("# %s #\n", path);
	exit(0);
	/* Obtenemos una array con todos los argumentos */
	arguments = get_arguments(filename, &splitted[1]);
	if (arguments)
		child_error(fd);

	/*
		dup2(fd, STDOUT_FILENO);
		execve(path, arguments, env);
	*/
}

int manage(char **argv, char **env)
{
	(void) argv, (void)env;
	int	pid;
	int fd[2];
	int res;

	if (pipe(fd))
		return printf("Error\n");
	pid = fork();
	if (pid == 0)
		first_command(argv[1], argv[2], env, fd[1]);
	
	/* Padre */
	wait(NULL);

	exit(0);
	/*close(fd[1]);
	read(fd[0], &res, sizeof(int));*/
	/*printf(">> %d\n", res);
	printf("Alo\n");*/
	
	return 0;
}

void leaks()
{
	system("leaks -q pipex");
}

int	main(int argc, char *argv[], char *env[])
{	
	if (argc != 5)
		return (printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]));

	return manage(argv, env);


}










	/* int	index = -1;
	while (env[++index])
		printf("(%d) %s\n", index, env[index]);*/

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