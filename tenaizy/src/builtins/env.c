/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 03:26:18 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/12/29 03:36:30 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_pars *pars, t_cmd *cmd)
{
	int	i;

	if (!pars)
		return (1);
	i = 0;
	while (cmd->env && cmd->env[i])
	{
		ft_putstr_fd(cmd->env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	pars->return_value = 0;
	return (0);
}
