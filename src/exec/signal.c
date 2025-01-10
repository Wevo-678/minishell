/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alribeyr <alribeyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:10:30 by alribeyr          #+#    #+#             */
/*   Updated: 2025/01/10 17:10:49 by alribeyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_rl_line(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
}

static void	handle_sigint(int code)
{
	(void)code;
	printf("\n");
	clear_rl_line();
	g_signal_pid = 130;
}

static void	handle_sigabrt(int code)
{
	(void)code;
	write(1, "abort\n", 6);
}

void	signals2(void)
{
	signal(SIGQUIT, SIG_DFL);
}

void	signals(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGABRT, &handle_sigabrt);
	signal(SIGQUIT, SIG_IGN);
}
