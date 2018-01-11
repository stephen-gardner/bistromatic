/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 21:45:17 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/11 15:10:26 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bistro.h"

t_num	*strip_zeroes(t_num *num)
{
	t_digit	*next;

	while (num->start && num->start->n == 0 && num->start->next)
	{
		next = num->start->next;
		free(num->start);
		num->start = next;
	}
	return (num);
}