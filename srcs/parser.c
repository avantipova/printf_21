#include "printf.h"

int parse_color(t_data *data)
{
    if (data->fmt[data->ptr] == '{')
    {
        if (ft_strncmp(data->fmt, "{red}", 5) == 0)
		    return (ft_putstr_all("\033[31m", 5));
        else if (ft_strncmp(data->fmt, "{green}", 7) == 0)
		    return (ft_putstr_all("\033[32m", 7));
        else if (ft_strncmp(data->fmt, "{yellow}", 8) == 0)
		    return (ft_putstr_all("\033[33m", 8));
	    else if (ft_strncmp(data->fmt, "{blue}", 6) == 0)
		    return (ft_putstr_all("\033[34m", 6));
	    else if (ft_strncmp(data->fmt, "{purple}", 8) == 0)
		    return (ft_putstr_all("\033[35m", 8));
    }
    return (0); 
}


t_data *parse_type(t_data *data)
{
    char *types;
    size_t i;

    types = "cspdiuoxXfbq%";
    i = 0;
    while (types[i] != '\0')
    {
        if (types[i] == data->fmt[data->ptr])
            data->type = types[i];
        i++;
    }
    return (data);
}

t_data *parse_flags(t_data *data)
{
    char *flags;
    size_t i;

    flags = "#0-+ ";
    i = 0;
    while (flags[i] != '\0')
    {
        while (flags[i] == data->fmt[data->ptr])
        {
            if (data->fmt[data->ptr] == '#' && data->ptr++)
                data->flag[0] = '#';
            if (data->fmt[data->ptr] == '0' && data->ptr++)
                data->flag[1] = '0';
            if (data->fmt[data->ptr] == '-' && data->ptr++)
                data->flag[2] = '-';
            if (data->fmt[data->ptr] == ' ' && data->ptr++)
                data->flag[4] = ' ';
            if (data->fmt[data->ptr] == '+' && data->ptr++)
                data->flag[3] = '+';
        }
        i++;
    }
    if (data->flag[3] == '+')
        data->flag[4] = '\0';
    return (data);
}

t_data *parse_precision(t_data *data)
{
    while (data->fmt[data->ptr] ==  '.')
    {
        data->precision = 0;
        data->ptr++;
        data->p_flag = 1;
    }
    while (data->fmt[data->ptr] >= '0' && data->fmt[data->ptr] <= '9')
    {
        data->precision *= 10;
        data->precision += (data->fmt[data->ptr] - 48);
        data->ptr++;
    }
    if (data->fmt[data->ptr] == '*')
    {
        data->precision = va_arg(data->args, int);
        data->ptr++;
    }
    if (data->precision < 0)
    {
        data->precision = 0;
        data->p_flag = 0;
    }
    return (data);
}

t_data *parse_size(t_data *data)
{
    size_t i;
    size_t j;
    char *sizes;

    i = 0;
    j = 0;
    sizes = "lhLjz";
    while (sizes[i] != '\0')
    {
        while (sizes[i] == data->fmt[data->ptr])
        {
            data->sizes[j] = data->fmt[data->ptr];
            data->sizes[j + 1] = '\0';
            data->ptr++;
            j++;
        }
        i++;
    }
    return (data);
}

t_data *parse_width(t_data *data)
{
    while (data->fmt[data->ptr] >= '0' && data->fmt[data->ptr] <= '9')
    {
        data->width *= 10;
        data->width += (data->fmt[data->ptr] - 48);
        data->ptr++;
    }
    if (data->fmt[data->ptr] == '*')
    {
        data->width = va_arg(data->args, int);
        data->ptr++;
    }
    if (data->width < 0)
    {
        data->width *= -1;
        data->flag[2] = '-';
    }
    return (data);
}