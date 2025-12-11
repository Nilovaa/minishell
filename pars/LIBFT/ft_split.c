/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:48:51 by andriamr          #+#    #+#             */
/*   Updated: 2025/11/24 11:58:47 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(char const	*s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			count++;
		i++;
	}
	if (s[i - 1] != c)
		count++;
	return (count);
}

static size_t	len_word(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static void	free_word(char **dest)
{
	int	i;

	i = 0;
	while (dest[i])
	{
		free (dest[i]);
		i++;
	}
}

static char	**utils(char const *s, char c, char **dest)
{
	size_t	j;
	size_t	i;
	size_t	k;

	i = 0;
	j = 0;
	while (j < count_word(s, c))
	{
		while (s[i] == c)
			i++;
		k = 0;
		dest[j] = ft_calloc(sizeof(char), len_word(&s[i], c) + 1);
		if (!dest[j])
			return (free_word(&dest[j]), NULL);
		while (s[i] != '\0' && s[i] != c)
		{
			dest[j][k] = s[i];
			k++;
			i++;
		}
		j++;
	}
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;

	if (s == NULL)
		return (NULL);
	dest = (char **) ft_calloc(sizeof (char *), (count_word(s, c) + 1));
	if (!dest)
		return (NULL);
	dest = utils (s, c, dest);
	return (dest);
}
