/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_add_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhammerc <mhammerc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 13:44:57 by mhammerc          #+#    #+#             */
/*   Updated: 2017/01/04 17:58:27 by mhammerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_engine.h"

void	me_add_state(t_me_engine *engine, t_me_state *state)
{
	t_list		*node;

	node = ft_lstnew(0, sizeof(t_me_state));
	node->content = state;
	ft_lstadd(&engine->state_list.list, node);
}
