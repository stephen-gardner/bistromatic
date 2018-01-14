/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 04:02:45 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/13 23:36:37 by sgardner         ###   ########.fr       */
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
  t_state (*function)(t_event *e);
}				t_transition;

/*
** EVENTS:
** ======
** { DIGIT, NULL_TERM, PAREN_LEFT, PAREN_RIGHT, OP_AS, OP_MDM, SYNTAX_ERROR }
**
** STATES:
** ======
** { APPEND, COLLAPSE, CREATE_NUM, PUSH_TOKEN, START, UNARY }
*/

t_transition	trans[NEVENTS][NSTATES] = {
	{ //digit
		fsm_append,
		fsm_error,
		fsm_append,
		fsm_create,
		fsm_create,
		fsm_create
	},
	{ //null
		fsm_eval,
		fsm_eval,
		fsm_eval,
		fsm_error,
		fsm_eval,
		fsm_error
	},
	{ //left paren
		fsm_error,
		fsm_error,
		fsm_error,
		fsm_error,
		fsm_push,
		fsm_push
	},
	{ //right paren
		fsm_collapse,
		fsm_collapse,
		fsm_collapse,
		fsm_error,
		fsm_error,
		fsm_error
	},
	{ //op add sub
		fsm_push,
		fsm_push,
		fsm_push,
		fsm_unary,
		fsm_unary,
		fsm_unary
	},
	{ //op mul div mod
		fsm_push,
		fsm_push,
		fsm_push,
		fsm_error,
		fsm_error,
		fsm_error
	},
	{ //syntax error
		fsm_error,
		fsm_error,
		fsm_error,
		fsm_error,
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

static t_state	get_next_state(t_event *event, t_state *state)
{
	return (trans[*event][*state].function(event));
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
	while ((state = get_next_state(&event,  &state)))
		event = get_event(calc->base, ++(*calc->pos));
}
