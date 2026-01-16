/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 03:31:33 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/16 15:57:10 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_exit(t_pars *pars, t_cmd *cmd)
{
	int i;

	i = 0;
	if (pars && pars->arg)
	{
		while(pars->arg[i])
		{
			if (!ft_isdigit(pars->arg[0][i]))
				break;
			i++;
		}
		if (!pars->arg[0][i])
			return (ft_atoi(pars->arg[0]));
	}
	else if (pars)
		exit(pars->return_value);
	free_all(cmd);
	exit(0);
}
