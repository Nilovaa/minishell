/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 02:55:49 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/03/13 14:05:36 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_word(char const *s, char c)
{
	int		word;

	word = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			while (*s && *s != c)
				s++;
			word++;
		}
	}
	return (word);
}

char	**ft_split(char const *s1, char c)
{
	int		i;
	int		j;
	int		start;
	int		word;
	char	**str;

	i = 0;
	j = 0;
	start = 0;
	word = ft_count_word(s1, c);
	str = malloc(sizeof(char *) * (word + 1));
	if (!str || !s1)
		return (NULL);
	while (j < word)
	{
		while (s1[i] == c)
			i++;
		start = i;
		while (s1[i] && s1[i] != c)
			i++;
		str[j] = ft_substr(s1, start, i - start);
		j++;
	}
	str[word] = 0;
	return (str);
}

void	ft_free_split(char **val)
{
	int	i;

	i = 0;
	while (val[i] != NULL)
	{
		free(val[i]);
		i++;
	}
	free(val);
}
