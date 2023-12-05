#include "../inc/pipex.h"

void	*free_array(char **arr)
{
	int	index;

	index = 0;
	if (!arr)
		return NULL;
	while (arr[index])
		free(arr[index++]);
	free(arr);
	return NULL;
}

void	exit_error(int flag, int end)
{
	if (flag)
		perror("Error");
	exit(end);
}
