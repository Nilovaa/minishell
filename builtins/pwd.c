/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:04:19 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/12/29 03:36:46 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars/parssing.h"

int ft_pwd(t_pars *pars)
{
	char	path[PATH_MAX];
	if (!getcwd(path, sizeof(path)))
	{
		perror("pwd");
		pars->return_value = 1;
		return (1);
	}
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	pars->return_value = 0;
	return (0);
}
