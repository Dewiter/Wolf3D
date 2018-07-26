/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolevy <rolevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 14:12:51 by rolevy            #+#    #+#             */
/*   Updated: 2018/07/25 05:13:34 by rolevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int				is_pos_in_bound(t_map *map, int x, int y)
{
	if (map->width > x && map->height > y && x >= 0 && y >= 0)
		return (1);
	else
		return (0);
}

int				clamp(int nbr, int min, int max)
{
	if (nbr < min)
		return (min);
	else if (nbr > max)
		return (max);
	else
		return (nbr);
}

void			normalize_out_of_bound(t_map *map, int *x, int *y)
{
	*x = clamp(*x, 0, map->width);
	*y = clamp(*y, 0, map->height);
}

/*
*** /--------------------------------------------------------------------------\
*** |                 _____________ Find Wall _____________                    |
*** |		              This function will find a wall                       |
*** |                                                                          |
*** | --> We loop until we actually hit a wall with ray->hit which acts        |
*** |	  as a boolean                                                         |
*** | --> We move on the the x-axis or the y-axis of the map index by comparing|
*** |	  the distance between the player and the current x/y coordinate       |
*** |	  that the ray is pointing                                             |
*** | --> if the distance(x) < distance(y) then                                |
*** |	  we move on the x-axis and we increment the distance(x) by Delta(x)   |
*** | --> if the distance(x) > distance(y) then                                |
*** |	  we move on the y-axis, we increment the distance(y) by Delta(y)      |
*** | --> we save in what orientation we hit the wall (NS/WE)                  |
*** | --> For safe measures we lock the value x and y values if they hit their |
*** |	  min / max values (normalize_out_of_bound())
*** \--------------------------------------------------------------------------/
*/

static inline void		find_wall(t_ray *ray, t_map *map)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->coord_dist.x < ray->coord_dist.y)
		{
			ray->coord_dist.x += ray->delta.x;
			map->index.x += (int)ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->coord_dist.y += ray->delta.y;
			map->index.y += (int)ray->step.y;
			ray->side = 1;
		}
		if (!is_pos_in_bound(map, map->index.x, map->index.y))
		{
			normalize_out_of_bound(map, &map->index.x, &map->index.y);
			ray->hit = 1;
			return ;
		}
		if (map->tab[map->index.x][map->index.y] > 0)
			ray->hit = 1;
	}
}

/*
*** /--------------------------------------------------------------------------\
*** |                 _____________ Get Texture pos _____________              |
*** |                  Get texture position to stick to the wall               |
*** |                                                                          |
*** | --> We pinpoint the exact pos hit point on the wall that we previously   |
*** |	  founded by                                                           |
*** |	  HitPoint = PlayerPos + WallDistance * RayDistance                    |
*** | --> We Stick the wall to that position previously calculated by          |
*** |	  TexturePos = TextureWidth - Hitpoint - 1                             |
*** \--------------------------------------------------------------------------/
*/

static inline void		get_texture_pos(t_ray *ray, t_player *player)
{
	double				wall_hit;

	if (ray->side == 0)
		wall_hit = player->pos.y + ray->wall_dist * ray->val.y;
	else
		wall_hit = player->pos.x + ray->wall_dist * ray->val.x;
	ray->tex_pos = (int)(wall_hit * (TEXTWIDTH));
	if (ray->side == 0 && ray->val.x > 0)
		ray->tex_pos = TEXTWIDTH - wall_hit - 1;
	if (ray->side == 1 && ray->val.y < 0)
		ray->tex_pos = TEXTWIDTH - wall_hit - 1;
}

/*
*** /--------------------------------------------------------------------------\
*** |                 _____________ Distance to Wall _____________             |
*** |		          Calculate distance between the player and the role       |
*** |                                                                          |
*** | --> We get the distance by                                               |
*** |	  Distance to Wall = (MapIndex(x/y) - PlayerPos(x/y) + (1 - *Step(x/y))|
*** |	 				    / 2) *RayDir(x/y))                                 |
*** | --> The use of the x-axis or y-axis is determined by the orientation     |
*** |	  saved previously                                                     |
*** |                                                                          |
*** | (*)Step	: Moved forward or backwards in the Map coords                 |
*** | (*)RayDir	: The direcionnal vector                                       |
*** \--------------------------------------------------------------------------/
*/

static inline void	get_wall_dist(t_ray *ray, t_map *map, t_player *player)
{
	if (ray->side == 0)
		ray->wall_dist = (map->index.x - player->pos.x
						+ (1 - ray->step.x) / 2) / ray->val.x;
	else
		ray->wall_dist = ((map->index.y - player->pos.y
						+ (1 - ray->step.y) / 2) / ray->val.y);
}

/*
*** /--------------------------------------------------------------------------\
*** |                _____________ Get Wall Height _____________               |
*** |                Calculate relative height of wall based on                |
*** |                the distance calculated previously                        |
*** |                                                                          |
*** | --> Determine bottom of the wall by                                      |
*** |	  (-1 * (*)WallHeight / 2) + (Screen Height / 2)                       |
*** | --> Determine top of the wall by                                         |
*** |	  ((*)WallHeight / 2) + (Screen Height / 2)                            |
*** |                                                                          |
*** | (*)WallHeight : Wall general height within the screen                    |
*** |               (ScreenHeight / DistanceToWall)                            |
*** \--------------------------------------------------------------------------/
*/

static inline void	get_wall_height(t_ray *ray)
{
	int				integral_height;

	integral_height = (int)ray->wall_dist;
	if (integral_height == 0)
		ray->wall.height = HEIGHT;
	else
		ray->wall.height = (int)(HEIGHT / ray->wall_dist);
	ray->wall.start = (-ray->wall.height / 2) + (HEIGHT / 2);
	if (ray->wall.start < 0)
		ray->wall.start = 0;
	ray->wall.end = (ray->wall.height / 2) + (HEIGHT / 2);
	if (ray->wall.end >= HEIGHT)
		ray->wall.end = HEIGHT - 1;
}

/*
*** /--------------------------------------------------------------------------\
*** |                _____________ Raycasting _____________                    |
*** |                This function will peform a raycasting                    |
*** |                through the whole width of the screen                     |
*** \--------------------------------------------------------------------------/
*/


void			raycasting(t_map *map, t_env *env)
{ 
	int			x;

	x = 0;
	while (x < WIDTH)
	{
		get_ray_coords(env->ray, map, x, env->player);
		get_coord_distance(env->player, env->ray, map);
		find_wall(env->ray, map);
		get_wall_dist(env->ray, map, env->player);
		get_wall_height(env->ray);
		get_texture_pos(env->ray, env->player);
		draw(x, env->ray, env->texture, env);
		x++;
	}
}
