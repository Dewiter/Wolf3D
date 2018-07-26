/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolevy <rolevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 17:13:38 by rolevy            #+#    #+#             */
/*   Updated: 2018/07/26 01:42:55 by rolevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
*** /--------------------------------------------------------------------------\
*** |       _____________ Move forward / backward _____________                |
*** |         Moving the player from the input of the user                     |
*** |                                                                          |
*** | --> We increase the player pos(x/y) by the directional vector(x/y) as    |
*** |	  long as it doesn't gets the player out of map                        |
*** | --> Once the values are changed we must call recasting in order to have  |
*** |	  a coherant values with this new rotation                             |
*** \--------------------------------------------------------------------------/
*/

// static inline int	get_time(t_env *env)
// {

// 	env->oldtime = env->curtime;
// 	env->curtime = SDL_GetTicks();
// 	env->fps = (env->curtime - env->oldtime) / 1000.0;
	
// 	return (MOVE_SPEED * env->fps);
// }

int		move_forward(t_env *env)
{
	int check;

	check = 0;
	if (!env->map->tab[(int)(env->player->pos.x + env->ray->dir.x *MOVE_SPEED)]
							[(int)env->player->pos.y])
	{
		env->player->pos.x += env->ray->dir.x *MOVE_SPEED;
		check++;
	}
	if (!env->map->tab[(int)env->player->pos.x]
					[(int)(env->player->pos.y + env->ray->dir.y *MOVE_SPEED)])
	{
		env->player->pos.y += env->ray->dir.y *MOVE_SPEED;
		check++;
	}
	if (check == 2)
	{
		clear_screen(env);
		raycasting(env->map, env);
	}
	return (0);
}

int		move_backward(t_env *env)
{
	if (env->map->tab[(int)(env->player->pos.x - env->ray->dir.x *MOVE_SPEED)]
							[(int)env->player->pos.y] == false)
		env->player->pos.x -= env->ray->dir.x *MOVE_SPEED;
	if (env->map->tab[(int)env->player->pos.x]
		[(int)(env->player->pos.y - env->ray->dir.y *MOVE_SPEED)] == false)
		env->player->pos.y -= env->ray->dir.y *MOVE_SPEED;
	clear_screen(env);
	raycasting(env->map, env);
	return (0);
}

/*
*** /--------------------------------------------------------------------------\
*** |             _____________ Rotate left / right _____________              |
*** |             Rotate the player from the input of the user                 |
*** |                                                                          |
*** | --> In order to rotate the player we must rotate the directional vector  |
*** |	  and the 2D raycaster (env->ray->plane) by                            |
*** | --> Once the values are changed we must call recasting in order to have  |
*** |	  a coherant values with this new rotation                             |
*** \--------------------------------------------------------------------------/
*/

int		move_left(t_env *env)
{
	double old;
	double oldplane;

	old = env->ray->dir.x;
	oldplane = env->ray->plane.x;
	env->ray->dir.x = env->ray->dir.x * cos(ROT_SPEED)
					- env->ray->dir.y * sin(ROT_SPEED);
	env->ray->dir.y = old * sin(ROT_SPEED)
					+ env->ray->dir.y * cos(ROT_SPEED);
	env->ray->plane.x = env->ray->plane.x * cos(ROT_SPEED)
					- env->ray->plane.y * sin(ROT_SPEED);
	env->ray->plane.y = oldplane * sin(ROT_SPEED)
						+ env->ray->plane.y * cos(ROT_SPEED);
	clear_screen(env);
	raycasting(env->map, env);
	return (0);
}

int		move_right(t_env *env)
{
	double old;
	double oldplane;

	old = env->ray->dir.x;
	oldplane = env->ray->plane.x;
	env->ray->dir.x = env->ray->dir.x * cos(-ROT_SPEED)
					- env->ray->dir.y * sin(-ROT_SPEED);
	env->ray->dir.y = old * sin(-ROT_SPEED)
					+ env->ray->dir.y * cos(-ROT_SPEED);
	env->ray->plane.x = env->ray->plane.x * cos(-ROT_SPEED)
					- env->ray->plane.y * sin(-ROT_SPEED);
	env->ray->plane.y = oldplane * sin(-ROT_SPEED)
						+ env->ray->plane.y * cos(-ROT_SPEED);
	clear_screen(env);
	raycasting(env->map, env);
	return (0);
}
