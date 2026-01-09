/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 03:31:33 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/09 11:41:37 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_exit(t_cmd *cmd)
{
	if (cmd->all)
		exit(cmd->all->return_value);
	free_all(cmd);
	exit(0);
}
