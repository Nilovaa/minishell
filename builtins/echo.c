/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:03:35 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/12/28 22:29:37 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars/parssing.h"
#include <unistd.h>

int	ft_echo(t_pars *pars)
{
	int	i;
	int j;
	int	n;

	i = 1;
	n = 0;
	if (!pars || !pars->arg)
		return (pars->return_value = 0);
	while (pars->arg[i] && pars->arg[i][0])
	{
		j = 1;
		while (pars->arg[i][j] == 'n')
			j++;
		if (pars->arg[i][j] != '\0' || j == 1)
			break;
		n = 1;
		i++;
	}
	while (pars->arg[i])
	{
		ft_putstr_fd(pars->arg[i], 1);
		if (pars->arg[i+1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	pars->return_value = 0;
	return (0);
}
