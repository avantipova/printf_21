#include "printf.h"

int ft_write(const char *str, size_t len)
{
    write(1, str, len);
    return (len);
}

int ft_repeat(const char c, size_t len)
{
    size_t i;

    i = 0;
    while (i < len)
    {
        ft_write(&c, 1);
        i++;
    }
    return (i);
}

void type_char(t_data *data)
{
    char c;

    c = va_arg(data->args, int);
    if (!(data->flag[2]) && data->width)
    {
        if (data->flag[1] && data->precision == -1)
            data->len += ft_repeat('0', data->width - 1);
        else
            data->len += ft_repeat(' ', data->width - 1);
    }
    data->len += ft_write((char *)&c, 1);
    if (data->flag[2] == '-' && data->width > 1)
        data->len += ft_repeat(' ', data->width - 1);
}