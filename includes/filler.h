/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 13:46:59 by kmoussai          #+#    #+#             */
/*   Updated: 2019/03/26 11:22:48 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "get_next_line.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct	s_map
{
	char		**tab;
	int			h_size;
	int			w_size;
	int			x_size;
}				t_map;

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct	s_filler
{
	int			id;
	char		c;
	char		*name;
	t_map		map;
	char		**piece;
	int			piece_len;
	int			piece_h;
	int			piece_w;
	t_pos		*pos_tab;
}				t_filler;

t_pos			ft_xytopos(int x, int y);
double			ft_sqrt(double n);
double			ft_distance(t_pos p1, t_pos p2);
double			calc_d(t_filler filler, int x, int y, char c);
int				checkposition_bis(t_filler filler, t_pos pos, int i, int j);
int				checkposition(t_filler f, t_pos pos, double *p);
int				checkneighbor(int i, int j, t_filler filler);
t_filler		ft_getpostab(t_filler filler, int i, int j);
char			*ft_getname(char *str);
char			**ft_read_piece(int height, int *piece_len);
t_map			ft_read_map(t_map map, char c);
t_filler		ft_readplateau(t_filler filler, char *line);
t_filler		ft_readpiece(t_filler filler, char *line);
void			ft_print_result(t_pos pos);
void			ft_freetab(char **tab, int n);
t_pos			ft_getpos(t_filler filler, double min);
int				ft_count(char *tab, char c);
#endif
