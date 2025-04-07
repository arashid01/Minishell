/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:27:41 by amrashid          #+#    #+#             */
/*   Updated: 2024/08/31 21:28:09 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = n;
	if (num < 0)
	{
		ft_putchar_fd(('-'), fd);
		num = -num;
	}
	if (num / 10 != 0)
		ft_putnbr_fd((num / 10), fd);
	ft_putchar_fd((num % 10 + 48), fd);
}
