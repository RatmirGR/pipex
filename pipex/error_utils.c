#include "pipex.h"

static void	ft_free_paths(char **paths)
{
	int	i;

	i = 0;
	if (paths != NULL)
	{
		while (paths[i] != NULL)
			free(paths[i++]);
		free(paths);
	}
}

static void	ft_free_file_des(t_fd *file_des, int count_cmd)
{
	int	i;
	int	j;

	i = 0;
	if (file_des != NULL)
	{
		while (i < count_cmd)
		{
			j = 0;
			if (file_des[i].fd_in != 0)
				close(file_des[i].fd_in);
			if (file_des[i].fd_out != 1)
				close(file_des[i].fd_out);
			if (file_des[i].name_cmd != NULL)
			{
				while (file_des[i].name_cmd[j] != NULL)
					free(file_des[i].name_cmd[j++]);
			}
			free(file_des[i].name_cmd);
			i++;
		}
		free(file_des);
	}
}

void	ft_close_file_descriptors(t_list *config)
{
	int	i;

	i = 0;
	while (i < config->count_cmd)
	{
		if (config->file_des[i].fd_in != 0)
			close(config->file_des[i].fd_in);
		if (config->file_des[i].fd_out != 1)
			close(config->file_des[i].fd_out);
		i++;
	}
}

void	ft_all_free(t_list *config)
{
	if (config != NULL)
	{
		ft_free_paths(config->paths);
		ft_free_file_des(config->file_des, config->count_cmd);
		ft_close_file_descriptors(config);
		if (config->fork_id != NULL)
			free(config->fork_id);
	}
	free(config);
}
