/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_g.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 09:40:37 by shunt             #+#    #+#             */
/*   Updated: 2019/09/20 00:59:20 by huller           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_g(long double g, int a, size_t b, unsigned short int c)
{
	char	*f;
	char	*e;
	int		i;

	f = ft_fld(g, a);
	e = ft_e(g, a);
	i = -1;
	while (f[++i] && f[i] != '.')
		;
	if (f[0] == '-')
		--i;
	if ((int)b < i)
	{
		free(f);
		return (ft_rg(e, b, c));
	}
	else
	{
		free(e);
		return (ft_rg(f, b, c));
	}
}
