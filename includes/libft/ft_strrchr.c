/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:02:49 by amrashid          #+#    #+#             */
/*   Updated: 2024/09/23 16:35:26 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			last = ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	else
		return (last);
}
