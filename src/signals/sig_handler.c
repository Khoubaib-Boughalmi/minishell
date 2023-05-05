/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:42:31 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/05 14:33:03 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sigint_hander(int sig)
{
	(void)sig;
    ft_printf("\n");
    rl_on_new_line();
    // rl_replace_line("", 0);
    rl_redisplay();
}

void	sigint_hander_executor(int sig)
{
	(void)sig;
	dup2(g_struct->ppout, 1);
	dup2(g_struct->ppin, 0);
	(void)sig;
    ft_printf("\n");
    rl_on_new_line();
    // rl_replace_line("", 0);
    // rl_redisplay();
}

void	sigquit_hander(int sig)
{
	
}
