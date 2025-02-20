
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

int ft_putstr(char *str)
{
	int	i = 0;
	int count = 0;

	if (str == NULL)
		str = "(null)";
	while (str[i] != '\0')
	{
		count += write(1, &str[i], 1);
		i++;
	}
	return (count);
}

int ft_putnbr(int nb)
{
	int count = 0;
	char c;

	if (nb == -2147483648)
	{
		count += ft_putstr("-2147483648");
		return (count);
	}	
	if (nb < 0)
	{
		count += write(1, "-", 1);
		nb *= -1;
	}
	if (nb >= 10)
		count += ft_putnbr(nb / 10);
	c = nb % 10 + '0';
	count += write(1, &c, 1);
	return (count);
}


int ft_puthexa(unsigned int nb)
{
	int count = 0;
	char c;
	char *hexa = "0123456789abcdef";

	if (nb >= 16)
		count += ft_puthexa(nb / 16);
	c = hexa[nb % 16];
	count += write(1, &c, 1);
	return (count);
}


int ft_printf(char *format, ...)
{
	va_list args;
	int i = 0;
	int count = 0;

	va_start(args, format);

	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == 's')
				count += ft_putstr(va_arg(args, char *));
			else if (format[i + 1] == 'd')
				count += ft_putnbr(va_arg(args, int));
			else if (format[i + 1] == 'x')
				count += ft_puthexa(va_arg(args, unsigned int));
			else
				count += write(1, &format[i], 1);
			i++;
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}

// int main(void)
// {
// 	printf("%d\n", ft_printf("%x", 2034341));
// 	printf("%d\n", printf("%x", 2034341));
// }