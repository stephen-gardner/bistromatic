/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:57:20 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/09 00:07:30 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "bistro.h"

static t_bool	load_base(t_calc *calc, char *base)
{
	int		i;
	char	*invalid;

	i = 0;
	while (base[i])
	{
		if (ft_strchr(reserved, base[i++]))
			return (syntax_error());
	}
	num->base = base;
	num->nbase = i;
	return (i > 0);
}

static t_bool	load_raw(t_calc	*calc)
{
	if (!(calc->raw = (char *)ft_memalloc(calc->raw_len + 1)))
		return (FALSE);
	if (read(0, calc->raw, calc->raw_len) < calc->raw_len)
	{
		syntax_error();
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	load_raw_len(t_num *num, char *raw_len)
{
	int		i;

	i = 0;
	while (raw_len[i])
	{
		if (!ft_isdigit(raw_len[i]))
			return (syntax_error());
		num->raw_len = (num->raw_len * 10) + (raw_len[i++] - '0');
	}
	return (i > 0);
}

t_bool			syntax_error(void)
{
	write(2, "syntax error\n", 13);
	return (FALSE);
}

int				main(int ac, char **av)
{
	t_num	*num;

	if (ac < 3
		|| !(num = (t_num *)ft_memalloc(sizeof(t_num)))
		|| !verify_params(num, av[1], av[2])
		|| !read_op(num))
		return (1);
printf("op: %s\nop_len: %d\nbase: %d\nkey: %s\n", num->op, num->op_len, num->base, num->key);
	if (*num->op && *num->op == '-')
	{
		num->sign = -1;
		*num->op += 1;
	}
	else
		num->sign = 1;
	while (*num->op)
		read_digit(num, *num->op++);
	reverse_num(num);
	num = add_num(num, num);
	reverse_num(num);
	t_digit *head = num->head;
	while (head)
	{
		printf("%c", num->key[head->n]);
		head = head->next;
	}
	printf("\n");
	UNUSED(reverse_num);
	return (0);
}
