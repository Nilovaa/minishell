/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 07:03:45 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/16 16:22:14 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *add_cmd(char **all_token)
{
	char	*cmd;
	int  	i;

	i = 0;

	cmd = NULL;
	if (!all_token)
		return (NULL);
	while (all_token[i])
	{
		if (ft_strncmp(all_token[i], ">", 1) == 0 || ft_strncmp(all_token[i], "<", 1) == 0)
		{
			i++;
			if (all_token[i])
				i++;
		}
		else 
			return (ft_strdup(all_token[i]));
	}
	// else if (all_token[0] && !((ft_strncmp(all_token[0], ">", 1) == 0
	// 	|| ft_strncmp(all_token[0], "<", 1) == 0 )))
	// 	return (ft_strdup(all_token[0]));
	// else if (all_token[0] && (ft_strncmp(all_token[0], ">", 1) == 0
	// 	|| ft_strncmp(all_token[0], "<", 1) == 0 ))
	// {
	// 	if (all_token[2])
	// 		add_cmd(&all_token[2]);
	// }
	// cmd = ft_strdup(all_token[2]);
	return (cmd);
}


char *get_cmd_name(char **tokens)
{
    int i;
	
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
