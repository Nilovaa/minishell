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

#include "../../include/minishell.h"

void	ft_echo_expand(char *str, t_pars *pars)
{
	int		i = 0;
	int		start;
	char	*key;
	char	*value;

	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
			{
				ft_putnbr_fd(pars->return_value, 1);
				i++;
			}
			else
			{
				start = i;
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
				key = ft_substr(str, start, i - start);
				if (!key)
					return;
				value = getenv(key);
				if (value)
					write(1, value, ft_strlen(value));
				free(key);
			}
		}
		else
			write(1, &str[i++], 1);
	}
}


int	ft_echo(t_pars *pars)
{
	int	i = 1;
	int	j;
	int	n = 0;

	if (!pars || !pars->arg)
		return (0);

	while (pars->arg[i])
	{
		j = 1;
		if (pars->arg[i][0] != '-')
			break;
		while (pars->arg[i][j] == 'n')
			j++;
		if (pars->arg[i][j] != '\0')
			break;
		n = 1;
		i++;
	}

	while (pars->arg[i])
	{
		ft_echo_expand(pars->arg[i], pars);
		if (pars->arg[i + 1])
			write(1, " ", 1);
		i++;
	}

	if (!n)
		write(1, "\n", 1);

	pars->return_value = 0;
	return (0);
}
