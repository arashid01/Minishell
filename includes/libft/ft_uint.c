/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:33:38 by amrashid          #+#    #+#             */
/*   Updated: 2025/04/18 15:05:29 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_uint(unsigned int nb)
{
	unsigned long	num;
	int				len;

	len = 0;
	num = nb;
	if (num >= 10)
		len += ft_uint(num / 10);
	len += ft_putchar((num % 10) + '0');
	return (len);
}
