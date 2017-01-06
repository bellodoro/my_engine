/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_get_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 13:59:15 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/03 10:58:37 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

t_me_state	*me_get_state(t_me_engine *engine, char *name)
{
	t_list	*actual_node;

	actual_node = engine->state_list.list;
	while (actual_node)
	{
		if (ft_strcmp(((t_me_state*)actual_node->content)->name, name) == 0)
			return (t_me_state*)actual_node->content;
		actual_node = actual_node->next;
	}
	return (0);
}
