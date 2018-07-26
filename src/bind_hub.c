/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_hub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolevy <rolevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:54:45 by rolevy            #+#    #+#             */
/*   Updated: 2018/07/26 10:39:48 by rolevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
*** /--------------------------------------------------------------------------\
*** |             _____________ Get Key Tab _____________                      |
*** |                   Create an Array of t_keys                              |
*** |                                                                          |
*** | --> The array contains for each element                                  |
*** |      ~> A reference to the keyboard input                                |
*** |      ~> An Enumerator                                                    |
*** |      ~> A function pointer                                               |
*** \--------------------------------------------------------------------------/
*/

t_key				*get_key_tab(void)
{
	static t_key	tab[KEY_MAX] =
	{{SDLK_ESCAPE, ESCAPE, quit},
	{SDLK_w, FORWARD, move_forward},
	{SDLK_s, BACKWARD, move_backward},
	{SDLK_a, LEFT, move_left},
	{SDLK_d, RIGHT, move_right},
	{SDLK_TAB, TOGGLE, toggle_fullscreen}};

	return (tab);
}

/*
*** /--------------------------------------------------------------------------\
*** |               _____________ Process Key _____________                    |
*** |                       Simple State machine                               |
*** |                                                                          |
*** | --> Loops in the array created above and compares the input given to     |
*** |	  the function and the current input in the array, if it's a match     |
*** |	  the current function pointer in the array will be called             |
*** | --> Since this function is call in the SDL loop this is called           |
*** |	  every 'frame'                                                        |
	\--------------------------------------------------------------------------/
*/

int					process_key(int input, t_env *env)
{
	int i;

	i = 0;
	while (i < KEY_MAX)
	{
		if (get_key_tab()[i].input == input)
			get_key_tab()[i].function(env);
		i++;
	}
	return (0);
}
