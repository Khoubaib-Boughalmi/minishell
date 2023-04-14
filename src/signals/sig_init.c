/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:40:20 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/14 16:41:48 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sig_init(int sig, void (*sig_handler)(int))
{
	struct sigaction	act;

	act.sa_handler = sig_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	if (sig == SIGINT)
	{
		if (sigaction(SIGINT, &act, 0) < 0)
			perror("minishell :");
	}
	else if (sig == SIGQUIT)
	{
		if (sigaction(SIGQUIT, &act, 0) < 0)
			perror("sigaction error :");
	}
}
