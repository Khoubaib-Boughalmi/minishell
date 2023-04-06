#include "../../minishell.h"

char	**get_paths(t_envp_node *envp)
{
	char	*def;

	if (!envp)
	{
		def = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
		def = ft_strdup(def);
		return (ft_split(def, ':'));
		free(def);
	}
	while (envp)
	{
		if (ft_strnstr(envp->key, "PATH", 4))
			return (ft_split(envp->value, ':'));
		envp = envp->next;
	}
	return (NULL);
}

char	*path_finder(char *cmd, t_envp_node *envp)
{
	char	*tmp;
	char	**path;
	char	*tmp2;
	int		i;

	path = get_paths(envp);
	if (!path)
		return (0);
	i = -1;
	while (path[++i])
	{
		tmp2 = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp2, cmd);
		free(tmp2);
		if (!access(tmp, F_OK))
		{
			free_split(path);
			return (tmp);
		}
		free(tmp);
	}
	free_split(path);
	return (0);
}
void red_in_last(t_redirection        **list_reds, int *fd)
{
    int i = 0;
    int t = -1;
    while(list_reds[i])
    {
				if (list_reds[i]->type == OUTPUT)
					t = fd[i];
				if (list_reds[i]->type == APPEND)
					t = fd[i];
        i++;
    }
    if (t != -1)
        dup2(t, 1);
}
void red_out_last(t_redirection        **list_reds, int *fd)
{
    int i = 0;
    int t = -1;

    while(list_reds[i])
    {
        if (list_reds[i]->type == INPUT)
            t = fd[i];
        if (list_reds[i]->type == HEREDOC)
            t = fd[i];
        i++;
    }
    if (t != -1)
        dup2(t, 0);
}

int splcount(t_redirection **list_reds)
{
	int count = 0;

	while (list_reds[count])
		count++;
	return (count);
}

int redirect_in_out(t_redirection **list_reds)
{
	int i = 0;
	int *fd;

	fd = malloc(splcount(list_reds) * sizeof(int));
	while(list_reds[i])
	{
		if (char_in_str(list_reds[i]->value, '\"') && char_in_str(list_reds[i]->value, ' '))
			printf("%s: ambiguous redirect", list_reds[i]->value);
		else
		{
			if (list_reds[i]->type == OUTPUT)
			{
				fd[i] = redirect_in_file(list_reds[i]->value);
				if (fd[i] < 0)
					return 1;
			}
			if (list_reds[i]->type == APPEND)
			{
				fd[i] = redirect_in_file_append(list_reds[i]->value);
				if (fd[i] < 0)
					return 1;
			}
			if (list_reds[i]->type == INPUT)
			{
				fd[i] = redirect_out_file(list_reds[i]->value);
				if (fd[i] < 0)
					return 1;
			}
		}
		if (list_reds[i]->type == HEREDOC)
		{
			fd[i] = redirect_out_file_heredoc(list_reds[i]->value);
			if (fd[i] < 0)
				return 1;
		}
		i++;
	}
	red_in_last(list_reds, fd);
	red_out_last(list_reds, fd);
	return 0;
}

void	cmd_not_found(char **cmd)
{
	// write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, "minishell : command not found\n", 31);
	// perror("minishell :");
	free_split(cmd);
	exit (127);
}

void    ex_main(t_token_lst *token1, t_token_lst *token2)
{
	int		fd[2];
	char **str;
	t_redirection **list_reds;

    pipe(fd);		
	gstruct->stout = dup2(fd[1], 1);
	close(fd[1]);
	str = create_lst_commands(token1);
	list_reds = create_lst_redirections(token1);
	int a1;
	signal(SIGINT, &sigint_hander_executor);
	a1 = fork();
	if (a1 == 0)
	{
		if(is_builtin(str[0]))
		{
			handle_builtin(str);
			exit(gstruct->exit_status);
		}
		if (redirect_in_out(list_reds))
			exit(gstruct->exit_status);
		if (str[0] && path_finder(str[0], gstruct->envp_head))
			execve(path_finder(str[0], gstruct->envp_head), str, get_envp_arr());
		else
			cmd_not_found(str);
	}
	waitpid(a1, &gstruct->exit_status, 0);
	gstruct->stin = dup2(fd[0], 0);
	close(fd[0]);
	executor(token2);
}
