/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:09:56 by amrashid          #+#    #+#             */
/*   Updated: 2024/08/31 21:10:34 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*arr;

	len = 0;
	i = 0;
	while (s[len] != '\0')
		len++;
	arr = malloc(sizeof(char) * (len + 1));
	if (arr == NULL)
		return (NULL);
	else
	{
		while (s[i] != '\0')
		{
			arr[i] = s[i];
			i++;
		}
		arr[i] = '\0';
	}
	return (arr);
}
