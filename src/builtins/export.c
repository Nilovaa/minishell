/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:49:23 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/24 20:48:46 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	*free_env_error1(char **env, int len)
{
	while (--len >= 0)
		free(env[len]);
	free(env);
	return (NULL);
}

int	copy_old_env(char **dest, char **src)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
		{
			free_env_error1(dest, i);
			return (-1);
		}
		i++;
	}
	return (i);
}

char	**ft_add_var(t_cmd *cmd, char *var)
{
	char	**dest;
	int		len;
	int		idx;

	len = 0;
	while (cmd->env && cmd->env[len])
		len++;
	dest = malloc(sizeof(char *) * (len + 2));
	if (!dest)
		return (NULL);
	idx = copy_old_env(dest, cmd->env);
	if (idx == -1)
		return (NULL);
	dest[idx] = ft_strdup(var);
	if (!dest[idx])
		return (free_env_error1(dest, idx));
	dest[idx + 1] = NULL;
	return (dest);
}

static int	ft_no_arg(t_pars *pars, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!pars->arg[0])
	{
		pars->return_value = 0;
		while (cmd && cmd->env && cmd->env[i])
		{
			ft_putstr_fd("export ", 1);
			ft_putstr_fd(cmd->env[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
		return (1);
	}
	return (0);
}

int	ft_export(t_pars *pars, t_cmd *cmd)
{
	int	j;

	if (!pars || !pars->arg)
	{
		pars->return_value = 0;
		return (0);
	}
	if (ft_no_arg(pars, cmd))
		return (0);
	j = 0;
	while (pars->arg[j])
	{
		if (ft_arg_export(pars, cmd, j))
			return (1);
		j++;
	}
	pars->return_value = 0;
	return (0);
}
