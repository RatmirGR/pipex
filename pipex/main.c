#include "pipex.h"

t_list	*ft_init_config(int ac, char *env[])
{
	t_list	*config;

	config = NULL;
	config = malloc(sizeof(t_list));
	if (config != NULL)
	{
		config->here_doc_flag = 0;
		config->limiter = NULL;
		config->file_des = NULL;
		config->env = env;
		config->count_cmd = ac - 3;
		config->count_paths = 0;
		config->flag = 1;
		config->fork_id = NULL;
		config->file_des = malloc(config->count_cmd * sizeof(t_fd));
		if (config->file_des == NULL)
			ft_print_error(config, ERROR_MEM_FILE_DES, "1");
		ft_init_paths(config, env);
		ft_init_file_des(config);
	}
	else
		ft_print_error(NULL, ERROR_MEM_CONFIG_FILE, "1");
	return (config);
}

int	main(int argc, char *argv[], char *env[])
{
	t_list	*config;

	if (argc >= 5)
	{
		config = ft_init_config(argc, env);
		if (ft_strcmp(argv[1], "here_doc") == 0)
		{
			if (argc >= 6)
			{
				config->here_doc_flag = 1;
				config->limiter = argv[2];
				config->count_cmd -= 1;
			}
			else
				ft_print_error(config, ERROR_ARG, "1");
		}
		ft_init_fd_files(config, argc, argv);
		ft_init_fd_cmds(config, argv);
		ft_pipex(config);
		ft_all_free(config);
	}
	else
		ft_print_error(NULL, ERROR_ARG, "1");
	return (0);
}
