/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_eval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 22:05:41 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/14 22:06:11 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bistro.h"

t_state			fsm_collapse(t_calc *calc, t_event *event)
{
	t_token	*token;

	UNUSED(event);
	while ((token = stack_pop(calc->stack)) && token->type != '(')
	{
		if (!enqueue(calc->queue, token))
			return (QUIT);
	}
	if (!token)
		return (QUIT);
	free(token);
	return (COLLAPSE);
}

t_state			fsm_eval(t_calc *calc, t_event *event)
{
	t_token	*token;

	UNUSED(event);
	while ((token = stack_pop(calc->stack)))
	{
		if (!enqueue(calc->queue, token))
			return (QUIT);
	}
	return (QUIT);
}
