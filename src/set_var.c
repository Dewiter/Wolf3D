/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolevy <rolevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 14:21:11 by rolevy            #+#    #+#             */
/*   Updated: 2018/07/26 09:32:29 by rolevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
*** /-------------------------------------------------------------------------\
*** |              _____________ Initial values _____________                 |
*** |		This function is called once at the begining of the game since it |
*** |		sets an initial look directional with the directional vector      |
*** |		and the plane (FOV)                                               |
*** |                                                                         |
*** | --> Setting initial directional vector (ray->dir)                       |
*** | --> Setting 2D raycaster (ray->plane)                                   |
*** \-------------------------------------------------------------------------/
*/

void		init_player_dir(t_ray *ray, t_player *player)
{
	ray->dir = (t_vector){-1, 0};
	ray->plane = (t_vector){0, 0.66};
	player->pos = (t_vector){3, 4};
}

/*
*** /--------------------------------------------------------------------------\
*** |             _____________ Calculate ray coords _____________             |
*** |       This function will called be for every abscisse of the screen      |
*** |                                                                          |
*** | --> Getting cam abscisse within screen (ray->cam)                        |
*** | --> Update current map index (map->index)                                |
*** | --> Get length between current pos and next coord within the screen (x/y)|
*** |	  (Side Distance)                                                      |
*** | --> Get length from current coords (within screen x/y) to the next one   |
*** |	  (Delta)                                                              |
*** \--------------------------------------------------------------------------/
*/

void		get_ray_coords(t_ray *ray, t_map *map, int x, t_player *player)
{
	ray->cam = (2 * (x) / (double)WIDTH - 1);
	ray->val = (t_vector){ray->dir.x + ray->plane.x * (ray->cam),
					ray->dir.y + ray->plane.y * (ray->cam)};
	ray->delta = (t_vector){fabs(1 / ray->val.x),
						fabs(1 / ray->val.y)};
	map->index = (t_index){(int)player->pos.x, (int)player->pos.y};
}

/*
*** /--------------------------------------------------------------------------\
*** |             _____________ Determine x/y distance _____________           |
*** |		This function will determine wether to move on the x axis or       |
*** |		the y axis and calculate the distance between the current player   |
*** |		pos and the current x/y that we check                              |
*** |                                                                          |
*** | --> If the directional vector(x/y) is > 0 then                           |
*** |	  Side Distance(x/y) = (Map->Index(x/y) + 1 - Player(x/y)) * Delta(x/y)|
*** | --> If the directional vector(x/y) is < 0 then                           |
*** |	  Side Distance(x/y) = (Player(x/y) - Map->Index(x/y)) * Delta(x/y)    |
*** | --> The movement on the x/y axis will vary between  1 and -1             |
*** |	  this value is determined by ray->step(x/y) and it changes with       |
*** |	  the sign of the directionnal vector                                  |
*** \--------------------------------------------------------------------------/
*/

t_vector	get_coord_distance(t_player *player, t_ray *ray, t_map *map)
{
	if (ray->val.x < 0)
	{
		ray->step.x = -1;
		ray->coord_dist.x = (player->pos.x - map->index.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->coord_dist.x = (map->index.x + 1.0 - player->pos.x) * ray->delta.x;
	}
	if (ray->val.y < 0)
	{
		ray->step.y = -1;
		ray->coord_dist.y = (player->pos.y - map->index.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->coord_dist.y = (map->index.y + 1.0 - player->pos.y) * ray->delta.y;
	}
	return (ray->coord_dist);
}
