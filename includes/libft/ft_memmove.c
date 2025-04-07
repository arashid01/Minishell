/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:57:01 by amrashid          #+#    #+#             */
/*   Updated: 2024/08/31 20:57:31 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*ptr_src;
	char		*ptr_dest;

	ptr_src = (char *)src;
	ptr_dest = (char *)dest;
	if (ptr_src == NULL && ptr_dest == NULL)
		return (NULL);
	if (dest < src)
	{
		while (n--)
			*ptr_dest++ = *ptr_src++;
	}
	else
	{
		ptr_dest = ptr_dest + (n - 1);
		ptr_src = ptr_src + (n - 1);
		while (n--)
			*ptr_dest-- = *ptr_src--;
	}
	return (dest);
}
