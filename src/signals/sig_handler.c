/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:42:31 by kboughal          #+#    #+#             */
/*   Updated: 2023/04/14 16:43:33 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sigint_hander(int sig)
{
	(void)sig;
	printf("\n");
}

void	sigint_hander_executor(int sig)
{
	(void)sig;
	dup2(g_struct->ppout, 1);
	dup2(g_struct->ppin, 0);
	printf("\n");
}

void	sigquit_hander(int sig)
{
}
