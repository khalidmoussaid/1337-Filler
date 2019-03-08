#include "filler.h"

#include <fcntl.h>

int fd;

typedef struct s_map
{
	char **tab;
	int h_size;
	int w_size;
}           t_map;

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct s_filler
{
	int id;
	char c;
	char *name;
	t_map map;
	char **piece;
	int     piece_len;
    int     piece_h;
    int     piece_w;
}               t_filler;

t_pos	ft_xytopos(int x, int y)
{
	t_pos p;

	p.x = x;
	p.y = y;
	return (p);
}
int		checkposition(t_filler filler, t_pos pos, t_pos *p)
{
	/*
	
		....*
		...**
		..***
		.....
	000 .................
	001 .................
	002 .................
	003 .................
	004 .................
	005 .................
	006 .................
	007 .................
	008 ..O..............
	009 .................
	010 .................
	011 .................
	012 ..............X..
	013 .................
	014 .................
	*/
	int i = 0;
	int j;
	int h = 0;
	while (i < filler.piece_h )
	{
		
		j = 0;
		while(j < filler.piece_w)
		{
			if (i + pos.x >= filler.map.h_size || i + pos.x < 0 || j + pos.y < 0 || j + pos.y >= filler.map.w_size)
				return (0);
			if (filler.map.tab[i + pos.x][j + pos.y] != '.' && filler.map.tab[i + pos.x][j + pos.y] != filler.c)
				return (0);
			if (filler.piece[i][j] == '*')
			{
				printf("[%d,%d]\n", i + pos.x, j + pos.y);
				if (filler.map.tab[i + pos.x][j + pos.y] == filler.c)
				{
					*p = ft_xytopos(i + pos.x, j + pos.y);
					h++;
				}
			}
			
			j++;
		}
		i++;
	}
	if (h == 1)
		return (1);
	return (0);
}

typedef struct s_option
{
	t_pos			pos;
	int				dist;
	struct s_option	*next;
}				t_option;

int			ft_sqrt(int n)
{
	int i;

	i = 1;
	while (i <= n)
	{
		if (i * i >= n)
			return i;
		i++;
	}
	return -1;
}

int 	ft_distance(t_pos p1, t_pos p2)
{
	int a;
	int b;

	a = p2.x - p1.x;
	b = p2.y - p1.y;
	return (a * a + b * b);
}

void		ft_addoption(t_option **l, t_pos p, int dist)
{
	t_option *t;

	t = (t_option *)malloc(sizeof(t_option));
	t->pos = p;
	t->dist = dist;
	t->next = NULL;
	
	if (!*l)
		*l = t;
	else 
	{
		t->next = *l;
		*l = t;
	}
}


t_pos 	ft_getlastpos(t_filler filler)
{
	char	c;
	int		i;
	int		j;
	t_pos	p;

	i = 0;
	c = (filler.id == 1) ? 'x' : 'o';
	p = ft_xytopos(0, 0);
	while (i < filler.map.h_size)
	{
		j = 0;
		while (j < filler.map.w_size)
		{
			if (filler.map.tab[i][j] == c)
				return (ft_xytopos(i, j));
			j++;
		}
		i++;
	}
	return (p);
}

t_pos 	ft_getpos(t_filler filler)
{
	int i = 0;
	int j = 0;
	t_pos pos;
	t_pos pos_toret;
	t_pos p2;
	t_option *l;
	t_pos	p;

	l = NULL;
	p2 = ft_getlastpos(filler);
	pos = ft_xytopos(0, 0);
	pos_toret = ft_xytopos(0, 0);
	int min;
	int min_new = 0;
	min = -1;
	while (i < filler.map.h_size)
	{
		j = 0;
		while (j < filler.map.w_size)
		{
			
			pos = ft_xytopos(i, j);
			if (checkposition(filler, pos, &p))
			{
				min_new = ft_distance(p, p2);;
				if (min == -1)
				{
					min = min_new;
					pos_toret = pos;
				}else if (min < min_new)
				{
					min = min_new;
					pos_toret = pos;
				}
				break;
			}
			j++;
		}
		i++;
	}
	return (pos_toret);
}

char *ft_getname(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ']')
		i++;
	str[i] = 0;
	return (ft_strdup(str));
}

void	ft_freetab(char **tab, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char **ft_read_map(t_map map)
{
	char *line;
	int i;
	char **tab;
	map.tab = (char **)malloc(sizeof(char *) * map.h_size);
	get_next_line(0, &line);
	ft_strdel(&line);
	i = 0;
	while(i < map.h_size)
	{
		get_next_line(0, &line);
		tab = ft_strsplit(line, ' ');
		map.tab[i] = ft_strdup(tab[1]);
		ft_freetab(tab, 3);
		ft_strdel(&line);
		i++;
	}
	return (map.tab);
}

void		ft_printtable(char **tab, int size)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		ft_putnbr(i);
		while (tab[i][j])
		{
			ft_putchar(tab[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}


char **ft_read_piece(int height, int width, int *piece_len)
{
	int i;
	char *line;
	char **piece;
	int j;
	int len;

	piece = (char **)malloc(sizeof(char *) * height);
	i = 0;
	while (i < height)
	{
		get_next_line(0, &line);
		piece[i] = line;
		i++;
	}

	i = 0;
	len = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (piece[i][j] == '*')
				len++;
			j++;
		}
		i++;
	}
	*piece_len = len;
	return (piece);
}

int main(void)
{
	char *line;
	char **tab;
	t_filler filler;
	t_pos pos;

	fd = open("/Users/kmoussai/Desktop/1337_file/42/filler/trace", O_WRONLY | O_CREAT);

	//ft_putstr_fd("START\n", fd);
	// $$$ exec pPLAYER_NUMBER : [PLAYER_NAME]
	if (get_next_line(0, &line) && line && !ft_strncmp(line,"$$$ exec p",10))
	{
		//ft_putendl_fd(line, fd);
		filler.id = line[10] - 48;
		filler.name = ft_getname(line + 15);
		filler.c = (filler.id == 1) ? 'O' : 'X';
	}
	while (get_next_line(0, &line))
	{
		
		if (!line)
			continue;
		//ft_putendl_fd(line, fd);
		if (!ft_strncmp(line, "Plateau", 7))
		{
			
			tab = ft_strsplit(line, ' ');
			filler.map.h_size = ft_atoi(tab[1]);
			filler.map.w_size = ft_atoi(tab[2]);
			ft_freetab(tab, 4);
			filler.map.tab = ft_read_map(filler.map);
		}
		else if (!ft_strncmp(line, "Piece", 5))
		{
			tab = ft_strsplit(line, ' ');
            filler.piece_h = ft_atoi(tab[1]);
            filler.piece_w = ft_atoi(tab[2]);
			filler.piece = ft_read_piece(filler.piece_h, filler.piece_w, &filler.piece_len);

			ft_freetab(tab, 4);
			/*int i = 0;
			while (i < filler.piece_h)
			{
				ft_putstr_fd(filler.piece[i],1);
				ft_putchar_fd('\n', 1);
			
				i++;
			}*/
			pos = ft_getpos(filler);
           	ft_putnbr_fd(pos.x,1);
           	ft_putchar_fd(' ', 1);
            ft_putnbr_fd(pos.y,1);
            ft_putchar_fd('\n', 1);
            //printf("%d %d\n",pos.x, pos.y);
			 //break;
		}
		ft_strdel(&line);
		// ft_printtable(filler.map.tab, filler.map.h_size);
	}
	close(fd);



	return 0;
}
