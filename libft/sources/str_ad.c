/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_ad.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 08:06:08 by shunt             #+#    #+#             */
/*   Updated: 2019/09/20 00:59:20 by huller           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ns(char **s)
{
	char	*r;
	int		i;

	if (!(r = (char *)malloc(sizeof(char) * (ft_strlen(*s) + 2))))
		return ;
	r[0] = '1';
	i = -1;
	while ((*s)[++i])
		r[i + 1] = (*s)[i];
	r[i + 1] = '\0';
	free(*s);
	*s = r;
}

void		str_ad(char **s1, char *s2)
{
	int		i;

	i = ft_strlen(*s1);
	while (--i >= 0)
	{
		(*s1)[i] = (*s1)[i] - '0' + s2[i];
		if ((*s1)[i] > '9')
		{
			(*s1)[i] -= 10;
			if (i - 1 >= 0 && (*s1)[i - 1] != '.')
				++(*s1)[i - 1];
			else if (i - 2 >= 0 && (*s1)[i - 1] == '.')
				++(*s1)[i - 2];
			else if (i - 1 < 0)
				ns(s1);
		}
	}
}
