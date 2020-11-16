#ifndef PRINTF_H
# define PRINTF_H

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>


typedef struct s_data
{
    const char *fmt;
    va_list    args;
    int        len;
    char       flag[5];
    long int   width;
    long int   precision;
    char       sizes[2];
    char       type;
    char       is_nan;
    char       is_inf;
    char       neg_float;
    size_t     ptr;
    int        p_flag;
    char       *prefix;
}              t_data;

int ft_printf(const char *fmt, ...);
t_data *init(t_data *data, const char *fmt);
int parse(t_data *data);
t_data *init_changing_part(t_data *data);
t_data *parse_type(t_data *data);
t_data *parse_flags(t_data *data);
t_data *parse_width(t_data *data);
t_data *parse_size(t_data *data);
t_data *parse_precision(t_data *data);
void type_string(t_data *data);
void type_char(t_data *data);
void type_pointer(t_data *data);
void type_double(t_data *data);
t_data *type_float(t_data *data);
void type_percent(t_data *data);
int ft_write(const char *str, size_t len);
int ft_repeat(const char c, size_t len);
int dispatcher(t_data *data);
int		pf_max(int a, int b);
void		*pf_memalloc(size_t size);
t_data *display_o(t_data *data, char *str, int len);
intmax_t get_unum(t_data *data);
int get_uwidth(uintmax_t num, unsigned int base);
char				*pf_uitoa(uintmax_t n, unsigned int base, char type, int precision);
int is_nan(long double num);
int is_inf(long double num);
int count_big_f(long double num);
char *big_f(long double num);
long double	pf_atof(char *s);
char *little_f(long double num, int precision, char *big_f);
int			is_str(char *str);
int		block_len_f(char *big_s, t_data *data);
void	pad_block_f(t_data *data, int seg);
void    write_f(t_data *data, char sign, char *big_s, char *little_s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
void	ft_putstr(char const *s);
char	*ft_strnew(size_t size);
void	*ft_memalloc(size_t size);
void	ft_bzero(void *s, size_t n);
size_t	ft_strnlen(const char *s, size_t maxlen);
void	*ft_memchr(const void *s, int c, size_t n);
t_data *type_usage(t_data *data);
int parse_color(t_data *data);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void type_base(t_data *data, int base);
intmax_t get_unum(t_data *data);
int get_uwidth(uintmax_t num, unsigned int base);
char				*pf_uitoa(uintmax_t n, unsigned int base, char type, int precision);
void    display_base(t_data *data, char *str, int len);
void    parser(t_data *data);
void    padding(t_data *data, int len);
int			ft_putstr_all(char *s, int color);
#endif