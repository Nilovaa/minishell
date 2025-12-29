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

#include "../pars/parssing.h"

int	ft_env(t_pars *pars, char **env)
{
	int	i;
	if (!pars)
		return (1);
	if (pars->arg && pars->arg[1])
	{
		ft_putstr_fd("env : too many arguments", 2);
		pars->return_value = 1;
		return (1);
	}
	i = 0;
	while (env && env[i])
	{
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	pars->return_value = 0;
	return (0);
}
