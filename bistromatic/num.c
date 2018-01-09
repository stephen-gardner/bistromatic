/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 19:28:25 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/09 00:07:40 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bistro.h"

t_bool	append_digit(t_num *num, int n)
{
	t_digit	**digit;

	digit = &num->head;
	while (*digit)
		digit = &(*digit)->next;
	if (!(*digit = (t_digit *)ft_memalloc(sizeof(t_digit))))
		return (FALSE);
	(*digit)->n = n;
	return (TRUE);
}

void	destroy_num(t_num **num)
{
	t_digit	*digit;
	t_digit	*next;

	digit = (*num)->head;
	while (digit)
	{
		next = digit->next;
		free(digit);
		digit = next;
	}
	free(*num);
	*num = NULL;
}

t_bool	read_digit(t_num *num, char c)
{
	char	*pos;

	if (!(pos = ft_strchr(num->key, c)))
		return (syntax_error());
	return (append_digit(num, pos - num->key));
}

void	reverse_num(t_num *num)
{
	t_digit	*digit;
	t_digit	*prev;
	t_digit	*next;

	digit = num->head;
	prev = NULL;
	while (TRUE)
	{
		next = digit->next;
		digit->next = prev;
		prev = digit;
		if (!next)
			break ;
		digit = next;
	}
	num->head = digit;
}
