/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:58:55 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/21 20:56:43 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_val(char *var, t_cmd *cmd)
{
	int		i;
	int		len;

	if (*var == '?')
		return (ft_itoa(cmd->last_exit_status));
	i = 0;
	len = ft_strlen(var);
	while (cmd->env && cmd->env[i])
	{
		if (ft_strncmp(cmd->env[i], var, len) == 0 && cmd->env[i][len] == '=')
			return (ft_strdup(cmd->env[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

static void	ft_append_char(t_expand *tools, char c)
{
	char	str[2];
	char	*tmp;

	str[0] = c;
	str[1] = '\0';
	tmp = ft_strjoin(tools->res, str);
	free(tools->res);
	tools->res = tmp;
	tools->i++;
}

static int	ft_handle_quotes(char c, t_expand *tools)
{
	if (c == '\'' && !tools->q[1])
	{
		tools->q[0] = !tools->q[0];
		tools->i++;
		return (1);
	}
	if (c == '"' && !tools->q[0])
	{
		tools->q[1] = !tools->q[1];
		tools->i++;
		return (1);
	}
	return (0);
}

static void	init_tools(t_expand *tools)
{
	tools->res = ft_calloc(1, 1);
	tools->i = 0;
	tools->q[0] = 0;
	tools->q[1] = 0;
}

char	*expand_and_clean(char *str, t_cmd *cmd)
{
	t_expand	tools;

	init_tools(&tools);
	if (!tools.res)
		return (NULL);
	while (str[tools.i])
	{
		if (ft_handle_quotes(str[tools.i], &tools))
			continue ;
		if (str[tools.i] == '$' && !tools.q[0]
			&& (ft_isalnum(str[tools.i + 1])
				|| str[tools.i + 1] == '_' || str[tools.i + 1] == '?'))
		{
			tools.i = handle_var(str, tools.i, &tools.res, cmd);
		}
		else
		{
			ft_append_char(&tools, str[tools.i]);
		}
	}
	return (tools.res);
}
