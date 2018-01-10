/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 19:28:25 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/09 18:44:38 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "bistro.h"

t_bool	append_digit(t_num *num, int n)
{
	t_digit	*digit;

	if (!(digit = (t_digit *)ft_memalloc(sizeof(t_digit))))
		return (FALSE);
	digit->n = n;
	if (!num->start)
		num->start = digit;
	if (num->end)
		num->end->next = digit;
	num->end = digit;
	num->len++;
	return (TRUE);
}

void	destroy_num(t_num **num)
{
	t_digit	*digit;
	t_digit	*next;

	digit = (*num)->start;
	while (digit)
	{
		next = digit->next;
		free(digit);
		digit = next;
	}
	free(*num);
	*num = NULL;
}

void	print_num(t_calc *calc, t_num *num)
{
	char	*out;
	t_digit	*digit;
	int		len;

	len = 0;
	digit = num->start;
	while (digit)
	{
		len++;
		digit = digit->next;
	}
	if (!(out = (char *)ft_memalloc(len + 1)))
		return ;
	len = 0;
	digit = num->start;
	while (digit)
	{
		out[len++] = calc->base[digit->n];
		digit = digit->next;
	}
	write(1, out, len);
	free(out);
}

t_num	*read_num(t_calc *calc, char *raw, int len)
{
	t_num	*num;
	char	*pos;
	int		i;

	if (!(num = (t_num *)ft_memalloc(sizeof(t_num))))
		return (NULL);
	i = 0;
	num->sign = (i < len && raw[i] == '-') ? -1 : 1;
	if (num->sign < 0)
		i++;
	while (i < len)
	{
		if (!(pos = ft_strchr(calc->base, raw[i++])))
		{
			syntax_error();
			return (NULL);
		}
		if (!(append_digit(num, pos - calc->base)))
		{
			free(num);
			return (NULL);
		}
	}
	return (num);
}

void	reverse_num(t_num *num)
{
	t_digit	*digit;
	t_digit	*prev;
	t_digit	*next;

	digit = num->start;
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
	num->start = digit;
}
