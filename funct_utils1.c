/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_putstr.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbendidi <mbendidi@student.42lausanne.c	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/10/10 18:34:58 by mbendidi		  #+#	#+#			 */
/*   Updated: 2024/10/10 18:34:58 by mbendidi		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	if ((write(1, &c, 1)) == -1)
		return (-1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	count;
	int	i;

	if (!str)
		return (ft_putstr("(null)"));
	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_putchar(((int)str[i]) == -1))
			return (-1);
		count++;
		i++;
	}
	return (count);
}

int	ft_putnbr(long n, int base)
{
	int		count;
	char	*symbols;

	symbols = "0123456789abcdef";
	if (n < 0)
	{
		if (ft_putchar('-') == -1)
			return (-1);
		return (ft_putnbr(-n, base) + 1);
	}
	else if (n < base)
		return (ft_putchar(symbols[n]));
	else
	{
		count = ft_putnbr(n / base, base);
		if (count == -1)
			return (-1);
		return (count + ft_putnbr(n % base, base));
	}
}

int	ft_putnbr_base_upper(unsigned long n, int base)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789ABCDEF";
	if (n < (unsigned int)base)
		return (ft_putchar(symbols[n]));
	else
	{
		count += ft_putnbr_base_upper(n / base, base);
		if (count == -1)
			return (-1);
		count += ft_putnbr_base_upper(n % base, base);
	}
	return (count);
}

int	ft_putnbr_unsigned(unsigned long n, int base)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789abcdef";
	if (n < (unsigned long)base)
		return (ft_putchar(symbols[n]));
	else
	{
		count += ft_putnbr_unsigned(n / base, base);
		count += ft_putnbr_unsigned(n % base, base);
	}
	return (count);
}
