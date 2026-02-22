/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvoyer <arvoyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:24:19 by arvoyer           #+#    #+#             */
/*   Updated: 2023/11/24 12:16:46 by arvoyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define DEC "0123456789"
# define HEX_MAJ "0123456789ABCDEF"
# define HEX_MIN "0123456789abcdef"

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>

int	ft_putchar(char c);
int	ft_putnbr_base(long long nbr, char *base);
int	ft_putstr(char *str);
int	ft_printf(const char *s, ...);
int	ft_strlen(const char *str);

#endif