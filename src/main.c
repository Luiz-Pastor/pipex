/* TODO: cambiar printf por write*/

#include <stdio.h>

int	main(int argc, char *argv[], char *env[])
{
	(void)argv;

	int	index = 0;
	
	if (argc != 5)
		return (printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]));

	while (env[index])
		printf("%s\n", env[index++]);

	return (0);
}