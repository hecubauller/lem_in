/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chck_g.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 00:16:00 by shunt             #+#    #+#             */
/*   Updated: 2019/09/20 00:59:20 by huller           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	chck_g(t_rd **read, va_list **ap, int a)
{
	if (a)
	{
		(*read)->mod_smb = 'g';
		if ((*read)->size == 128)
			(*read)->mod = ft_g(va_arg(**ap,
						long double), 1, (*read)->prs, (*read)->flag);
		else
			(*read)->mod = ft_g(va_arg(**ap,
						double), 1, (*read)->prs, (*read)->flag);
	}
	else
	{
		(*read)->mod_smb = 'G';
		if ((*read)->size == 128)
			(*read)->mod = ft_g(va_arg(**ap, long double), 0, (*read)->prs,
					(*read)->flag);
		else
			(*read)->mod = ft_g(va_arg(**ap, double), 0, (*read)->prs,
					(*read)->flag);
	}
}
