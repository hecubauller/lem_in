/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huller <ubyrd@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 09:54:07 by huller            #+#    #+#             */
/*   Updated: 2020/05/23 09:57:27 by huller           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

/*
** ---------- FLAGS ----------
*/

# define F_ANTS   (1u << 5u)
# define F_ROOMS  (1u << 4u)
# define F_RSTART (1u << 3u)
# define F_REND   (1u << 2u)
# define F_START  (1u << 1u)
# define F_END    (1u << 0u)

/*
** ---------- MACROS ----------
*/

# define ABS(a)    ((a) > 0 ? (a) : -(a))
# define MAX(a, b) ((a) > (b) ? (a) : (b))
# define MIN(a, b) ((a) < (b) ? (a) : (b))

# define SIZE_DIFF  0x7F
# define PTR_SIZE   8
# define ROOM_SIZE  48
# define TUBE_SIZE  24

# define COM_START  "##start"
# define COM_END    "##end"

# define MAX_CAPAC  1

# define PRINT_BUFF_SIZE  2048

/*
** ---------- STRUCTURES ----------
*/

typedef struct s_room	t_room;

typedef struct	s_tube
{
	t_room			*room;
	int				capacity;

	struct s_tube	*pair;
}				t_tube;

struct			s_room
{
	char			*name;
	t_tube			**tube;
	int				tube_count;
	int				x;
	int				y;

	t_tube			*prev;
	char			in_solution;

	int				ant;
};

typedef struct	s_solution
{
	t_room			***room;
	int				path_count;
	int				*path_length;
	int				path_sum_length;

	int				turn_count;
}				t_solution;

typedef	struct	s_lem
{
	unsigned short	flags;
	char			**stdin;
	int				stdin_size;

	int				ant_count;
	t_room			*start;
	t_room			*end;
	t_room			**room;
	int				room_count;

	t_room			**queue;
	int				left;
	int				right;

	t_solution		**solution;
	int				solution_count;
	int				best_solution;
}				t_lem;

/*
** ---------- FUNCTIONS ----------
*/

/*
** utils.c
*/
int				extend_array(void **array, size_t array_size, size_t elem_size);
int				write_check_num(char *s, int *n);
void			free_all(t_lem *l);

/*
** reader_room.c
*/
int				is_add_room(t_lem *l, char *line);

/*
** reader_tube.c
*/
int				is_add_tube(t_lem *l, char *line);

/*
** reader.c
*/
int				read_check_create_graph(t_lem *l);

/*
** find_best_flow.c
*/
int				analyze_current_flow(t_lem *l, int path_count);

/*
** find_best_flow.c
*/
int				check_solution(t_lem *l, int path_count);
int				find_best_flow(t_lem *l);

/*
** fast_print.c
*/
void			fast_print(t_lem *l, t_room **ant, char *buff, int *buff_i);

/*
** print.c
*/
int				print(t_lem *l);

#endif
