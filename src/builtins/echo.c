/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:03:35 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/16 14:33:41 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_expansion(char *str, t_pars *pars)
{
	int		i;
	int		start;
	char	*key;
	char	*value;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			if (str[i] == '?')
			{
				ft_putnbr_fd(pars->return_value, 1);
				i++;
			}
			else if (ft_isalpha(str[i]) || str[i] == '_')
			{
				start = i;
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
				key = ft_substr(str, start, i - start);
				if (key)
				{
					value = getenv(key);
					if (value)
						ft_putstr_fd(value, 1);
					free(key);
				}
			}
			else
			{
				write(1, "$", 1);
			}
		}
		else
		{
			write(1, &str[i], 1);
			i++;
		}
	}
}

int	ft_echo(t_pars *pars)
{
	int	i;
	int	j;
	int	n;

	if (!pars)
		return (0);
	i = 0;
	n = 0;
	if (!pars->arg || !pars->arg[0])
	{
		write(1, "\n", 1);
		pars->return_value = 0;
		return (0);
	}
	while (pars->arg[i] && pars->arg[i][0] == '-' && pars->arg[i][1] == 'n')
	{
		j = 1;
		while (pars->arg[i][j] == 'n')
			j++;
		if (pars->arg[i][j] != '\0')
			break;
		n = 1;
		i++;
	}
	while (pars->arg[i])
	{
		// ft_expansion(pars->arg[i], pars);
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
