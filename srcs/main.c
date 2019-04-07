/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:38:47 by kmoussai          #+#    #+#             */
/*   Updated: 2019/03/26 15:27:38 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_pos	ft_getpos(t_filler filler, double min)
{
	int		i;
	int		j;
	t_pos	pos_toret;
	double	p;

	i = 0;
	pos_toret = ft_xytopos(0, 0);
	while (i < filler.map.h_size)
	{
		j = -1;
		while (j++ < filler.map.w_size)
		{
			if (checkposition(filler, ft_xytopos(i, j), &p))
			{
				if (min == -1.0)
					min = p;
				else if (min > p)
					min = p;
				if (min == p)
					pos_toret = ft_xytopos(i, j);
			}
		}
		i++;
	}
	return (pos_toret);
}

void	ft_freetab(char **tab, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		ft_strdel(&tab[i]);
		i++;
	}
	ft_memdel((void **)tab);
}

int		ft_count(char *tab, char c)
{
	int count;

	count = 0;
	while (*tab)
	{
		if (*tab == c && c == '*')
		{
			count++;
			tab++;
			continue;
		}
		if (*tab == c || *tab == c + 32)
			count++;
		tab++;
	}
	return (count);
}

void	ft_print_result(t_pos pos)
{
	ft_putnbr_fd(pos.x, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(pos.y, 1);
	ft_putchar_fd('\n', 1);
}

int		main(void)
{
	char		*line;
	t_filler	filler;

	filler.map.h_size = 0;
	if (get_next_line(0, &line) && line && !ft_strncmp(line, "$$$ exec p", 10))
	{
		filler.id = line[10] - 48;
		filler.name = ft_getname(line + 15);
		filler.c = (filler.id == 1) ? 'O' : 'X';
	}
	while (get_next_line(0, &line))
	{
		if (!line)
			continue;
		if (!ft_strncmp(line, "Plateau", 7))
			filler = ft_readplateau(filler, line);
		else if (!ft_strncmp(line, "Piece", 5))
			filler = ft_readpiece(filler, line);
		ft_strdel(&line);
	}
	ft_strdel(&filler.name);
	return (0);
}
