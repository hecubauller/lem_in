/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huller <huller@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 20:18:10 by huller            #+#    #+#             */
/*   Updated: 2020/05/14 12:42:00 by huller           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				extend_array(void **array, size_t array_size, size_t elem_size)
{
	void			*new_array;

	if (!(new_array = (void *)malloc(elem_size * (array_size + SIZE_DIFF + 1))))
		return (0);
	if (*array)
	{
		ft_memcpy(new_array, *array, elem_size * array_size);
		free(*array);
	}
	*array = new_array;
	return (1);
}

int				write_check_num(char *s, int *n)
{
	int				i;
	char			*num;

	if (!*s || !((*s >= '0' && *s <= '9') || *s == '-' || *s == '+'))
		return (0);
	*n = ft_atoi(s);
	i = (*s == '-' || *s == '+') ? 0 : -1;
	while (s[++i] == '0')
		;
	if (!(num = ft_itoa(*n)) ||
		(*s == '-' && ft_strncmp(num + 1, s + i, ft_strlen(num) - 1)) ||
		(*s != '-' && ft_strncmp(num, s + (*n ? i : i - 1), ft_strlen(num))) ||
		(*s == '-' && !*n))
	{
		num ? free(num) : 0;
		return (0);
	}
	i += (*n ? ft_strlen(num) : 0) - (*s == '-' ? 1 : 0);
	free(num);
	return (i);
}

static void		free_solution(t_lem *l)
{
	int				i;
	int				j;

	i = -1;
	while (++i < l->solution_count)
	{
		j = -1;
		while (++j < l->solution[i]->path_count)
			free(l->solution[i]->room[j]);
		free(l->solution[i]->path_length);
		free(l->solution[i]->room);
		free(l->solution[i]);
	}
	free(l->solution);
}

void			free_all(t_lem *l)
{
	int				i;
	int				j;

	i = -1;
	while (++i < l->stdin_size)
		free(l->stdin[i]);
	l->stdin ? free(l->stdin) : 0;
	i = -1;
	while (++i < l->room_count)
	{
		j = -1;
		while (++j < l->room[i]->tube_count)
			free(l->room[i]->tube[j]);
		free(l->room[i]->tube);
		free(l->room[i]->name);
		free(l->room[i]);
	}
	l->room ? free(l->room) : 0;
	l->queue ? free(l->queue) : 0;
	l->solution ? free_solution(l) : 0;
}
