#include "printf.h"

static void padding_p(t_data *data, int not_blank)
{
    if (!(data->flag[2]) && data->width > not_blank)
    {
        if (data->flag[1] && data->precision == -1)
            ft_repeat('0', data->width - not_blank);
        else
            ft_repeat(' ', data->width - not_blank);
    }
	write(1, "0x", 2);
}

static void check_p(t_data *data)
{
    if (data->flag[1] == '0' && data->precision == -1)
    {
        data->precision = data->width - 2;
        data->width = 0;
    }
}

void type_pointer(t_data *data)
{
    char *str;
    uintmax_t num;
    int not_blank;
    int width;

    num = (uintmax_t)va_arg(data->args, unsigned long int);
    if (!(str = pf_uitoa(num, 16, 'x', data->precision)))
        exit (-1);
    if (data->precision == 0 && num == 0 && data->p_flag == 1)
        ft_bzero(str, (sizeof(str))); 
    if (data->precision == 0 && num == 0 && data->p_flag == 0)
        *str = '0';
    check_p(data);
    width = ft_strlen(str) + 2;
    not_blank = width;
    if (not_blank <= data->width)
        data->len += data->width;
    else
        data->len += not_blank;
    padding_p(data, not_blank);
	ft_putstr(str);
	if (data->flag[2] == '-' && data->width > not_blank)
		ft_repeat(' ', data->width - not_blank);
	free(str);
}
