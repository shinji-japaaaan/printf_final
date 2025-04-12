#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

size_t        ft_strlen(const char *str)
{
        size_t        length;

        length = 0;
        while (*str != '\0')
        {
                length++;
                str++;
        }
        return (length);
}


void        ft_putstr_fd(char *s, int fd)
{
        if (s == NULL)
                return ;
        while (*s)
        {
                write(fd, s, 1);
                s++;
        }
}


int        ft_prints(char *s)
{
        if (!s)
                return (write(1, "(null)", 6));
        ft_putstr_fd(s, 1);
        return (ft_strlen(s));
}

int        ft_printc(int c)
{
        int        n;

        n = write(1, &c, 1);
        if (0 <= n)
                return (1);
        else
                return (-1);
}

static char        *ft_num_0(void)
{
        char        *str;

        str = (char *)malloc(2 * sizeof(char));
        if (str == NULL)
                return (NULL);
        str[0] = '0';
        str[1] = '\0';
        return (str);
}

static char        *ft_itoa_convert(int num_digits, long long num)
{
        char        *str;

        str = (char *)malloc((num_digits + 1) * sizeof(char));
        if (str == NULL)
                return (NULL);
        str[num_digits] = '\0';
        if (num < 0)
        {
                str[0] = '-';
                num = num * -1;
        }
        while (num != 0)
        {
                str[num_digits - 1] = '0' + (num % 10);
                num = num / 10;
                num_digits--;
        }
        return (str);
}

char        *ft_itoa(int num)
{
        int                                num_digits;
        long long                temp;

        if (num == 0)
                return (ft_num_0());
        num_digits = 0;
        if (num < 0)
                num_digits = 1;
        temp = num;
        while (temp != 0)
        {
                temp = temp / 10;
                num_digits++;
        }
        return (ft_itoa_convert(num_digits, (long long)num));
}


int        ft_printdi(int nbr)
{
        int                printed_chars;
        char        *str;

        str = ft_itoa(nbr);
        if (!str)
                return (-1);
        printed_chars = ft_prints(str);
        free(str);
        return (printed_chars);
}

static int        ft_get_digit_count(unsigned int n)
{
        int        count;

        count = 1;
        while (n / 10 != 0)
        {
                n /= 10;
                count++;
        }
        return (count);
}


char        *ft_uitoa(unsigned int num)
{
        char        *str;
        int                len;
        long        num_copy;

        num_copy = num;
        len = ft_get_digit_count(num_copy);
        str = (char *)malloc(sizeof(char) * (len + 1));
        if (!str)
                return (NULL);
        str[len] = '\0';
        while (len > 0)
        {
                str[len - 1] = (num_copy % 10) + '0';
                num_copy /= 10;
                len--;
        }
        return (str);
}

int        ft_printu(unsigned int u)
{
        int                printed_chars;
        char        *str;

        str = ft_uitoa(u);
        if (!str)
                return (-1);
        printed_chars = ft_prints(str);
        free(str);
        return (printed_chars);
}

static int        ft_get_digit_count_hex(unsigned int n)
{
        int        count;

        count = 1;
        while (n / 16 != 0)
        {
                count++;
                n /= 16;
        }
        return (count);
}


char        *ft_uitoa_hex(unsigned int num, char format)
{
        char                        *hex_str;
        char                        *hex_digits;
        int                                len;
        unsigned int        num_copy;

        if (format == 'x')
                hex_digits = "0123456789abcdef";
        else
                hex_digits = "0123456789ABCDEF";
        num_copy = num;
        len = ft_get_digit_count_hex(num_copy);
        hex_str = (char *)malloc(sizeof(char) * (len + 1));
        if (!hex_str)
                return (NULL);
        hex_str[len] = '\0';
        while (len > 0)
        {
                hex_str[len - 1] = hex_digits[num_copy % 16];
                num_copy /= 16;
                len--;
        }
        return (hex_str);
}

int        ft_printx(unsigned int x, char format)
{
        int                printed_chars;
        char        *hex_str;

        hex_str = ft_uitoa_hex(x, format);
        if (!hex_str)
                return (-1);
        printed_chars = ft_prints(hex_str);
        free(hex_str);
        return (printed_chars);
}

static int ft_get_digit_count_hex_p(unsigned long long n)
{
    int count;

    count = 1;
    while (n / 16 != 0)
    {
        count++;
        n /= 16;
    }
    return (count);
}


char *ft_uitoa_hex_p(unsigned long long num)
{
    char                *hex_str;
    char                *hex_digits;
    int                 len;
    unsigned long long  num_copy;

    hex_digits = "0123456789abcdef";
    num_copy = num;
    len = ft_get_digit_count_hex_p(num_copy);
    hex_str = (char *)malloc(sizeof(char) * (len + 1));
    if (!hex_str)
        return (NULL);
    hex_str[len] = '\0';
    while (len > 0)
    {
        hex_str[len - 1] = hex_digits[num_copy % 16];
        num_copy /= 16;
        len--;
    }
    return (hex_str);
}


int        ft_printp(unsigned long long p)
{
        int                printed_chars;
        char        *hex_str;

        if (p == 0)
                return (write(1, "(nil)", 5));
        printed_chars = write(1, "0x", 2);
        hex_str = ft_uitoa_hex_p(p);
        if (!hex_str)
                return (-1);
        printed_chars += ft_prints(hex_str);
        free(hex_str);
        return (printed_chars);
}


int        ft_format(char format, va_list args)
{
        int        printed_chars;

        printed_chars = 0;
        if (format == 'c')
                printed_chars = ft_printc(va_arg(args, int));
        else if (format == 's')
                printed_chars = ft_prints(va_arg(args, char *));
        else if (format == 'd' || format == 'i')
                printed_chars = ft_printdi(va_arg(args, int));
        else if (format == 'u')
                printed_chars = ft_printu(va_arg(args, unsigned int));
        else if (format == 'x' || format == 'X')
                printed_chars = ft_printx(va_arg(args, unsigned int), format);
        else if (format == 'p')
                printed_chars = ft_printp(va_arg(args, unsigned long long));
        else if (format == '%')
                printed_chars = ft_printc('%');
        if (printed_chars == -1)
                return (-1);
        return (printed_chars);
}

int        is_invalid_format_specifier(char c)
{
        if (c == 'd' || c == 's' || c == 'c' || c == 'x' || c == 'X' || c == 'p'
                || c == '%' || c == 'i' || c == 'u')
        {
                return (0);
        }
        return (1);
}


int        ft_printf(const char *format, ...)
{
        va_list        args;
        int                printed_chars;
        int                temp;

        va_start(args, format);
        printed_chars = 0;
        while (*format)
        {
                if (*format == '%' && *(++format))
                {
                        if (is_invalid_format_specifier(*format))
                        {
                                va_end(args);
                                return (-1);
                        }
                        temp = ft_format(*format, args);
                }
                else
                        temp = ft_printc(*format);
                if (temp >= 0)
                        printed_chars += temp;
                else
                        return (-1);
                format++;
        }
        va_end(args);
        return (printed_chars);
}
