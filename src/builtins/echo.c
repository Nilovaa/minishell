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

static void	ft_expand_variable(char *str, int *i)
{
	int		start;
	char	*key;
	char	*value;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	key = ft_substr(str, start, *i - start);
	if (key)
	{
		value = getenv(key);
		if (value)
			ft_putstr_fd(value, 1);
		free(key);
	}
}

void	ft_expansion(char *str, t_pars *pars)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			if (str[i] == '?')
			{
				ft_print_exit_code(pars);
				i++;
			}
			else if (ft_isalpha(str[i]) || str[i] == '_')
				ft_expand_variable(str, &i);
			else
				write(1, "$", 1);
		}
		else
		{
			write(1, &str[i], 1);
			i++;
		}
	}
}

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
