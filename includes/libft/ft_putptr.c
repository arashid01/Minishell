/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:34:17 by amrashid          #+#    #+#             */
/*   Updated: 2025/04/18 15:05:14 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(void *ptr)
{
	unsigned long	address;
	int				length;

	length = 0;
	address = (unsigned long)ptr;
	if (address == 0)
		return (ft_putstr("(nil)"));
	else
		length += ft_putstr("0x");
	length += ft_puthex(address, 0);
	return (length);
}
