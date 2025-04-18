/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:33:15 by amrashid          #+#    #+#             */
/*   Updated: 2025/04/18 15:05:09 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int nb)
{
	long	num;
	int		len;

	num = nb;
	len = 0;
	if (num < 0)
	{
		len++;
		ft_putchar('-');
		num = -num;
	}
	if (num / 10 != 0)
	{
		len += ft_putnbr(num / 10);
	}
	len += ft_putchar(num % 10 + 48);
	return (len);
}
