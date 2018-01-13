/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 23:06:44 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/13 01:14:34 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bistro.h"

t_stack	*stack_init(void)
{
	return ((t_stack *)ft_memalloc(sizeof(t_stack)));
}

t_bool	stack_isEmpty(t_stack *stack)
{
	return (stack->top == NULL);
}

void	*stack_peek(t_stack *stack)
{
	return ((stack->top) ? stack->top->content : NULL);
}

void	*stack_pop(t_stack *stack)
{
	void	*content;
	t_node	*next;

	if (!stack->top)
		return (NULL);
	content = stack->top->content;
	next = stack->top->next;
	free(stack->top);
	stack->top = next;
	return (content);
}

t_bool	stack_push(t_stack *stack, void *content)
{
	t_node	*new;

	if (!(new = (t_node *)ft_memalloc(sizeof(t_node))))
		return (FALSE);
	new->content = content;
	new->next = stack->top;
	stack->top = new;
	return (TRUE);
}
