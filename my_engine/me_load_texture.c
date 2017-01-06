/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_load_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 11:50:27 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/04 14:55:37 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include "my_engine.h"

void	me_load_texture(char *name, int id, char *filename, t_me_engine *engine)
{
	t_me_texture	*texture;
	t_list			*list;

	texture = (t_me_texture*)malloc(sizeof(t_me_texture));
	texture->name = ft_strdup(name);
	texture->id = id;
	texture->img = mlx_xpm_file_to_image(engine->mlx.mlx, filename,
			&texture->size.x, &texture->size.y);
	texture->pixel = (int*)mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->sl, &texture->endian);
	list = ft_lstnew(0, sizeof(t_me_texture));
	list->content = (void*)texture;
	ft_lstadd(&engine->textures, list);
}
