#include "../../minishell.h"

int redirect_in_file_append(char *red)
{
    int fd;

    if (!red)
    {
        ft_printf("minishell: No such file or directory\n");
        g_struct->exit_status = 1;
        return -1;
    }
    fd = open(red, O_RDWR| O_CREAT| O_APPEND, 0666);
    if (access(red, W_OK))
    {
        ft_printf("minishell: %s: Permission denied\n", red);
        g_struct->exit_status = 1;
        return -1;
    }
    if (fd < 0)
    {
        ft_printf("minishell: No such file or directory\n");
        g_struct->exit_status = 1;
        return -1;
    }
    return fd;
}
int redirect_in_file(char *red)
{
    int fd;

    if (!red)
    {
        ft_printf("minishell: No such file or directory\n");
        g_struct->exit_status = 1;
        return -1;
    }
    fd = open(red, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (access(red, W_OK))
    {
        ft_printf("minishell: %s: Permission denied\n", red);
        g_struct->exit_status = 1;
        return -1;
    }
    if (fd < 0)
    {
        ft_printf("minishell: No such file or directory\n");
        g_struct->exit_status = 1;
        return -1;
    }
    return fd;
}

int redirect_out_file(char *red)
{
    int fd;

    fd = open(red, O_RDWR);
    if (access(red, F_OK))
    {
        ft_printf("minishell: No such file or directory\n");
        g_struct->exit_status = 1;
        return -1;
    }
    if (access(red, R_OK))
    {
       ft_printf("minishell: %s: Permission denied\n", red);
       g_struct->exit_status = 1;
       return -1;
    }
    return fd;
}

int redirect_out_file_heredoc(char *red)
{
    int pip[2];
    char *str;
    char    *new_str;
    char    *red_cpy;
	char	*str_join;
    int		i;
    int		j;

	j = 0;
    new_str = NULL;
    pipe(pip);
    dup2(g_struct->ppin, 0);
    red = ft_strjoin(red, "\n");
    red_cpy = ft_strdup(red);
    expand_quotes_red(&red_cpy);
    str = get_next_line(0);
    if (!str)
        return -1;
    while (1)
    {
		i = 0;
        if(!ft_strlcmp(red_cpy, str))
            break;
		if(char_in_str(str, '$') && !char_in_str(red, '\"') && !char_in_str(red, '\''))
		{
			while (str[i])
			{
				if(str[i] == '$')
				{
					str[ft_strlen(str)-1] = '\0';
					expand_variables(&new_str, str + i, AST_COMMAND, NOTRIM);
					if(new_str)
                    {
						j = 0;
						while (new_str[j])
						{
							ft_putchar_fd(new_str[j], pip[1]);
							j++;
						}
						i += get_variable_len(str + i + 1);
					}
					free(new_str);
					new_str = NULL;
				}
				else
					ft_putchar_fd(str[i], pip[1]);
                i++;
			}
            ft_putchar_fd('\n', pip[1]);
		}
		else
			ft_putstr_fd(str, pip[1]);
		free(str);
		str = NULL;
        str = get_next_line(0);
    }
    if(red_cpy)
        free(red_cpy);
    close(pip[1]);
    dup2(g_struct->stin, 0);
    return pip[0];
}