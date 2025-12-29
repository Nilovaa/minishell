/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrakoto <nyrakoto@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 03:31:33 by nyrakoto          #+#    #+#             */
/*   Updated: 2025/12/29 03:53:00 by nyrakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars/parssing.h"

int ft_exit(t_pars *pars)
{
	if (pars && pars->arg && pars->arg[1])
	{
		ft_putstr_fd("exit : too many arguments\n", 2);
		pars->return_value = 1;
		return (1);
	}
	if (pars)
		exit(pars->return_value);
	exit(0);
}
