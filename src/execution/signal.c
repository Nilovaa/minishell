/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 02:13:41 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/24 20:16:08 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_signal_received = 0;

void	ft_set_heredoc_fd(int fd)
{
	g_signal_received = fd;
}

int	ft_get_heredoc_fd(void)
{
	return (g_signal_received);
}

void	ft_handle_sigint(int sig)
{
	(void)sig;
	g_signal_received = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	ft_get_signal_received(void)
{
	return (g_signal_received);
}

void	ft_reset_signal_received(void)
{
	g_signal_received = 0;
}
