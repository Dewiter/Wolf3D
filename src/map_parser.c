/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolevy <rolevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:14:02 by rolevy            #+#    #+#             */
/*   Updated: 2018/07/24 02:18:30 by rolevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
*** /--------------------------------------------------------------------------\
*** |              _____________ Get Map Size _____________                    |
*** |              Returns the General height and width of                     |
*** |              the map                                                     |
*** |                                                                          |
*** | --> get_next_line will read line per line the counted that it is given   |
*** | --> We get the width of the map by increment an integer (map->with)      |
*** |	  for every it encounters                                              |
*** | --> Every time we get to a line we increment an integers (map->height)   |
*** \--------------------------------------------------------------------------/
*/

static inline t_map	*get_map_size(char *src, t_map *map)
{
	int				fd;
	char			*line = NULL;
	int				l;

	fd = open(src, O_RDONLY);
	l = 0;
	if (get_next_line(fd, &line) > 0)
	{
		while(line[l])
		{
			if(ft_isdigit(line[l]))
				map->width++;
			l++;
		}
	}
	else
		return NULL;
	map->height++;
	while (get_next_line(fd, &line) > 0)
		map->height++;
	close(fd);
	return (map);
}

/*
*** /--------------------------------------------------------------------------\
*** |                 _____________ Parse Map _____________                    |
*** |                 Parse the map given to wolf3d to two                     |
*** |                 dimensional integer array                                |
*** |                                                                          |
*** \--------------------------------------------------------------------------/
*/

static inline int	**parse_map(t_map *map, char *src)
{
	int				**tab;
	int				fd;
	int				index[2];
	char			*line;

	index[0] = 0;
	fd = open(src, O_RDONLY);
	if (!(tab = (int**)malloc(sizeof(int*) * map->height)))
		exit(EXIT_FAILURE);
	while (get_next_line(fd, &line) > 0)
	{
		index[1] = 0;
		if (!(tab[index[0]] = (int*)malloc(sizeof(int) * ft_strlen(line) + 1)))
			return (NULL);
		while (*(line + index[1]))
		{
			tab[index[0]][index[1]] = ft_atoi(line + index[1]);
			index[1]++;
		}
		index[0]++;
	}
	close(fd);
	return (tab);
}

/*
*** /--------------------------------------------------------------------------\
*** |               _____________ Generate Map _____________                   |
*** |                     Creating map used for wolf3d                         |
*** |                                                                          |
*** | --> Allocates memory to map                                              |
*** | --> Get map dimension (get_map_size())                                   |
*** | --> Parse map into a two dimensional integer array (parse_map())         |
*** \--------------------------------------------------------------------------/
*/
t_map				*gen_map(char *src)
{
	t_map			*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	map->height = 0;
	map->width = 0;
	map = get_map_size(src, map);
	map->tab = parse_map(map, src);
	return (map);
}
