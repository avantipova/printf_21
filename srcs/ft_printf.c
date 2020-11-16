#include "printf.h"

void    parser(t_data *data)
{
    parse_flags(data);
    parse_width(data);
    parse_precision(data);
    parse_size(data);
    parse_type(data);
}

int     parse(t_data *data)
{
    int i;

    i = 0;
    if (ft_strcmp((char *)data->fmt, "%") == 0)
        return (0);
    while (data->fmt[data->ptr] != '\0')
    {
        init_changing_part(data);
        if (data->fmt[data->ptr] == '{')
        {
            i = parse_color(data);
            data->ptr += i;
        }
        if (data->fmt[data->ptr] == '%')
        {
            data->ptr++;
            parser(data);
            if (dispatcher(data)) 
                return (0);
        }
        else
        {
            write(1, &data->fmt[data->ptr], 1);
            data->len += 1;
        }
        data->ptr++;
    }
    return (data->len);
}


int ft_printf(const char *fmt, ...)
{
    t_data  *data;

    if (!(data = (t_data*)malloc(sizeof(t_data))))
    {
    //tipa problems memory allocation
        return (0);
    }
    data = init(data, fmt);
    if (fmt)
    {
        va_start(data->args, fmt);
        data->len = parse(data);
        va_end(data->args);
    }
    free(data);
    return(data->len);
}
