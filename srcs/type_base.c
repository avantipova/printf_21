/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeirdre <ldeirdre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 15:18:34 by ldeirdre          #+#    #+#             */
/*   Updated: 2020/11/13 18:50:58 by ldeirdre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

intmax_t get_unum(t_data *data)
{
    intmax_t num;

    if (ft_strcmp(data->sizes, "ll") == 0)
		num = va_arg(data->args, unsigned long long);
	else if (ft_strcmp(data->sizes, "l") == 0)
        num = va_arg(data->args, unsigned long);
    else if (ft_strcmp(data->sizes, "j") == 0)
        num = va_arg(data->args, uintmax_t);
    else if (ft_strcmp(data->sizes, "z") == 0)
        num = va_arg(data->args, size_t);
    else
        num = va_arg(data->args, unsigned int);
    if (ft_strcmp(data->sizes, "hh") == 0)
		num = (unsigned char)num;
	else if (ft_strcmp(data->sizes, "h") == 0)
		num = (unsigned short)num;
    return (num);
}

int get_uwidth(uintmax_t num, unsigned int base)
{
    int i;

	i = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		i++;
		num /= base;
	}
	return (i);
}

char				*pf_uitoa(uintmax_t n, unsigned int base, char type, int precision)
{
	int		count;
	char		*str;
    char        *dig;

    dig = "0123456789abcdef";
    if (type == 'X')
        dig = "0123456789ABCDEF";
	count = get_uwidth(n, base);
	if (count < precision)
		count = precision;
	str = ft_memalloc(count + 1);
	if (str == NULL)
		return (NULL);
	while (count > 0)
	{
		str[count - 1] = dig[n % base];
		count--;
		n /= base;
	}
	return (str);
}

static int check_prefix(t_data *data, char *str)
{
    if (data->flag[0] && str != NULL)
    {
        if (data->type != 'x' && data->type != 'X')
        {
            data->prefix = "0";
            return (1);
        }
        else if (*str != 0)
        {
            data->prefix ="0x";
            if (data->type == 'X')
                data->prefix = "0X";
            return (2);
        }
    }
    return (0);
}

void    display_base(t_data *data, char *str, int len)
{
    int rem;

    rem = 0;
    rem = check_prefix(data, str);
    if (data->precision == 0 && data->p_flag == 1 && *str == '0')
    {
       str = ft_strdup("");
       len = 0;
    }
	data->width -= rem;
	padding(data, len);
    if ((rem && ft_strcmp(str, "") != 0) || (rem && data->type == 'o'))
		data->len += ft_write(data->prefix, rem);
	data->len += ft_write(str, len);
	if (data->flag[2] && data->width > len)
        data->len += ft_repeat(' ', data->width - len);
    if (str)
        free((void *)str);
}