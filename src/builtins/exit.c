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
	int	sign;

	if (!str || !*str)
		return (0);
	i = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (sign == -1 || str[0] == '+')
		return (ft_atoll(str + 1, sign));
	return (ft_atoll(str, sign));
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

static int	ft_exit_only(t_pars *pars, t_cmd *cmd)
{
	int	exit_code;

	if (cmd)
		exit_code = cmd->last_exit_status;
	else if (pars)
		exit_code = pars->return_value;
	else
		exit_code = 0;
	if (pars && pars->global)
		pars->global->exit = 1;
	if (pars)
		pars->return_value = exit_code;
	return (exit_code);
}

static int	ft_exit_arg(t_pars *pars, t_cmd *cmd, int arg_count)
{
	if (!ft_is_valid_number(pars->arg[0]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(pars->arg[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		if (pars && pars->global)
			pars->global->exit = 1;
		if (pars)
			pars->return_value = 2;
		(void)cmd;
		return (2);
	}
	if (arg_count > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	ft_exit(t_pars *pars, t_cmd *cmd)
{
	int	exit_code;
	int	arg_count;

	printf("exit\n");
	if (!pars || !pars->arg || !pars->arg[0])
	{
		return (ft_exit_only(pars, cmd));
	}
	arg_count = ft_count_args(pars->arg);
	if (ft_exit_arg(pars, cmd, arg_count))
	{
		if (pars && pars->global && pars->global->exit)
			return (pars->return_value);
		return (1);
	}
	exit_code = ft_atoi(pars->arg[0]);
	exit_code = (unsigned char)exit_code;
	if (pars && pars->global)
		pars->global->exit = 1;
	if (pars)
		pars->return_value = exit_code;
	(void)cmd;
	return (exit_code);
}
