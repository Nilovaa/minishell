/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 08:58:40 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/11 09:29:53 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parssing.h"

int check_pipe(char *str)
{
	int i;
	int	last;

	i = 0;
	last = 0;
	if (ft_count_pipe(str) == 0)
		return (0);
	i += skip_space(str);
	if (str[i] == '|')
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
			last = i;
		i++;
	}
	if (last != 0)
		last += skip_space(&str[last]) + 1;
	while (ft_is_space(str[last]))
		last++;
	if (!str[last + 1])
		return (0);
	return (1);
}
