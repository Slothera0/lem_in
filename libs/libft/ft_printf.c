/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvoyer <arvoyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:00:37 by arvoyer           #+#    #+#             */
/*   Updated: 2024/01/22 18:54:10 by arvoyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_var(const char *s, va_list tab);
int	ft_putaddr(unsigned long addr);
int	sort_char(const char *s, va_list tab);

int	ft_printf(const char *s, ...)
{
	va_list	tab;
	int		i;
	int		count;
	int		temp;

	if (!s)
		return (-1);
	va_start(tab, s);
	i = -1;
	count = 0;
	while (s[++i])
	{
		temp = sort_char(&s[i], tab);
		if (temp < 0)
			break ;
		count += temp;
		if (s[i] == '%')
			i++;
	}
	va_end(tab);
	if ((size_t)i != ft_strlen(s))
		return (-1);
	return (count);
}

int	sort_char(const char *s, va_list tab)
{
	int	temp;

	if (*s == '%')
		temp = print_var(s, tab);
	else
		temp = ft_putchar(*s);
	return (temp);
}

int	print_var(const char *s, va_list tab)
{
	int	temp;

	if (s[1] == 'c')
		temp = ft_putchar(va_arg(tab, int));
	else if (s[1] == 's')
		temp = ft_putstr(va_arg(tab, char *));
	else if (s[1] == 'p')
		temp = ft_putaddr(va_arg(tab, unsigned long));
	else if (s[1] == 'd')
		temp = ft_putnbr_base(va_arg(tab, int), DEC);
	else if (s[1] == 'i')
		temp = ft_putnbr_base(va_arg(tab, int), DEC);
	else if (s[1] == 'u')
		temp = ft_putnbr_base(va_arg(tab, unsigned int), DEC);
	else if (s[1] == 'x')
		temp = ft_putnbr_base(va_arg(tab, unsigned int), HEX_MIN);
	else if (s[1] == 'X')
		temp = ft_putnbr_base(va_arg(tab, unsigned int), HEX_MAJ);
	else if (s[1] == '%')
		temp = ft_putchar('%');
	else
		temp = ft_putchar(s[1]);
	if (temp < 0)
		return (-1);
	return (temp);
}

int	ft_putaddr(unsigned long addr)
{
	int	temp;

	if (!addr)
		return (ft_putstr("(nil)"));
	temp = ft_putstr("0x");
	if (temp != 2)
		return (-1);
	temp += ft_putnbr_base(addr, HEX_MIN);
	if (temp - 2 < 0)
		return (-1);
	return (temp);
}
