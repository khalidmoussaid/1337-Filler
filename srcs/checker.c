/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:55:18 by kmoussai          #+#    #+#             */
/*   Updated: 2019/03/26 15:46:44 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			checkposition_bis(t_filler filler, t_pos pos, int i, int j)
{
	if (i + pos.x >= filler.map.h_size || i + pos.x < 0
		|| j + pos.y < 0 || j + pos.y >= filler.map.w_size)
		return (1);
	if (filler.map.tab[i + pos.x][j + pos.y] != '.'
		&& (filler.piece[i][j] == '*'
		&& filler.map.tab[i + pos.x][j + pos.y] != filler.c))
		return (1);
	return (0);
}

int			checkposition(t_filler f, t_pos pos, double *p)
{
	int i;
	int j;
	int h;

	i = 0;
	h = 0;
	while (i < f.piece_h)
	{
		j = -1;
		while (j++ < f.piece_w)
		{
			if (checkposition_bis(f, pos, i, j))
				return (0);
			if (f.piece[i][j] == '*')
			{
				*p = calc_d(f, i + pos.x, j + pos.y, (f.id == 1 ? 'X' : 'O'));
				if (f.map.tab[i + pos.x][j + pos.y] == f.c)
					h++;
				if (h == 2)
					return (0);
			}
		}
		i++;
	}
	return (h == 1 ? 1 : 0);
}

int			checkneighbor(int i, int j, t_filler filler)
{
	int c;

	c = 0;
	if (i - 1 >= 0 && filler.map.tab[i - 1][j] == '.')
		c++;
	if (j + 1 < filler.map.w_size && filler.map.tab[i][j + 1] == '.')
		c++;
	if (i + 1 < filler.map.h_size && filler.map.tab[i + 1][j] == '.')
		c++;
	if (j - 1 >= 0 && filler.map.tab[i][j - 1] == '.')
		c++;
	if (filler.map.h_size > 50)
		return (c >= 3 ? 1 : 0);
	return (c >= 1 ? 1 : 0);
}

t_filler	ft_getpostab(t_filler filler, int i, int j)
{
	int		k;
	char	c;

	k = 0;
	c = (filler.id == 1) ? 'X' : 'O';
	while (i < filler.map.h_size)
	{
		j = 0;
		while (j < filler.map.w_size)
		{
			if ((filler.map.tab[i][j] == c || filler.map.tab[i][j] == c - 32)
				&& checkneighbor(i, j, filler))
			{
				filler.pos_tab[k].x = i;
				filler.pos_tab[k].y = j;
				k++;
			}
			j++;
		}
		i++;
	}
	filler.map.x_size = k;
	return (filler);
}
