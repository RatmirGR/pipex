#include "pipex.h"

void	ft_init_paths(t_list *config, char *env[])
{
	int		i;
	char	*path;
	char	**tmp;

	i = 0;
	while (env != NULL && env[i] != NULL && ft_strncmp("PATH=", env[i], 5) != 0)
		++i;
	if (ft_strncmp("PATH=", env[i], 5) != 0)
		ft_print_error(config, ERROR_PATH, "1");
	path = ft_substr(env[i], 5, ft_strlen(env[i]));
	tmp = ft_split(path, ':');
	free(path);
	config->count_paths = ft_line_len(tmp);
	config->paths = malloc((config->count_paths + 1) * sizeof(char *));
	if (config->paths == NULL)
		ft_print_error(config, ERROR_MEM_PATHS, "1");
	i = 0;
	while (tmp[i])
	{
		path = ft_strjoin(tmp[i], "/");
		config->paths[i] = path;
		free(tmp[i++]);
	}
	free(tmp);
	config->paths[i] = NULL;
}

void	ft_init_file_des(t_list *config)
{
	int	i;

	i = 0;
	while (i < config->count_cmd)
		config->file_des[i++].name_cmd = NULL;
}

void	ft_read_keyboard(t_list *config)
{
	int		filedes[2];
	char	*str;

	if (pipe(filedes) == -1)
		ft_print_error(config, ERROR_PIPE, "1");
	config->file_des[0].fd_in = filedes[0];
	if (config->file_des[0].fd_in == -1)
		ft_print_error(config, ERROR_PIPE, "1");
	while (config->flag == 1)
	{
		write(1, "pipe heredoc> ", 14);
		str = get_next_line(0);
		if (ft_strcmp(str, config->limiter) == 0)
			config->flag = 0;
		else if (ft_strcmp(str, "") != 0)
		{
			write(filedes[1], str, ft_strlen(str));
			write(filedes[1], "\n", 1);
		}
		else if (ft_strcmp(str, "") == 0)
			write(filedes[1], "\n", 1);
		free(str);
	}
	close(filedes[1]);
}

void	ft_init_fd_files(t_list *config, int ac, char *av[])
{
	int	fd_out;

	if (config->here_doc_flag != 1)
	{
		config->file_des[0].fd_in = open(av[1], O_RDONLY);
		if (config->file_des[0].fd_in == -1)
			ft_print_error(config, ERROR_FILE, av[1]);
		fd_out = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		config->file_des[config->count_cmd - 1].fd_out = fd_out;
		if (config->file_des[config->count_cmd - 1].fd_out == -1)
			ft_print_error(config, ERROR_FILE, av[ac - 1]);
	}
	else
	{
		ft_read_keyboard(config);
		fd_out = open(av[ac - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		config->file_des[config->count_cmd - 1].fd_out = fd_out;
		if (config->file_des[config->count_cmd - 1].fd_out == -1)
			ft_print_error(config, ERROR_FILE, av[ac - 1]);
	}
}

void	ft_init_fd_cmds(t_list *config, char *av[])
{
	int	i;
	int	j;
	int	filedes[2];

	i = 1;
	while (i < config->count_cmd)
	{
		if (pipe(filedes) == -1)
			ft_print_error(config, ERROR_PIPE, "1");
		config->file_des[i - 1].fd_out = filedes[1];
		if (config->file_des[i - 1].fd_out == -1)
			ft_print_error(config, ERROR_FD, "1");
		config->file_des[i].fd_in = filedes[0];
		if (config->file_des[i].fd_in == -1)
			ft_print_error(config, ERROR_FD, "1");
		i++;
	}
	i = 2;
	if (config->here_doc_flag == 1)
		i = 3;
	j = 0;
	while (j < config->count_cmd)
		config->file_des[j++].name_cmd = ft_split(av[i++], ' ');
}
