/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 04:02:45 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/14 22:16:24 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bistro.h"

/*
** STATES:
** ======
** { APPEND_NUM, COLLAPSE, CREATE_NUM, PUSH_TOKEN, QUIT, START, UNARY }
**
** EVENTS:
** ======
** { DIGIT, NULL_TERM, PAREN_LEFT, PAREN_RIGHT, OP_AS, OP_MDM, SYNTAX_ERROR }
*/

t_state	(*g_trans[NSTATES][NEVENTS])(t_calc *calc, t_event *event) = {
	{
		fsm_append,
		fsm_eval,
		fsm_push,
		fsm_error,
		fsm_push,
		fsm_push,
		fsm_error
	},
	{
		fsm_error,
		fsm_eval,
		fsm_error,
		fsm_collapse,
		fsm_push,
		fsm_push,
		fsm_error
	},
	{
		fsm_append,
		fsm_eval,
		fsm_error,
		fsm_collapse,
		fsm_push,
		fsm_push,
		fsm_error
	},
	{
		fsm_create,
		fsm_error,
		fsm_push,
		fsm_error,
		fsm_unary,
		fsm_error,
		fsm_error
	},
	{
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
	},
	{
		fsm_create,
		fsm_eval,
		fsm_push,
		fsm_error,
		fsm_unary,
		fsm_error,
		fsm_error
	},
	{
		fsm_create,
		fsm_error,
		fsm_push,
		fsm_error,
		fsm_unary,
		fsm_error,
		fsm_error
	}
};

static t_event	get_event(char *base, char c)
{
	if (!c)
		return (NULL_TERM);
	else if (ft_strchr(base, c))
		return (DIGIT);
	else if (c == '(')
		return (PAREN_LEFT);
	else if (c == ')')
		return (PAREN_RIGHT);
	else if (c == '+' || c == '-')
		return (OP_AS);
	else if (c == '*' || c == '/' || c == '%')
		return (OP_MDM);
	else
		return (SYNTAX_ERROR);
}

t_state			fsm_error(t_calc *calc, t_event *event)
{
	UNUSED(calc);
	UNUSED(event);
	syntax_error();
	return (QUIT);
}

void			fsm_run(t_calc *calc)
{
	t_state	state;
	t_event	event;

	if (!(calc->stack = stack_init())
		|| !(calc->queue = queue_init()))
		return ;
	state = START;
	while (state != QUIT)
	{
		event = get_event(calc->base, *calc->pos);
		state = g_trans[state][event](calc, &event);
		calc->pos++;
	}
}

t_state			fsm_unary(t_calc *calc, t_event *event)
{
	t_token	*token;
	int		sign;

	UNUSED(event);
	token = peek_end(calc->queue);
	if (!token
		|| token->type != 'd'
		|| (token->type == 'd' && ((t_num *)token->content)->len > 0))
	{
		if (!(token = (t_token *)ft_memalloc(sizeof(t_token)))
			|| !(token->content = (t_num *)ft_memalloc(sizeof(t_num)))
			|| !enqueue(calc->queue, token))
			return (QUIT);
	}
	sign = (*calc->pos == '+') ? 1 : -1;
	((t_num *)token->content)->sign *= sign;
	return (UNARY);
}
