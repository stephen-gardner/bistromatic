/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_eval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 22:05:41 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/15 06:53:15 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bistro.h"

static void		destroy_token(t_token *token)
{
	(void)token;
//	if (token->type == 'd')
//		destroy_num(token->content);
//	free(token);
}

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
		res->content = add(calc, t2->content, t1->content);
	else if (op == '/')
		res->content = divide(calc, t2->content, t1->content);
	else if (op == '%')
		res->content = mod(calc, t2->content, t1->content);
	else if (op == '*')
		res->content = mul(calc, t2->content, t1->content);
	else if (op == '-')
		res->content = sub(calc, t2->content, t1->content);
	else
		syntax_error();
	destroy_token(t1);
	destroy_token(t2);
	return (res);
}

static t_num	*solve(t_calc *calc)
{
	t_token	*token;
	t_token	*res;
	t_num	*num;

	while ((token = dequeue(calc->queue)))
	{
		if (token->type == 'd')
		{
			stack_push(calc->stack, token);
		}
		else
		{
			res = get_result(calc, stack_pop(calc->stack),
				stack_pop(calc->stack), token->type);
			if (!res || !res->content || !stack_push(calc->stack, res))
				return (NULL);
			destroy_token(token);
		}
	}
	if (!(token = stack_pop(calc->stack)) || stack_peek(calc->stack))
		return (NULL);
	num = token->content;
	destroy_token(token);
	return (num);
}

t_state			fsm_collapse(t_calc *calc)
{
	t_token	*token;

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

t_state			fsm_eval(t_calc *calc)
{
	t_token	*token;
	t_num	*num;

	while ((token = stack_pop(calc->stack)))
	{
		if (!enqueue(calc->queue, token))
			return (QUIT);
	}
	if ((num = solve(calc)))
		print_num(calc, num);
	return (QUIT);
}
