/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_get_texture_information.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 10:59:33 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/03 10:59:37 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

t_me_texture	*me_get_texture_information_by_name(char *name,
		t_me_engine *engine)
{
	t_list	*list;

	list = engine->textures;
	while (list)
	{
		if (ft_strcmp(((t_me_texture*)(list->content))->name, name) == 0)
			return (t_me_texture*)(list->content);
		list = list->next;
	}
	return (0);
}

t_me_texture	*me_get_texture_information_by_id(int id, t_me_engine *engine)
{
	t_list	*list;

	list = engine->textures;
	while (list)
	{
		if (list->content && ((t_me_texture*)(list->content))->id == id)
			return (t_me_texture*)(list->content);
		list = list->next;
	}
	return (t_me_texture*)(engine->textures->content);
}
