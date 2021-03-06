/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:57:20 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/14 18:28:47 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "bistro.h"

static t_bool	load_base(t_calc *calc, char *base)
{
	int		i;
	char	*invalid;

	invalid = "()+-/*";
	i = 0;
	while (base[i])
	{
		if (ft_strchr(invalid, base[i])
			|| ft_strchr(&base[i + 1], base[i]))
			return (syntax_error());
		i++;
	}
	calc->base = base;
	if ((calc->nbase = i) < 2)
		return (syntax_error());
	return (TRUE);
}

static t_bool	load_raw(t_calc *calc)
{
	if (!(calc->raw = (char *)ft_memalloc(calc->raw_len + 1)))
		return (FALSE);
	if (read(0, calc->raw, calc->raw_len) < 0)
		return (FALSE);
	calc->pos = calc->raw;
	return (TRUE);
}

static t_bool	load_raw_len(t_calc *calc, char *raw_len)
{
	int		i;

	i = 0;
	while (raw_len[i])
	{
		if (!ft_isdigit(raw_len[i]))
			return (syntax_error());
		calc->raw_len = (calc->raw_len * 10) + (raw_len[i++] - '0');
	}
	return (i > 0);
}

t_bool			syntax_error(void)
{
	write(2, "syntax error", 12);
	return (FALSE);
}

int				main(int ac, char **av)
{
	t_calc	calc;

	if (ac < 3
		|| !load_base(&calc, av[1])
		|| !load_raw_len(&calc, av[2])
		|| !load_raw(&calc))
		return (1);
	fsm_run(&calc);
	return (0);
}
