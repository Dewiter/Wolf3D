/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolevy <rolevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 02:56:05 by rolevy            #+#    #+#             */
/*   Updated: 2018/07/26 06:22:49 by rolevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"


void		gen_surface(t_env *env)
{
	env->texture->srf = IMG_Load("./assets/textures/eagle.png");
	env->render->srf = SDL_GetWindowSurface(env->win);
	printf("%p\n", env->render->srf);
}
