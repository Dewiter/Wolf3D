/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullscreen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolevy <rolevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 10:36:38 by rolevy            #+#    #+#             */
/*   Updated: 2018/07/26 10:45:32 by rolevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		toggle_fullscreen(t_env *env)
{
	if (env->fullscreen == 0)
	{
		env->h = 1440;
		env->w = 2560;

		SDL_RestoreWindow(env->win);
		SDL_SetWindowSize(env->win, env->w, env->h);
		SDL_SetWindowFullscreen(env->win, SDL_WINDOW_FULLSCREEN_DESKTOP);
		env->fullscreen = 1;
	}
	else
	{
		env->h = 720;
		env->w = 1080;
		SDL_RestoreWindow(env->win);
		SDL_SetWindowSize(env->win, env->w, env->h);
		SDL_SetWindowFullscreen(env->win, 0);
		env->fullscreen = 0;
	}
	return (0);
}