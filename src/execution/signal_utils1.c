/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:20:43 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/24 20:20:59 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_handle_sigint_heredoc(int sig)
{
	int	fd;

	(void)sig;
	fd = ft_get_heredoc_fd();
	if (fd >= 0)
		close(fd);
	close(STDIN_FILENO);
	write(1, "\n", 1);
	rl_clear_history();
	exit(130);
}
