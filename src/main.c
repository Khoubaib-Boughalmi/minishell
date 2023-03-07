#include "../minishell.h"

t_global_struct *gstruct; //global struct

int	repl(void)
{
	char	*input;
	struct termios orig_termios, new_termios;
	/* Save original terminal settings */
    tcgetattr(STDIN_FILENO, &orig_termios);
    /* Set new terminal settings */
    new_termios = orig_termios;
    new_termios.c_lflag &= ~(ICANON); /* Non-canonical mode */
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

	while (1)
	{
		if(gstruct->sigint_listener)
		{
			gstruct->sigint_listener = 0;
			break;
		}
		input = readline("$ ");
		if (!input)
			exit(EXIT_FAILURE);
		if(input[0] == '\0' || input[0] == '\n')
		{
			free(input);
			continue;
		}
		if (!strncmp(input, "exit", 5))
		{
			free(input);
			break;
		}
		add_history(input);
		parse_and_execute(input); //tokenization etc
		free(input);
	}
	/* Restore original terminal settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
	return (0);
}

int main(int ac, char *av[], char *envp[])
{
	(void) ac;
	(void) av;
	t_token_lst *token;
	sig_init(SIGINT, &sigint_hander);
	sig_init(SIGQUIT, &sigquit_hander);
	if(!init_gstruct())
		return (1);
	// init_envp(envp);
	// ft_env();
	// repl();
	token = tokenizer("ls -la ||||ls|||||||| cat -e >>>>> out.txt");
	int i = 0;
	while(token)
	{
		i = 0;
		if(token->token->args)
		{
			if(token->token->type == AST_COMMAND)
			{
				printf("COMMAND: ");
				while (token->token->args[i] != 0)
				{
					printf("%s ", token->token->args[i]);
					i++;
				}
			}
			else
			{
				printf("PIPE: ");
				while (token->token->args[i] != 0)
				{
					printf("%s ", token->token->args[i]);
					i++;
				}

			}			
		}
		if(token->token->type == AST_REDIRECTION)
		{
			printf("REDIR: %s %s", token->token->redirect_fd, token->token->redirect_fname);
		}
		printf("\n");
		token = token->next;
	}
	return (0);
}