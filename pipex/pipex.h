#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define ERROR_ARG "Invalid number of arguments"
# define ERROR_MEM_PATHS "Memory allocation error for paths"
# define ERROR_MEM_FILE_DES "Memory allocation error for file descriptor"
# define ERROR_MEM_CONFIG_FILE "Memory allocation error for config file"
# define ERROR_MEM_FORK_FD "Memory allocation error for fork_fd"
# define ERROR_PATH "Error path not found"
# define ERROR_FORK_FD "Error fork"
# define ERROR_FILE "No such file or directory"
# define ERROR_CMD "Command not found"
# define ERROR_PIPE "Error pipe"
# define ERROR_FD "Error file descriptor"
# define ERROR_DUP2 "Error dup2"

typedef struct s_fd
{
	char	**name_cmd;
	int		fd_in;
	int		fd_out;
}		t_fd;

typedef struct s_list
{
	char	**paths;
	char	**env;
	char	*limiter;
	t_fd	*file_des;
	int		count_cmd;
	int		here_doc_flag;
	int		flag;
	int		count_paths;
	pid_t	*fork_id;
}			t_list;

char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_line_len(char **line);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_init_paths(t_list *config, char *env[]);
void	ft_init_file_des(t_list *config);
void	ft_init_fd_files(t_list *config, int ac, char *av[]);
void	ft_init_fd_cmds(t_list *config, char *av[]);
void	ft_pipex(t_list *config);
void	ft_all_free(t_list *config);
void	ft_print_error(t_list *config, char *desc, char *name);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_close_file_descriptors(t_list *config);

#endif
