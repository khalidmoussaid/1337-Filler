/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:48:00 by kmoussai          #+#    #+#             */
/*   Updated: 2019/03/26 15:58:29 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_pos	ft_xytopos(int x, int y)
{
	t_pos p;

	p.x = x;
	p.y = y;
	return (p);
}

double	ft_sqrt(double n)
{
	double x0;
	double x1;
	double delta;

	x0 = n;
	while (1)
	{
		x1 = x0 - (x0 * x0 - n) / (2 * x0);
		delta = (x1 - x0) / x0;
		if (delta < .000001 && delta > -.000001)
			return (x1);
		x0 = x1;
	}
}

double	ft_distance(t_pos p1, t_pos p2)
{
	double a;
	double b;

	a = (double)(p2.x - p1.x);
	b = (double)(p2.y - p1.y);
	return (ft_sqrt(a * a + b * b));
}

double	calc_d(t_filler filler, int x, int y, char c)
{
	int		h;
	double	min_d;
	double	d;

	h = 0;
	c = 'a';
	min_d = -1;
	while (h < filler.map.x_size)
	{
		d = ft_distance(ft_xytopos(x, y), filler.pos_tab[h]);
		if (min_d == -1)
			min_d = d;
		else if (d < min_d)
			min_d = d;
		h++;
	}
	return (min_d);
}
