/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:34:15 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/24 20:36:05 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_make_args(t_pars *pars)
{
	int		i;
	int		len;
	char	**argv;

	i = 0;
	len = 0;
	while (pars->arg && pars->arg[len])
		len++;
	argv = malloc(sizeof(char *) * (len + 2));
	if (!argv)
		return (NULL);
	argv[0] = pars->cmd;
	while (i < len)
	{
		argv[i + 1] = pars->arg[i];
		i++;
	}
	argv[i + 1] = NULL;
	return (argv);
}

void	no_such_file(t_pars *pars)
{
	ft_putstr_fd(pars->cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	pars->return_value = 127;
}

char	*ft_handle_direct_path(t_pars *pars)
{
	if (access(pars->cmd, F_OK) != 0)
	{
		ft_putstr_fd(pars->cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		pars->return_value = 127;
		return (NULL);
	}
	if (access(pars->cmd, X_OK) != 0)
	{
		ft_putstr_fd(pars->cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		pars->return_value = 126;
		return (NULL);
	}
	return (ft_strdup(pars->cmd));
}
