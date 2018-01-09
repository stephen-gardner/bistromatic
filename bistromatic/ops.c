/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 19:35:32 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/08 22:26:37 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

t_num	*add_num(t_num *n1, t_num *n2)
{
	t_num	*result;
	t_digit	*d1;
	t_digit	*d2;
	int		tmp;
	int		remain;

	if (!(result = (t_num *)ft_memalloc(sizeof(t_num))))
		return (NULL);
	ft_memcpy(result, n1, sizeof(t_num));
printf("num sign: %d copy sign: %d\n", n1->sign, result->sign);
	result->head = NULL;
	d1 = n1->head;
	d2 = n2->head;
	remain = 0;
	while (d1 || d2)
	{
		tmp = remain * result->sign;
		if (d1)
		{
			tmp += d1->n;
			d1 = d1->next;
		}
		if (d2)
		{
			tmp += d2->n;
			d2 = d2->next;
		}
		remain = (tmp * result->sign >= result->base) ? 1 : 0;
		append_digit(result, tmp * result->sign % n1->base);
if (d1)
	printf("d1: %d ", d1->n);
if (d2)
	printf("d2: %d ", d2->n);
printf("remainder: %d result: %d\n", remain, tmp % n1->base);
	}
	if (remain)
		append_digit(result, remain);
	return (result);
}
