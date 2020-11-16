/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeirdre <ldeirdre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 15:18:07 by ldeirdre          #+#    #+#             */
/*   Updated: 2020/11/10 22:56:17 by ldeirdre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void type_percent(t_data *data)
{
    int		count;
	char	p;

	p = (data->flag[1] ? '0' : ' ');
	count = 0;
	if (data->flag[2] == 0 && data->width > 1)
		data-> len += ft_repeat(p, data->width - 1);
	data->len += ft_write("%", 1);
	if (data->flag[2] != 0 && data->width > 1)
		data->len += ft_repeat(' ', data->width - 1);
}

t_data *type_usage(t_data *data)
{
    char *str;

    str = "%[flags][width][.precision][length]type";
    ft_putstr(str);
    return (data);
}

void type_base(t_data *data, int base)
{
    int size;
    char *str;
    uintmax_t num;

    size = 0;
    
    if (data->flag[0] && base != 16)
        size = 1;
    if (data->flag[0] && base == 16)
        size = 2;
    num = get_unum(data);
    if (data->precision)
        data->flag[1] = '\0';
    if ((data->precision == -1 && num == 0))
        str = NULL;
    else
        str = pf_uitoa(num, base, data->type, pf_max(data->precision, data->flag[1] && !data->flag[2] ? data->width - size : 0));
    if (base == 16 && num == 0 && data->flag[0])
        *str = '0';
    display_base(data, str, ft_strlen(str));
}

int dispatcher(t_data *data)
{
    char type;

    type = data->type;
    if (type == 'c')
        type_char(data);
    else if (type == 'd' || type == 'i')
        type_double(data);
    else if (type == 'p')
        type_pointer(data);
    else if (type == 's')
        type_string(data);
    else if (type == 'o')
        type_base(data, 8);
    else if (type == 'u')
        type_base(data, 10);
    else if (type == 'x' || type == 'X')
        type_base(data, 16);
    else if (type == 'f')
        type_float(data);
    else if (type == 'b')
        type_base(data, 2);
    else if (type == '%')
        type_percent(data);
    else if (type == 'q')
        type_usage(data);
    else
        return (1);
    return(0);
}