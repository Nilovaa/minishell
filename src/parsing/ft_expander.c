/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:58:55 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/20 16:59:37 by andriamr         ###   ########.fr       */
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

int	handle_var(char *str, int i, char **res, t_cmd *cmd)
{
	int		start;
	char	*key;
	char	*val;
	char	*tmp;

	i++;
	start = i;
	if (str[i] == '?')
		i++;
	else
		while (ft_isalnum(str[i]) || str[i] == '_')
			i++;
	if (start == i)
		val = ft_strdup("$");
	else
	{
		key = ft_substr(str, start, i - start);
		val = get_env_val(key, cmd);
		free(key);
	}
	tmp = ft_strjoin(*res, val);
	free(*res);
	free(val);
	*res = tmp;
	return (i);
}

char	*expand_and_clean(char *str, t_cmd *cmd)
{
	char	*res;
	char	*tmp;
	int		i;
	int		q[2];
	char	c[2];

	res = ft_calloc(1, 1);
	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !q[1])
		{
			q[0] = !q[0];
			i++;
		}
		else if (str[i] == '"' && !q[0])
		{
			q[1] = !q[1];
			i++;
		}
		else if (str[i] == '$' && !q[0] && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?'))
			i = handle_var(str, i, &res, cmd);
		else
		{
			c[0] = str[i++];
			c[1] = '\0';
			tmp = ft_strjoin(res, c);
			free(res);
			res = tmp;
		}
	}
	return (res);
}

void	process_all_tokens(t_pars *pars, t_cmd *cmd)
{
	int		i;
	char	*cleaned;

	i = 0;
	if (!pars || !pars->all_token)
		return ;
	while (pars->all_token[i])
	{
		cleaned = expand_and_clean(pars->all_token[i], cmd);
		free(pars->all_token[i]);
		pars->all_token[i] = cleaned;
		i++;
	}
}
