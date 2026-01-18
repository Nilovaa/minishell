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

static int	ft_is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_count_args(char **args)
{
	int	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

int ft_exit(t_pars *pars, t_cmd *cmd)
{
	int		exit_code;
	int		arg_count;

	printf("exit\n");
	if (!pars || !pars->arg || !pars->arg[0])
	{
		if (pars)
			exit_code = pars->return_value;
		else
			exit_code = 0;
		free_all(cmd);
		exit(exit_code);
	}
	arg_count = ft_count_args(pars->arg);
	if (!ft_is_valid_number(pars->arg[0]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(pars->arg[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_all(cmd);
		exit(2);
	}
	if (arg_count > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_code = ft_atoi(pars->arg[0]);
	exit_code = (unsigned char)exit_code;
	free_all(cmd);
	exit(exit_code);
}
