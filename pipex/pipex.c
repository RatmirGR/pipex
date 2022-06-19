#include "pipex.h"

static void	ft_child_process(t_list *config, int idx)
{
	int		i;
	char	*path;

	i = 0;
	if (dup2(config->file_des[idx].fd_in, 0) == -1)
		ft_print_error(config, ERROR_DUP2, "1");
	if (dup2(config->file_des[idx].fd_out, 1) == -1)
		ft_print_error(config, ERROR_DUP2, "1");
	ft_close_file_descriptors(config);
	while (config->paths[i] != NULL)
	{
		path = ft_strjoin(config->paths[i], config->file_des[idx].name_cmd[0]);
		execve(path, config->file_des[idx].name_cmd, config->env);
		free(path);
		i++;
	}
	ft_print_error(config, ERROR_CMD, config->file_des[idx].name_cmd[0]);
}

static void	ft_parent_process(t_list *config, int idx)
{
	pid_t	pid;
	int		i;
	int		flag;

	pid = waitpid(idx, NULL, 0);
	i = 0;
	flag = 1;
	while (flag == 1 && i < config->count_cmd)
	{
		if (config->fork_id[i] == pid)
			flag = 0;
		i++;
	}
	if (flag == 0 && config->file_des[i - 1].fd_in != 0)
		close(config->file_des[i - 1].fd_in);
	if (flag == 0 && config->file_des[i - 1].fd_out != 1)
		close(config->file_des[i - 1].fd_out);
}

void	ft_pipex(t_list *config)
{
	int	i;

	config->fork_id = malloc(config->count_cmd * sizeof(pid_t));
	if (config->fork_id == NULL)
		ft_print_error(config, ERROR_MEM_FORK_FD, "1");
	i = 0;
	while (i < config->count_cmd)
	{
		config->fork_id[i] = fork();
		if (config->fork_id[i] < 0)
			ft_print_error(config, ERROR_FORK_FD, "1");
		if (config->fork_id[i] == 0)
			ft_child_process(config, i);
		else
			ft_parent_process(config, i);
		i++;
	}
}
