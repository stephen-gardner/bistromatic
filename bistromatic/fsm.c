/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 04:02:45 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/14 03:33:59 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_state	(*trans[NSTATES][NEVENTS])(t_calc *calc, t_event *event) = {
	{ // APPEND
		fsm_append,
		fsm_eval,
		fsm_push,
		fsm_error,
		fsm_unary,
		fsm_error,
		fsm_error
	},
	{ // COLLAPSE
		fsm_error,
		fsm_eval,
		fsm_error,
		fsm_collapse,
		fsm_push,
		fsm_push,
		fsm_error
	},
	{ // CREATE_NUM
		fsm_append,
		fsm_eval,
		fsm_error,
		fsm_collapse,
		fsm_push,
		fsm_push,
		fsm_error
	},
	{ // PUSH_TOKEN
		fsm_create,
		fsm_error,
		fsm_push,
		fsm_error,
		fsm_unary,
		fsm_error,
		fsm_error
	},
	{ // QUIT
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
	},
	{ // START
		fsm_create,
		fsm_eval,
		fsm_push,
		fsm_error,
		fsm_unary,
		fsm_error,
		fsm_error
	},
	{ // UNARY
		fsm_create,
		fsm_error,
		fsm_push,
		fsm_error,
		fsm_unary,
		fsm_error,
		fsm_error
	}
};

t_state			fsm_append(t_calc *calc, t_event *event)
{
	UNUSED(calc);
	UNUSED(event);
	return (APPEND_NUM);
}

t_state			fsm_collapse(t_calc *calc, t_event *event)
{
	UNUSED(calc);
	UNUSED(event);
	return (COLLAPSE);
}

t_state			fsm_create(t_calc *calc, t_event *event)
{
	UNUSED(calc);
	UNUSED(event);
	return (CREATE_NUM);
}

t_state			fsm_error(t_calc *calc, t_event *event)
{
	UNUSED(calc);
	UNUSED(event);
	syntax_error();
	return (QUIT);
}

t_state			fsm_eval(t_calc *calc, t_event *event)
{
	UNUSED(calc);
	UNUSED(event);
	return (QUIT);
}

t_state			fsm_push(t_calc *calc, t_event *event)
{
	UNUSED(calc);
	UNUSED(event);
	return (PUSH_TOKEN);
}

t_state			fsm_unary(t_calc *calc, t_event *event)
{
	UNUSED(calc);
	UNUSED(event);
	return (UNARY);
}

static t_event	get_event(char *base, char c)
{
	if (ft_strchr(base, c))
		return (DIGIT);
	else if (c == '\0')
		return (NULL_TERM);
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

void			fsm_run(t_calc *calc)
{
	t_state	state;
	t_event	event;

	if (!(calc->operators = stack_init())
		|| !(calc->operands = queue_init()))
		return ;
	state = START;
	event = get_event(calc->base, *calc->pos);
	while ((state = trans[state][event](calc, &event)))
	{
		if (state == QUIT)
			break ;
		event = get_event(calc->base, ++(*calc->pos));
	}
}
