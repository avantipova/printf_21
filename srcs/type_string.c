#include "printf.h"

void type_string(t_data *data)
{
    char *str;
    int len;
    char *str1;

    str1 = "(null)";
    len = 0;
    str = va_arg(data->args, char *);
    if(data->precision > 0 && str)
        str = ft_strndup(str, data->precision);
    else if (data->precision == 0 && data->p_flag == 1)
       str = ft_strdup("");
    else if (!str)
    {
        str = str1;
        if (data->precision)
            str = ft_strndup(str, data->precision);
    }
    len = ft_strlen(str);
    data->len += len;
    padding(data, len);
    ft_putstr(str);
    if (data->flag[2] == '-' && data->width > len)
        data->len += ft_repeat(' ', data->width - len);
}
