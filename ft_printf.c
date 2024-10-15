/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_printf.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbendidi <mbendidi@student.42lausanne.c	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/10/10 18:29:38 by mbendidi		  #+#	#+#			 */
/*   Updated: 2024/10/10 18:29:38 by mbendidi		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex(va_list ap)
{
	return (ft_putnbr((unsigned long)(va_arg(ap, unsigned int)), 16));
}

int	print_pointer(va_list ap)
{
	void	*ptr;
	int		ret;
	int		count;

	ptr = va_arg(ap, void *);
	if (!ptr)
		return (ft_putstr("0x0"));
	count = ft_putstr("0x");
	if (count == -1)
		return (-1);
	ret = ft_putnbr_unsigned((unsigned long)ptr, 16);
	if (ret == -1)
		return (-1);
	return (count + ret);
}

int	print_input(char found, va_list ap)
{
	if (found == 'c')
		return (print_char(ap));
	if (found == 's')
		return (print_str(ap));
	if (found == 'd' || found == 'i')
		return (print_int(ap));
	if (found == 'u')
		return (print_unsigned(ap));
	if (found == 'x')
		return (print_hex(ap));
	if (found == 'X')
		return (print_hex_upper(ap));
	if (found == 'p')
		return (print_pointer(ap));
	if (found == '%')
		return (ft_putchar('%'));
	return (write(1, &found, 1));
}

int	handle_format(const char *input, int i, va_list ap)
{
	int	res;

	if (input[i] == '%')
	{
		if (input[i + 1])
		{
			res = print_input(input[i + 1], ap);
			if (res == -1)
				return (-1);
			i++;
		}
		else
			return (-1);
	}
	else
	{
		res = write(1, &input[i], 1);
		if (res == -1)
			return (-1);
	}
	return (res);
}

int	ft_printf(const char *input, ...)
{
	va_list	ap;
	int		count;
	int		res;
	int		i;

	va_start(ap, input);
	count = 0;
	i = 0;
	while (input[i])
	{
		res = handle_format(input, i, ap);
		if (res == -1)
			return (-1);
		count += res;
		i++;
	}
	va_end(ap);
	return (count);
}
