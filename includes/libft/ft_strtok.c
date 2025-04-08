/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 03:00:11 by amal              #+#    #+#             */
/*   Updated: 2025/04/08 03:53:59 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delimiter)
{
	static char	*next;
	char		*tok_start;

	if (str)
		next = str;
	while (*next && ft_strchr(delimiter, *next))
		next++;
	if (*next == '\0')
		return (NULL);
	tok_start = next;
	while (*next && !ft_strchr(delimiter, *next))
		next++;
	if (*next != '\0')
	{
		*next = '\0';
		next++;
	}
	return (tok_start);
}