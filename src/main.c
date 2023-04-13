/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:51:33 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/13 20:28:41 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_global_struct	*gstruct;

int	repl(void)
{
	char	*input;

	input = NULL;
	while (1)
	{
		if(gstruct->sigint_listener)
		{
			gstruct->sigint_listener = 0;
			exit(gstruct->exit_status);
			break;
		}
		input = readline("$ ");
		if (!input)
		{
			free_all();
			exit(gstruct->exit_status);
		}
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		tokenize_expand_execute(input); //tokenization etc
		free(input);
		}
	return (gstruct->exit_status);
}

int main(int ac, char *av[], char *envp[])
{
	(void) ac;
	(void) av;
	sig_init(SIGINT, &sigint_hander);
	sig_init(SIGQUIT, &sigquit_hander);
	if(!init_gstruct())
		return (1);
	init_envp(envp);
	repl();
	return (gstruct->exit_status);
}