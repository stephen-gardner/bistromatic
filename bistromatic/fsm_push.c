/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 16:33:12 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/14 18:26:38 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

static t_bool	push_op(t_calc *calc, t_token token, char *lower)
{
	t_token *peek;

	while ((peek = stack_peek(calc->stack)) && !ft_strchr(lower, peek->type))
	{
		if (!enqueue(calc->queue, stack_pop(calc->stack)))
			return (FALSE);
	}
	return (stack_push(calc->stack, token));
}

t_state			fsm_push(t_calc *calc, t_event *event)
{
	t_token	*token;

	UNUSED(event);
	if (!(token = (t_token *)ft_memalloc(sizeof(t_token))))
		return (QUIT);
	token->type = *calc->pos;
	if (token->type == '(')
	{
		if (!stack_push(calc->stack, token))
			return (QUIT);
	}
	else if (token->type == '+' || token->type == '-')
	{
		if (!push_op(calc, token, "("))
			return (QUIT);
	}
	else
	{
		if (!push_mdm(calc, token, "(+-"))
			return (QUIT);
	}
	return (PUSH_TOKEN);
}
