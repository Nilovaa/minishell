/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 21:47:52 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/12/29 03:36:49 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd(t_pars *pars)
{
	if (!pars || !pars->arg)
	{
		ft_putstr_fd("cd : need an argument\n", 2);
		pars->return_value = 1;
		return (1);
	}
	if (chdir(pars->arg[0]) != 0)
	{
		perror("cd");
		pars->return_value = 1;
		return (1);
	}
	chdir(pars->arg[0]);
	pars->return_value = 0;
	return (0);
}
