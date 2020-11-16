#include "printf.h"

static intmax_t get_num(t_data *data)
{
    intmax_t num;

    if (ft_strcmp(data->sizes, "ll") == 0)
		num = va_arg(data->args, long long int);
	else if (ft_strcmp(data->sizes, "l") == 0)
        num = va_arg(data->args, long int);
    else if (ft_strcmp(data->sizes, "j") == 0)
        num = va_arg(data->args, intmax_t);
    else if (ft_strcmp(data->sizes, "z") == 0)
        num = va_arg(data->args, size_t);
    else
        num = va_arg(data->args, int);
    if (ft_strcmp(data->sizes, "hh") == 0)
		num = (char)num;
	else if (ft_strcmp(data->sizes, "h") == 0)
		num = (short)num;
    return (num);
}

static int get_width(intmax_t num)
{
    int width;

    width = 1;
    if (num < 0)
        num *= -1;
    while ((num /= 10) > 0)
        width++;
    return (width);
}

static char *itoa_in(int width, char sign, char neg, uintmax_t v)
{
    static char	*dig = "0123456789";
	char		*str;
	int			base;

	base = 10;
	str = ft_memalloc(width + neg + 1);
	if (str == NULL)
		return (NULL);
	if (sign)
		str[0] = sign;
	while (width > 0)
	{
		str[width + neg - 1] = dig[v % base];
		width--;
		v /= base;
	}
	return (str);
}

static char *pf_itoa(t_data *data, intmax_t num, char sign)
{
    char neg; 
    uintmax_t v;
    int width;

    neg = (num < 0 || sign ? 1 : 0);
    width = get_width(num);
    if (width < data->precision)
        width = data->precision;
    if (!(data->flag[2]) && data->flag[1] && width < (int)data->width - neg)
    {
        width = (int)data->width - neg;
        if (data->precision > 0)
            width = data->precision;
        if (get_width(num) > data->precision && data->precision > 0)
            width = get_width(num);
    }
    v = (num < 0 ? -num : num);
    if (num < 0)
        sign  = '-';
    return(itoa_in(width, sign, neg, v));
}

static void display_d(t_data *data, char *str, int len)
{
    int rem;
    int count;

    rem = 0;
    count = 0;
    if (data->precision == 0 && data->p_flag == 1 && *str == '0')
    {
       str = ft_strdup("");
       len = 0;
    }
    padding(data, len);
    ft_putstr(str);
    data->len += ft_strlen(str);
    if (data->flag[2] && data->width > len)
        data->len += ft_repeat(' ', data->width - len);
    if (str)
        free((void *)str);
}

void type_double(t_data *data)
{
    intmax_t num;
    char sign;
    char *str;

    num = get_num(data);
    
    if (data->flag[3] == '+')
        sign = '+';
    else if (data->flag[4] == ' ')
        sign = ' ';
    else
        sign = 0;
    if (data->precision == -1 && num == 0)
        str = NULL;
    else
        str = pf_itoa(data, num, sign);
    display_d(data, str, ft_strlen(str));
}