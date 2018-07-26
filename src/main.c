/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolevy <rolevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 22:09:09 by cdivry            #+#    #+#             */
/*   Updated: 2018/07/13 00:27:13 by rolevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int			main(int ac, char **av)
{
	t_env	*env;

	if (ac != 2) 
	{
		ft_putstr_fd("Bad usage", 2);
		exit(EXIT_FAILURE);
	}
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		exit(EXIT_FAILURE);
	init_env(env, av);
	return (0);
}
