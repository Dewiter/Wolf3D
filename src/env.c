/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolevy <rolevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:43:26 by rolevy            #+#    #+#             */
/*   Updated: 2018/07/26 10:50:50 by rolevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
*** /--------------------------------------------------------------------------\
*** |        _____________ Initiate Wolf3d environnement _____________         |
*** |        This function will initate values for Wolf3D and manage           |
*** |        the SDL main loop                                                 |
*** |                                                                          |
*** | --> Parses the map given as an argument to the programm                  |
*** | --> Create an SDL Window                                                 |
*** | --> Load textures                                                        |
*** | --> Allocated strucures                                                  |
*** | --> Raycast                                                              |
*** | --> Display                                                              |
*** | --> Check for user input                                                 |
*** \--------------------------------------------------------------------------/
*/

void		init_env(t_env *env, char **src)
{
	alloc_wolf3d(env);
	env->loop = false;
	env->w = 1080;
	env->h = 720;
	env->fullscreen = 0;
	SDL_Init(SDL_INIT_VIDEO);
	env->map = gen_map(src[1]);
	env->win = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	env->curtime = 0;
	gen_surface(env);
	init_player_dir(env->ray, env->player);
	while (!env->loop)
	{
		SDL_WaitEvent(&(env->ev));
		raycasting(env->map, env);
		printf("player pos [%f][%f]\n", env->player->pos.x, env->player->pos.y);
		SDL_UpdateWindowSurface(env->win);
		if (SDL_PollEvent(&env->ev))
			if (SDL_KEYUP)
				process_key(env->ev.key.keysym.sym, env);
		if (env->ev.window.event == SDL_WINDOWEVENT_CLOSE
			|| env->ev.window.event == SDLK_ESCAPE)
			env->loop = true;
	}
}
