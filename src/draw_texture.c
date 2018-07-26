/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolevy <rolevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 14:34:17 by rolevy            #+#    #+#             */
/*   Updated: 2018/07/26 09:05:17 by rolevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
*** /--------------------------------------------------------------------------\
*** |               _____________ Convert to RGBA _____________                |
*** |               Simple convert from interger simple RGBA                   |
*** |                                                                          |
*** | --> In order to convert an int to a rgba we bit shift the value into     |
*** |	  four different integers each represanting red, green, blue or the    |
*** |	  of the color                                                         |
*** \--------------------------------------------------------------------------/
*/

Uint32					get_pixel(int y, SDL_Surface *srf, t_ray *ray)
{
	Uint32	*pixels;
	int		tex_heigth;
	int		delta;
	
	pixels = (Uint32 *)srf->pixels;
	delta = y * 256 - HEIGHT * 128 + ray->wall.height * 128;
	tex_heigth = ((delta * TEXTHEIGHT) / ray->wall.height) / 256;
	printf("texture_height = %d\n", tex_heigth);
	return (pixels[TEXTHEIGHT * tex_heigth + ray->tex_pos]);
}

void				set_pixel(int x, int y, int color, SDL_Surface *srf)
{
	unsigned int	*ptr; 
	int				offset;
	
	offset = y * (srf->pitch / 4);
	ptr = (unsigned int *)(srf->pixels);
	ptr[offset + x] = color;
}

/*
*** /--------------------------------------------------------------------------\
*** |                   _____________ Clear screen _____________               |
*** |                   Covers the screen in black after the                   |
*** |                   user desides to move the player                        |
*** |                                                                          |
*** | --> Go through th hole screen put black pixel by calling ft_putpixel()   |
*** \--------------------------------------------------------------------------/
*/

void				clear_screen(t_env *env)
{
	t_index 		i;
	
	i = (t_index){0, 0};
	SDL_LockSurface(env->render->srf);
	while (i.y < HEIGHT)
	{
		i.x = 0;
		while (i.x < WIDTH)
			set_pixel(i.x++, i.y, 0, env->render->srf);
		i.y++;
	}
	SDL_UnlockSurface(env->render->srf);
}

void				draw(int x, t_ray *ray, t_texture *texture, t_env *env)
{
	int y;
	Uint32 color;
	(void)texture;

	if (SDL_MUSTLOCK(env->render->srf))
		SDL_LockSurface(env->render->srf);
		if (ray->side == 1)
			color = 0x0FF00FFFF/*get_pixel(y, texture->srf, env->ray)*/;
		else
			color = 0x0FFFF00FF;
	y = ray->wall.start;
	while (y < ray->wall.end)
	{
		set_pixel(x, y++, color, env->render->srf);
	}
	if (SDL_MUSTLOCK(env->render->srf))
		SDL_UnlockSurface(env->render->srf);
}