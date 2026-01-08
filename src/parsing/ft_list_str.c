/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 11:20:36 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/08 14:33:24 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>

t_str	*new_list(char *str)
{
	t_str	*new;
	int		j;
	int 	len;
	j = 0;
	new = malloc(sizeof(t_str));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	if (!new->str)
		return (NULL);
	new->next = NULL;
	return (new);
}

void 	add_list_str(t_str *list, char *str)
{
	t_str	*firs;
	t_str	*new;
	t_str	*tmp;
	
	tmp = list;
	new = new_list(str);
	if (!new)
	{
		list = new;
		return ;
	}
	firs = list;
	while (firs->next != NULL)
		firs = firs->next;
	firs->next = new;
	firs->next = NULL;
	list = tmp;
}

