/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 19:28:25 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/10 22:06:20 by sgardner         ###   ########.fr       */
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
	int		i;

	if (!(out = (char *)ft_memalloc(num->len + (num->sign < 0) + 1)))
		return ;
	i = 0;
	digit = skip_zeroes(num->start);
	if (num->sign < 0 && digit && digit->n != 0)
		out[i++] = '-';
	while (digit)
	{
		out[i++] = calc->base[digit->n];
		digit = digit->next;
	}
	write(1, out, i);
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
