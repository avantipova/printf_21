/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeirdre <ldeirdre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 14:53:22 by ldeirdre          #+#    #+#             */
/*   Updated: 2020/11/13 18:39:35 by ldeirdre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int			is_str(char *str)
{
	return ((str[ft_strlen(str) - 1] - '0') % 2);
}

int count_big_f(long double num)
{
    int count;

    count = 0;
    while (num > 1)
    {
        count++;
        num /= 10;
    }
    if (count > 1)
        return (count);
    else 
        return (1);
}

char *big_f(long double num)
{
    char *s;
    char *ptr;
    int count;
    int i;
    long double tmp;

    count = count_big_f(num);
    if (!(s = (char *)ft_memalloc(count + 1)))
        return (NULL);
    ptr = s;
    while (count)
    {
        i = count - 1;
        tmp = num;
        while (i--)
            tmp /= 10;
        *ptr++ = (int)tmp + '0';
        tmp = (int)tmp;
        while (++i < count - 1)
            tmp *= 10;
        num -= tmp;
        --count;
    }
    return (s);
}

long double	pf_atof(char *s)
{
	long double num;

	num = 0;
	while (*s)
	{
		num *= 10;
		num += (long double)(*s - '0');
		++s;
	}
	return (num);
}


char *little_f(long double num, int precision, char *big_f)
{
    char *s;
    int i;

    i = 0;
    num = num < 0 ? -num : num;
    num -= pf_atof(big_f);
    if (!(s = (char *)ft_memalloc(precision + 1)))
        return (NULL);
    while (i < precision)
    {
        num *= 10;
        s[i++] = (num > 0) ? (int)num + '0' : '0';
        num -= (int)num;
    }
    return (s);
}


