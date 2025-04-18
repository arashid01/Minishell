/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:33:26 by amrashid          #+#    #+#             */
/*   Updated: 2025/04/18 15:05:03 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(unsigned long num, int hexcase)
{
	int	length;

	length = 0;
	if (num >= 16)
		length += ft_puthex((num / 16), hexcase);
	if (num % 16 < 10)
		length += ft_putchar('0' + (num % 16));
	else
	{
		if (hexcase)
			length += ft_putchar('A' + (num % 16) - 10);
		else
			length += ft_putchar('a' + (num % 16) - 10);
	}
	return (length);
}
