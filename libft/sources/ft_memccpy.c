/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huller <huller@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:26:29 by huller            #+#    #+#             */
/*   Updated: 2019/09/20 00:59:20 by huller           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*b;

	i = 0;
	p = ((unsigned char *)dst);
	b = ((unsigned char *)src);
	while (i < n && b[i] != (unsigned char)c)
	{
		p[i] = b[i];
		i++;
	}
	if (i != n && b[i] == (unsigned char)c)
		p[i] = b[i];
	return (i == n ? NULL : dst + i + 1);
}
