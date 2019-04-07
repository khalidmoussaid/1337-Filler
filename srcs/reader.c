/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:59:30 by kmoussai          #+#    #+#             */
/*   Updated: 2019/03/26 15:58:48 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char		*ft_getname(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ']')
		i++;
	str[i] = 0;
	return (ft_strdup(str));
}

t_map		ft_read_map(t_map map, char c)
{
	char	*line;
	int		i;

	map.tab = (char **)malloc(sizeof(char *) * map.h_size);
	map.x_size = 0;
	get_next_line(0, &line);
	ft_strdel(&line);
	i = 0;
	while (i < map.h_size)
	{
		get_next_line(0, &line);
		map.tab[i] = ft_strsub(line, 4, map.w_size);
		map.x_size += ft_count(map.tab[i], c);
		ft_strdel(&line);
		i++;
	}
	return (map);
}

char		**ft_read_piece(int height, int *piece_len)
{
	int		i;
	char	*line;
	char	**piece;

	piece = (char **)malloc(sizeof(char *) * height);
	i = 0;
	while (i < height)
	{
		get_next_line(0, &line);
		piece[i] = line;
		*piece_len += ft_count(line, '*');
		i++;
	}
	return (piece);
}

t_filler	ft_readplateau(t_filler filler, char *line)
{
	char **tab;

	if (filler.map.h_size == 0)
	{
		tab = ft_strsplit(line, ' ');
		filler.map.h_size = ft_atoi(tab[1]);
		filler.map.w_size = ft_atoi(tab[2]);
		ft_freetab(tab, 4);
	}
	filler.map = ft_read_map(filler.map, (filler.id == 1) ? 'X' : 'O');
	filler.pos_tab = (t_pos *)malloc(filler.map.x_size * sizeof(t_pos));
	filler = ft_getpostab(filler, 0, 0);
	return (filler);
}

t_filler	ft_readpiece(t_filler filler, char *line)
{
	char	**tab;
	t_pos	pos;

	tab = ft_strsplit(line, ' ');
	filler.piece_h = ft_atoi(tab[1]);
	filler.piece_w = ft_atoi(tab[2]);
	filler.piece = ft_read_piece(filler.piece_h, &filler.piece_len);
	ft_freetab(tab, 4);
	pos = ft_getpos(filler, -1.0);
	ft_print_result(pos);
	ft_freetab(filler.piece, filler.piece_h);
	ft_freetab(filler.map.tab, filler.map.h_size);
	ft_memdel((void **)&filler.pos_tab);
	return (filler);
}
