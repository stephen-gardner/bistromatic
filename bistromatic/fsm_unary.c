/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_unary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 05:46:37 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/15 07:01:21 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

t_state	fsm_unary(t_calc *calc)
{
	t_token	*token;
	int		sign;

	token = peek_end(calc->queue);
	if (!token
		|| token->type != 'd'
		|| (token->type == 'd' && ((t_num *)token->content)->len > 0))
	{
		if (!(token = (t_token *)ft_memalloc(sizeof(t_token)))
			|| !(token->content = (t_num *)ft_memalloc(sizeof(t_num)))
			|| !enqueue(calc->queue, token))
			return (QUIT);
		((t_num *)token->content)->sign = 1;
		token->type = 'd';
	}
	sign = (*calc->pos == '+') ? 1 : -1;
	((t_num *)token->content)->sign *= sign;
	return (UNARY);
}

t_state	fsm_unary_paren(t_calc *calc)
{
	t_token	*token;

	token = peek_end(calc->queue);
	if (!append_digit(token->content, 1))
		return (QUIT);
	*calc->pos = '*';
	if (fsm_push(calc) == QUIT)
		return (QUIT);
	*calc->pos = '(';
	return (fsm_push(calc));
}
