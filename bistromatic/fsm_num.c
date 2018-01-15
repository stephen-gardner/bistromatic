/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 21:50:21 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/14 21:50:46 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

t_state			fsm_append(t_calc *calc, t_event *event)
{
	t_token	*token;

	if (!(token = peek_end(calc->queue)))
		return (fsm_error(calc, event));
	if (!read_digit(calc, token->content))
		return (QUIT);
	return (APPEND_NUM);
}

t_state			fsm_create(t_calc *calc, t_event *event)
{
	t_token	*token;

	UNUSED(event);
	if (!(token = (t_token *)ft_memalloc(sizeof(t_token)))
		|| !(token->content = (t_num *)ft_memalloc(sizeof(t_num)))
		|| !read_digit(calc, token->content)
		|| !enqueue(calc->queue, token))
		return (QUIT);
	token->type = 'd';
	return (CREATE_NUM);
}
