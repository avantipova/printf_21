/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeirdre <ldeirdre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 15:10:11 by ldeirdre          #+#    #+#             */
/*   Updated: 2020/11/13 18:30:11 by ldeirdre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"


static long double float_handle(t_data *data)
{
   long double num;

   if (ft_strcmp(data->sizes, "L") == 0 || ft_strcmp(data->sizes, "l") == 0)
		num = va_arg(data->args, long double);
   else
      num = (double)va_arg(data->args, double);
      return (num);
}

static void flag_handle(long double num, t_data *data)
{
   if (is_nan (num) || is_inf(num))
   {
      data->flag[0] = 0;
      data->flag[1] = 0;
      data->precision = 0;
      if (is_nan(num))
         {
            data->is_nan = 1;
            data->flag[3] = 0;
         }
      else
      {
         data->is_inf = 1;
         if (num == -(1.0 / 0))
            data->neg_float = 1;
      } 
   }
   if (data->flag[2])
      data->flag[1] = 0;
   if (data->flag[3])
      data->flag[4] = 0;
   if (!data->precision && data->p_flag == 0)
      data->precision = 6;
}

static char sign_handle(long double num, t_data *data)
{
   char sign;

   sign = data->flag[4] ? ' ' : '+';
   if (num < 0)
   {
      sign = '-';
      data->neg_float = 1;
   }
   return (sign);
}

static long double ten_pow(int pow)
{
   long double num;

   num = 1;
   while (pow > 0)
   {
      num = num * 10;
      --pow;
   }
   while (pow < 0)
   {
      num = num / 10;
      ++pow;
   }
   return (num);
}

static long double ft_round(long double num, t_data *data)
{
   long double tmp;
   char *little_s;
   char *big_s;
   
   num = num < 0 ? -num : num;
   tmp = num * ten_pow(data->precision);
   big_s = big_f(tmp);
   little_s = little_f(tmp, data->precision, big_s);
   tmp -= pf_atof(big_s);
   free(big_s);
   if (tmp > 0.5 || (tmp == 0.5 && is_str(big_s)))
		num += 0.5 * ten_pow(-data->precision);
	return (num);
   
}

static void	free_float(t_data *data, char *big_s, char *little_s)
{
	if (!data->is_inf && !data->is_nan)
	{
		free(big_s);
		free(little_s);
	}
}

t_data *type_float(t_data *data)
{
   long double num;
   char sign;
   char *little_s;
   char *big_s;

   num = float_handle(data);
   flag_handle(num, data);
   sign = sign_handle(num, data);
   if (!data->is_nan && !data->is_inf)
   {
      num = ft_round(num, data);
      big_s = big_f(num);
      little_s = little_f(num, data->precision, big_s);
   }
   else
   {
      big_s = data->is_inf ? "inf" : "nan";
      little_s = "";
   }
   write_f(data, sign, big_s, little_s);
   free_float(data, big_s, little_s);
   return (data);
}