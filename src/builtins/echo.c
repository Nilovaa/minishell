/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:03:35 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/24 12:20:54 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_check_n_flag(char *arg)
{
	int	j;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	j = 1;
	while (arg[j] == 'n')
		j++;
	if (arg[j] != '\0')
		return (0);
	return (1);
}

static int	ft_parse_flags(t_pars *pars, int *n)
{
	int	i;

	i = 0;
	*n = 0;
	while (pars->arg[i] && ft_check_n_flag(pars->arg[i]))
	{
		*n = 1;
		i++;
	}
	return (i);
}

int	ft_echo(t_pars *pars)
{
	int	i;
	int	n;

	if (!pars || !pars->arg || !pars->arg[0])
	{
		if (pars)
			pars->return_value = 0;
		write(1, "\n", 1);
		return (0);
	}
	i = ft_parse_flags(pars, &n);
	while (pars->arg[i])
	{
		ft_putstr_fd(pars->arg[i], 1);
		if (pars->arg[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n)
		write(1, "\n", 1);
	pars->return_value = 0;
	return (0);
}
