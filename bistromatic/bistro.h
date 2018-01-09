/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bistro.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:49:48 by sgardner          #+#    #+#             */
/*   Updated: 2018/01/08 16:32:24 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BISTRO_H
# define BISTRO_H
# include "libft.h"

typedef struct	s_digit
{
	int				remain;
	int				n;
	struct s_digit	*next;
}				t_digit;

typedef struct	s_num
{
	t_digit	*head;
	char	*op;
	char	*key;
	int		op_len;
	int		base;
}				t_num;

t_bool			syntax_error(void);
#endif
