/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:04:19 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/12/29 03:36:46 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_pars *pars)
{
	char	path[PATH_MAX];

	if (!getcwd(path, sizeof(path)))
	{
		perror("pwd");
		pars->return_value = 1;
		return (1);
	}
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	pars->return_value = 0;
	return (0);
}

void	ft_print_exit_code(t_pars *pars)
{
	ft_putnbr_fd(pars->return_value, 1);
}

int	ft_is_only_spaces(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atol(char *str, int sign)
{
	long long	result;
	int			i;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (sign == 1 && (result > LLONG_MAX / 10
				|| (result == LLONG_MAX / 10
					&& (str[i] - '0') > LLONG_MAX % 10)))
			return (1);
		if (sign == -1 && (result > -(LLONG_MIN / 10)
				|| (result == -(LLONG_MIN / 10)
					&& (str[i] - '0') > -(LLONG_MIN % 10))))
			return (1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (0);
}
