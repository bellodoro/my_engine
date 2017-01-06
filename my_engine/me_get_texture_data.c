/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_get_texture_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 10:59:01 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/03 10:59:02 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

int		*me_get_texture_data_by_name(char *name, t_me_engine *engine)
{
	t_me_texture	*texture;

	texture = me_get_texture_information_by_name(name, engine);
	if (texture)
		return (int*)(texture->pixel);
	return (0);
}

int		*me_get_texture_data_by_id(int id, t_me_engine *engine)
{
	t_me_texture	*texture;

	texture = me_get_texture_information_by_id(id, engine);
	if (texture)
		return (int*)(texture->pixel);
	return (0);
}
