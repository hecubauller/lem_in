/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chck_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 00:16:00 by shunt             #+#    #+#             */
/*   Updated: 2019/09/20 00:59:20 by huller           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	chck_x(t_rd **read, va_list **ap)
{
	(*read)->mod_smb = 'x';
	if ((*read)->size == 0)
		(*read)->mod = ft_ox(va_arg(**ap, unsigned int), 16, 1);
	else if ((*read)->size == 1)
		(*read)->mod = ft_ox(va_arg(**ap, unsigned long), 16, 1);
	else if ((*read)->size == 2)
		(*read)->mod = ft_ox(va_arg(**ap, unsigned long long), 16, 1);
	else if ((*read)->size == 4)
		(*read)->mod = ft_ox((unsigned short)va_arg(**ap, unsigned int), 16, 1);
	else if ((*read)->size == 8)
		(*read)->mod = ft_ox((unsigned char)va_arg(**ap, unsigned int), 16, 1);
	else if ((*read)->size == 16)
		(*read)->mod = ft_ox(va_arg(**ap, uintmax_t), 16, 1);
	else if ((*read)->size == 32 || (*read)->size == 64)
		(*read)->mod = ft_ox(va_arg(**ap, size_t), 16, 1);
	else if ((*read)->size == 128)
		(*read)->mod = ft_ox(va_arg(**ap, u_int64_t), 16, 1);
	if ((((*read)->kostil == 1 || (*read)->prs != 6) &&
	((long)ft_strlen((*read)->mod)) < (*read)->prs) || ((*read)->mod[0] == '0'
	&& !(*read)->mod[1] && !(*read)->prs))
		(*read)->mod = ft_ro(&(*read)->mod, (*read)->prs, read, 1);
}
