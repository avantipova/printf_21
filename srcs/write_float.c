/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeirdre <ldeirdre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 16:09:22 by ldeirdre          #+#    #+#             */
/*   Updated: 2020/11/13 18:39:21 by ldeirdre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int is_nan(long double num)
{
    return(!(num == num));
}

int is_inf(long double num)
{
    if (num == (1.0 / 0.0) || num == (-1.0 / 0.0))
        return (1);
    else
        return (0);
}

int		block_len_f(char *big_s, t_data *data)
{
	int len;

	if (data->is_inf || data->is_nan)
		len = 3;
	else
		len = ft_strlen(big_s) + data->precision;
	if (data->precision > 0 || data->flag[0])
		len += 1;
	if (data->flag[3] || data->flag[4])
		len += 1;
	if (data->neg_float)
		len += 1;
	return (len);
}

void	pad_block_f(t_data *data, int seg)
{
	if (!data->flag[1] && !data->flag[2] && data->width >
		data->len && seg == 1)
		ft_repeat(' ', data->width - data->len);
	else if (!data->flag[1] && data->flag[2] && data->width >
		data->len && seg == 2)
		ft_repeat(' ', data->width - data->len);
	else if (seg == 0)
	{
		if (data->flag[1] && data->width)
			ft_repeat('0', data->width > data->len ? data->width - data->len : 0);
	}
}

void		write_f(t_data *data, char sign, char *big_s, char *little_s)
{
	data->len = block_len_f(big_s, data);
	pad_block_f(data, 1);
	if (data->flag[4] || data->flag[3] || data->neg_float)
		write(1, &sign, 1);
	pad_block_f(data, 0);
	write(1, big_s, ft_strlen(big_s));
	if (data->precision || data->flag[0])
		write(1, ".", 1);
	write(1, little_s, ft_strlen(little_s));
	pad_block_f(data, 2);
}