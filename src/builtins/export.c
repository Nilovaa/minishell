/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:49:23 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/12/29 03:36:41 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_find_var(char **env, char *name)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (name[len] && name[len] != '=')
		len++;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char **ft_add_var(char **env, char *var)
{
	char	**dest_env;
	int		i;
	i = 0;
	while (env && env[i])
		i++;
	dest_env = malloc(sizeof(char *) * (i + 2));
	if (!dest_env)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		dest_env[i] = ft_strdup(env[i]);
		i++;
	}
	dest_env[i+1] = ft_strdup(var);
	dest_env[i] = NULL;
	return (dest_env);
}

int	ft_export(t_pars *pars, char ***env)
{
	int i;
	int j;
	char **dest_env;
	if (!pars || !pars->arg || !pars->arg[1])
	{
		pars->return_value = 0;
		return (0);
	}
	j = 1;
	while (pars->arg[j])
	{
		if (!ft_strchr(pars->arg[1], '='))
		{
			ft_putstr_fd("export : invalid format\n", 2);
			pars->return_value = 1;
			return (1);
		}
		i = ft_find_var(*env, pars->arg[1]);
		if (i >= 0)
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(pars->arg[1]);
		}
		else 
		{
			dest_env = ft_add_var(*env, pars->arg[1]);
			ft_free_split(*env);
			*env = dest_env;
		}
		j++;
	}
	pars->return_value = 0;
	return (0);
}
