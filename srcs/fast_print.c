/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 11:01:37 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/24 02:22:40 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		buffer(char *buff, int *buff_i, char *src, int size)
{
	while (BUFF_SIZE - *buff_i < size)
	{
		size -= BUFF_SIZE - *buff_i;
		while (*buff_i < BUFF_SIZE)
			buff[(*buff_i)++] = *(src++);
		write(1, buff, BUFF_SIZE);
		*buff_i = 0;
	}
	while (size--)
		buff[(*buff_i)++] = *(src++);
}

static void		putnbr_in_buffer(char *buff, int *buff_i, int n)
{
	if (n >= 10)
	{
		putnbr_in_buffer(buff, buff_i, n / 10);
		putnbr_in_buffer(buff, buff_i, n % 10);
	}
	else
	{
		while (BUFF_SIZE - *buff_i < 1)
		{
			write(1, buff, *buff_i);
			*buff_i = 0;
		}
		buff[(*buff_i)++] = '0' + n;
	}
}

void			fast_print(t_lem *l, t_room **ant, char *buff, int *buff_i)
{
	int				i;
	int				flag;

	flag = 0;
	i = 0;
	while (++i <= l->ant_count)
		if (ant[i])
		{
			flag ? buffer(buff, buff_i, " ", 1) : 0;
			buffer(buff, buff_i, "L", 1);
			putnbr_in_buffer(buff, buff_i, i);
			buffer(buff, buff_i, "-", 1);
			buffer(buff, buff_i, ant[i]->name, ft_strlen(ant[i]->name));
			flag = 1;
			ant[i] == l->end ? ant[i] = NULL : 0;
		}
	buffer(buff, buff_i, "\n", 1);
}
