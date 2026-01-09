/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 03:46:54 by nyrakoto          #+#    #+#             */
/*   Updated: 2026/01/09 03:46:57 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_listtochar(t_env *env)
{
	t_env	*tmp;
	char	**result;
	char	*temp;
	int		i;
	int		count;

	tmp = env;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		temp = ft_strjoin(tmp->key, "=");
		if (!temp)
			return (ft_free_split(result), NULL);
		result[i] = ft_strjoin(temp, tmp->value);
		free(temp);
		if (!result[i])
			return (ft_free_split(result), NULL);
		tmp = tmp->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}