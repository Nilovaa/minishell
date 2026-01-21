/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:47:00 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/16 11:24:45 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_str	*init_str(char *str)
{
	t_str	*new;

	new = malloc (sizeof(t_str));
	if (!new)
		return (NULL);
	new->str = str;
	return (new);
}

t_str	*add_str_last(t_str *list, char *str)
{
	t_str	*new;
	t_str	*temp;

	new = init_str(str);
	if (!new)
		return (NULL);
	if (!list)
		return (new);
	temp = list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (list);
}

t_str	*char_to_list(char **str)
{
	t_str	*list;
	int		i;

	list = NULL;
	i = 0;
	while (str[i])
	{
		list = add_str_last(list, str[i]);
		if (!list)
			return (NULL);
		i++;
	}
	return (list);
}

int	ft_list_size_str(t_str *list)
{
	t_str	*temp;
	int		i;

	temp = list;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

char	**list_to_char(t_str *list)
{
	char	**str;
	t_str	*temp;
	int		i;

	str = ft_calloc(sizeof(char *), ft_list_size_str(list) + 1);
	if (!str)
		return (NULL);
	temp = list;
	i = 0;
	while (temp)
	{
		str[i] = temp->str;
		temp = temp->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}
