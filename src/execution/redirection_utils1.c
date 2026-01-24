/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:23:51 by andriamr          #+#    #+#             */
/*   Updated: 2026/01/24 20:26:15 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_tmp_heredoc(void)
{
	static int	count = 0;
	char		*file;

	file = ft_make_heredoc_name(count);
	while (file && access(file, F_OK) == 0)
	{
		free(file);
		count++;
		file = ft_make_heredoc_name(count);
	}
	count++;
	return (file);
}

char	*ft_make_heredoc_name(int count)
{
	char	*num;
	char	*file;

	num = ft_itoa(count);
	if (!num)
		return (NULL);
	file = ft_strjoin("/tmp/.heredoc_", num);
	free(num);
	return (file);
}
