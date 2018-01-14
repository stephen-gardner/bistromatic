/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 04:02:45 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/14 02:15:36 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

typedef enum
{
	DIGIT,
	NULL_TERM,
    PAREN_LEFT,
	PAREN_RIGHT,
	OP_AS,
	OP_MDM,
	SYNTAX_ERROR,
	NEVENTS
}	t_event;

typedef enum
{
	APPEND_NUM,
	COLLAPSE,
	CREATE_NUM,
	PUSH_TOKEN,
    START,
	UNARY,
	NSTATES
}	t_state;


typedef struct	s_transition
{
  t_state (*function)(t_calc *calc, t_event *event);
}				t_transition;

/*
** STATES:
** ======
** { APPEND, COLLAPSE, CREATE_NUM, PUSH_TOKEN, START, UNARY }
**
** EVENTS:
** ======
** { DIGIT, NULL_TERM, PAREN_LEFT, PAREN_RIGHT, OP_AS, OP_MDM, SYNTAX_ERROR }
*/

t_transition	trans[NSTATES][NEVENTS] = {
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

static t_state	get_next_state(t_calc *calc, t_event *event, t_state *state)
{
	return (trans[*event][*state].function(calc, event));
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
	while ((state = get_next_state(calc, &event,  &state)))
		event = get_event(calc->base, ++(*calc->pos));
}
