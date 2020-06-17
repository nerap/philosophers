/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_form.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 23:02:31 by racohen           #+#    #+#             */
/*   Updated: 2019/11/11 05:39:35 by racohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

t_format	*ft_setup_form(t_format *form)
{
	if ((form = (t_format*)malloc(sizeof(t_format))) == NULL)
		return (NULL);
	form->type = 'v';
	form->justify = 0;
	form->width = 0;
	form->precision = 0;
	form->o_char = 0;
	form->is_zero = 0;
	form->is_min = 0;
	form->is_dot = 0;
	form->len = 0;
	return (form);
}
