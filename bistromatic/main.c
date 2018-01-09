/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:57:20 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/08 16:42:01 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "bistro.h"
#include <stdio.h>
static t_bool	add_digit(t_num *num, char c)
{
	t_digit	**digit;
	char	*pos;

	if (!(pos = ft_strchr(num->key, c)))
		return (syntax_error());
	digit = &num->head;
	while (*digit)
		digit = &(*digit)->next;
	if (!(*digit = (t_digit *)ft_memalloc(sizeof(t_digit))))
		return (FALSE);
	(*digit)->n = pos - num->key;
	return (TRUE);
}

static t_bool	read_op(t_num *num)
{
	if (!(num->op = (char *)ft_memalloc(num->op_len + 1)))
		return (FALSE);
	if (read(0, num->op, num->op_len) < num->op_len)
	{
		syntax_error();
		return (FALSE);
	}
	return (TRUE);
}

static void		reverse_num(t_num *num)
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

static t_bool	verify_params(t_num *num, char *base, char *size)
{
	int	i;

	if (!*base)
		return (syntax_error());
	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || base[i] == '*'
			|| base[i] == '/' || base[i] == '%')
			return (syntax_error());
		i++;
	}
	num->key = base;
	num->base = ft_strlen(base);
	i = 0;
	while (size[i])
	{
		if (!ft_isdigit(size[i]))
			return (syntax_error());
		num->op_len = (num->op_len * 10) + (size[i] - '0');
		i++;
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
	while (*num->op)
		add_digit(num, *num->op++);
	reverse_num(num);
	t_digit *head = num->head;
	while (head)
	{
		printf("%d", head->n);
		head = head->next;
	}
	printf("\n");
	UNUSED(reverse_num);
	return (0);
}
