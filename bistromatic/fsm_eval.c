/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_eval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 22:05:41 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/14 23:56:40 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bistro.h"

static t_token	*get_result(t_calc *calc, t_token *t1, t_token *t2, char op)
{
	t_token	*res;

	if (!t1 || !t2 || t1->type != 'd' || t2->type != 'd')
	{
		syntax_error();
		return (NULL);
	}
	if (!(res = (t_token *)ft_memalloc(sizeof(t_token))))
		return (NULL);
	res->type = 'd';
	if (op == '+')
		res->content = add(calc, t1->content, t2->content);
	else if (op == '/')
		res->content = divide(calc, t1->content, t2->content);
	else if (op == '%')
		res->content = mod(calc, t1->content, t2->content);
	else if (op == '*')
		res->content = mul(calc, t1->content, t2->content);
	else if (op == '-')
		res->content = sub(calc, t1->content, t2->content);
	else
		syntax_error();
	return (res);
}

static t_num	*solve(t_calc *calc)
{
	t_token	*token;
	t_token	*res;

	while ((token = dequeue(calc->queue)))
	{
		if (token->type == 'd')
			stack_put(calc->stack, token);
		else
		{
			res = get_result(stack_pop(calc->stack), stack_pop(calc->stack))
			if (!res || !res->content || !stack_push(calc->stack, res))
				return (NULL);
			
		}
	}
}

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
