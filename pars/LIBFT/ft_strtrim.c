/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:03:28 by andriamr          #+#    #+#             */
/*   Updated: 2025/04/06 11:08:10 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	char	*trim;
	int		i;
	int		last;

	i = 0;
	last = ft_strlen(s1) - 1;
	str = (char *)s1;
	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, str[i]) && i <= last)
		i++;
	if (i > last)
		return (ft_strdup(s1 + last + 1));
	while (last >= i && ft_strchr(set, str[last]))
		last--;
	trim = malloc(sizeof(char) * ((last - i + 2)));
	if (!trim)
		return (NULL);
	ft_strlcpy(trim, &str[i], last - i + 2);
	return (trim);
}
