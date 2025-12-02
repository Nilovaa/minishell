/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 09:03:51 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/02 11:59:05 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parssing.h"

void	ft_exit(void)
{
	exit (1);
}

void	free_cmd2(char **dest)
{
	int	i;

	i = 0;
	while (dest[i])
	{
		free (dest[i]);
		i++;
	}
	free (dest);
}


void free_all(t_cmd *cmd)
{
	int i;

	i = 0;
	if (cmd->sav)
	{
		free(cmd->sav->line);
		if (cmd->sav->split_pipe)
			free_cmd2(cmd->sav->split_pipe);
		free(cmd->sav);
	}
	
}