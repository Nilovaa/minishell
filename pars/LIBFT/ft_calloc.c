/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:32:51 by andriamr          #+#    #+#             */
/*   Updated: 2025/03/19 14:57:56 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*str;

	if (size != 0 && (nmemb != ((nmemb * size) / size)))
		return (NULL);
	str = malloc (nmemb * size);
	if (!str)
		return (NULL);
	ft_bzero (str, nmemb * size);
	return (str);
}
