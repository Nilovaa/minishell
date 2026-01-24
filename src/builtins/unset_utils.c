/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:45:22 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/24 20:46:44 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_find_var1(char **env, char *name)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	free_env_error(char **env, int len)
{
	while (--len >= 0)
		free(env[len]);
	free(env);
	return (0);
}
