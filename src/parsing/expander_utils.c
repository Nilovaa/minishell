/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:55:23 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/23 03:05:57 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static void	handle_val_utils(char **res, char *val)
{
	char *tmp;

	tmp = ft_strjoin(*res, val);
	free(*res);
	free(val);
	*res = tmp;
}

int	handle_var(char *str, int i, char **res, t_cmd *cmd)
{
	int		start;
	char	*key;
	char	*val;

	i++;
	start = i;
	if (str[i] == '?')
		i++;
	else if (ft_isdigit(str[i]))
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
	handle_val_utils(res, val);
	return (i);
}
