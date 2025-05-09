/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:03:49 by amal              #+#    #+#             */
/*   Updated: 2025/04/18 18:14:28 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(char c)
{
	return ((c == '|') || (c == '<') || (c == '>'));
}

char	*save_token(char *start, int len)
{
	int		i;
	char	*token;

	i = 0;
	token = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		token[i] = start[i];
		i++;
	}
	token[i] = '\0';
	return (token);
}
void	print_tokens(t_token *token)
{
	while (token)
	{
		printf("A token: [%s] -> %d \n", token->val, token->type);
		token = token->next;
	}
}
