/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:37:55 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/23 04:16:40 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_space(char c)
{
	if ((c > 9 && c < 13) || c == 32)
		return (1);
	return (0);
}

int	skip_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_space(str[i]))
			break ;
		i++;
	}
	return (i);
}

int	check_qote(char *str)
{
	int	i;
	int	cot1;
	int	cot2;

	i = 0;
	cot1 = 0;
	cot2 = 0;
	while (str[i])
	{
		if (str[i] == 39 && !cot2)
			cot1 = !cot1;
		else if (str[i] == '"' && !cot1)
			cot2 = !cot2;
		i++;
	}
	if (cot1 || cot2)
		return (1);
	return (0);
}

t_cmd	*ft_init_cmd_base(char **env)
{
	t_cmd	*cmd_base;

	cmd_base = cmd_init(NULL, env, 0);
	return (cmd_base);
}

char	*get_cmd_name(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], ">", 1) == 0
			|| ft_strncmp(tokens[i], "<", 1) == 0)
		{
			if (tokens[i + 1])
				i += 2;
			else
				i++;
		}
		else
			return (tokens[i]);
	}
	return (NULL);
}
