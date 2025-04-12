/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:53:53 by amrashid          #+#    #+#             */
/*   Updated: 2024/09/23 16:38:47 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	word_count(const char *s, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] != c && s[i] != '\0')
			{
				i++;
			}
		}
		else
			i++;
	}
	return (words);
}

static char	**arrays(char **helper, const char *s, char c)
{
	size_t	i;
	size_t	j;
	int		k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		j = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (i > j)
		{
			helper[k] = ft_substr(s, j, i - j);
			if (helper[k++] == NULL)
			{
				free_split(helper);
				return (NULL);
			}
		}
	}
	helper[k] = NULL;
	return (helper);
}

char	**ft_split(char const *s, char c)
{
	char	**helper;
	int		words;

	if (s == NULL)
		return (NULL);
	words = word_count(s, c);
	helper = malloc(sizeof(char *) * (words + 1));
	if (helper == NULL)
		return (NULL);
	helper = arrays(helper, s, c);
	return (helper);
}
