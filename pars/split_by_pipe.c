/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:10:37 by andriamr          #+#    #+#             */
/*   Updated: 2025/12/11 10:27:07 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/libft.h"
#include "parssing.h"

static char	*cpy_cmd(char *str, char *dest)
{
	int	i;

	i = 0;
	while (i < len_sep(str))
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**utils_split(char *str, char **dest)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	if (ft_count_pipe(str) == 0)
		return (ft_putstr_fd("ERROR QUOTE\n", 2) ,NULL);
	while (j < ft_count_pipe(str))
	{
		if (str[i] == '|')
		{
			free_cmd2(dest);
			return (dest);
		}
		dest[j] = ft_calloc(sizeof(char), len_sep(&str[i]) + 1);
		if (!dest[j])
			return (free_cmd2(dest), free (str), NULL);
		cpy_cmd(&str[i], dest[j]);
		tmp = len_sep(&str[i]);
		i =  i + tmp + 1 ;
		j++;
	}
	dest[j] = NULL;
	return (dest);
}

char	**split_pipe(char *str)
{
	char	**dest;

	if (str[0] == '\0')
		return (NULL);
	dest = ft_calloc(sizeof(char *), (ft_count_pipe(str)) + 1);
	if (!dest)
		return (NULL);
	dest = utils_split(str, dest);
	return (dest);
}
