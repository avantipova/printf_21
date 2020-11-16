#include "printf.h"

void    padding(t_data *data, int len)
{
    if (!(data->flag[2]) && data->width > len)
    {
        if (data->flag[1] && data->precision == 0)
            data->len += ft_repeat('0', data->width - len);
        else
            data->len += ft_repeat(' ', data->width - len);
    }
}

int		pf_max(int a, int b)
{
	return (a > b ? a : b);
}

int			ft_putstr_all(char *s, int color)
{
	int i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (color);
}

t_data   *init(t_data *data, const char *fmt)
{
    data->fmt = fmt;
    data->len = 0;
    data->ptr = 0;
    return (data);
}

t_data   *init_changing_part(t_data *data)
{
    data->flag[0] = '\0';
    data->flag[1] = '\0';
    data->flag[2] = '\0';
    data->flag[3] = '\0';
    data->flag[4] = '\0';
    data->width = 0;
    data->sizes[0] = '\0';
    data->sizes[1] = '\0';
    data->precision = 0;
    data->type = '\0';
    data->p_flag = 0;
    return (data);
}