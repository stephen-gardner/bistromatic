/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 23:54:42 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/13 17:22:36 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*dequeue(t_queue *queue)
{
	void	*content;
	t_node	*next;

	if (!queue->start)
		return (NULL);
	content = queue->start->content;
	if (queue->start == queue->end)
		queue->end = NULL;
	next = queue->start;
	free(queue->start);
	queue->start = next;
	return (content);
}

t_bool	enqueue(t_queue *queue, void *content)
{
	t_node	*new;

	if (!(new = (t_node *)ft_memalloc(sizeof(t_node))))
		return (FALSE);
	new->content = content;
	if (!queue->start)
		queue->start = new;
	if (queue->end)
		queue->end->next = new;
	queue->end = new;
	return (TRUE);
}

t_queue	*queue_init(void)
{
	return ((t_queue *)ft_memalloc(sizeof(t_queue)));
}

int		queue_isempty(t_queue *queue)
{
	return (queue->start == NULL);
}

void	*queue_peek(t_queue *queue)
{
	return ((queue->start) ? queue->start->content : NULL);
}
