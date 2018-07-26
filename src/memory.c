/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolevy <rolevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 01:23:22 by rolevy            #+#    #+#             */
/*   Updated: 2018/07/25 03:38:57 by rolevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
*** /--------------------------------------------------------------------------\
*** |        _____________ Alloc various variables _____________               |
*** |                   Allocates memory to variables                          |
*** |                                                                          |
*** | --> player 	(env->player)                                              |
*** | --> ray		(env->ray)                                                 |
*** | --> tetxures	(env->textures)                                            |
*** | --> render	(env->render)                                              |
*** \--------------------------------------------------------------------------/
*/

void	alloc_wolf3d(t_env *env)
{
	if (!(env->texture = (t_texture*)malloc(sizeof(t_texture))))
		exit(EXIT_FAILURE);
	if (!(env->render = (t_texture*)malloc(sizeof(t_texture))))
		exit(EXIT_FAILURE);
	if (!(env->player = (t_player *)malloc(sizeof(t_player))))
		exit(EXIT_FAILURE);
	if (!(env->ray = (t_ray *)malloc(sizeof(t_ray))))
		exit(EXIT_FAILURE);
}