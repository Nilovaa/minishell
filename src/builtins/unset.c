/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 01:36:33 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/12/29 03:36:38 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_check_name(char *str)
{
	int i;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int ft_find_var(char **env, char *name)
{
	int i = 0;
	int len = ft_strlen(name);
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
			return(i);
		i++;
	}
	return (-1);
}

static char **ft_remove_var(char **env, int index_env)
{
	int i = 0, j = 0;
	char **dest_env;
	while (env[i])
		i++;
	dest_env = malloc(sizeof(char *) * i);
	if (!dest_env)
		return (NULL);
	while (env[i])
	{
		if (i != index_env)
			dest_env[j++] = ft_strdup(env[i]);
		i++;
	}
	dest_env[j] = NULL;
	return (dest_env);
}

int	ft_unset(t_pars *pars, char ***env)
{
	int i;
	int check;
	int index_env;
	char **dest_env;
	if (!pars || !pars->arg || !pars->arg[1])
	{
		pars->return_value = 0;
		return (0);
	}
	i = 1;
	check = 0;
	while (pars->arg[i])
	{
		if (!ft_check_name(pars->arg[i]))
		{
			ft_putstr_fd("unset : not a valid identifier", 2);
			check = 1;
			i++;
			continue;
		}
		index_env = ft_find_var(*env, pars->arg[1])	;
		if (index_env >= 0)
		{
			dest_env = ft_remove_var(*env, index_env);
			ft_free_split(*env);
			*env = dest_env;
		}
		i++;
	}
	pars->return_value = 0;
	return (check);
}
