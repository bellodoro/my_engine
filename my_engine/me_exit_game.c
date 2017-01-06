/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_exit_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 15:35:26 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/03 10:58:01 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include "my_engine.h"

static void	free_list(t_list *list)
{
	t_list	*next;

	if (!list)
		return ;
	next = list->next;
	if (list->content)
		free(list->content);
	free(list);
	free_list(next);
}

int			me_exit_game(t_me_engine *engine)
{
	free_list(engine->events.key_pressed);
	mlx_destroy_image(engine->mlx.mlx, engine->mlx.img.img);
	mlx_destroy_window(engine->mlx.mlx, engine->mlx.win);
	exit(0);
	return (0);
}
