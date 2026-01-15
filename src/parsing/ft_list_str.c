/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:47:00 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/15 16:47:44 by andriamr         ###   ########.fr       */
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
