/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:51:33 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/11 13:23:40 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parssing.h"

void add_list_last(t_pars *pars, char *split_pipe)
{
	t_pars	*last;
	t_pars	*first;

	last = init_token(split_pipe);
	if (pars == NULL)
	{
		pars = last;
		return;
	}
	first = pars;
	while (first->next != NULL)
		first = first->next;
	first->next = last;
	last->next = NULL;
}

t_pars	*init_token(char *split_pipe)
{
	t_pars	*pars;
	t_pars	*tmp;
	
	pars = ft_calloc(sizeof(t_pars), 1);
	if (!pars)
		return (NULL);
	pars->count_token = count_token(split_pipe);
	pars->all_token = split_token(split_pipe);
	if (!pars->all_token)
		return (NULL);
	pars->redir = init_dir(pars->all_token);
	if (!pars->redir)
		return (NULL);
	pars->cmd = pars->all_token[0];
	tmp = pars;
	pars->arg = cpy_arg(tmp);
	if (!pars->arg)
		return (NULL);
	pars->next = NULL;
	return (pars);
}
