/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:41:48 by amal              #+#    #+#             */
/*   Updated: 2025/04/18 18:22:40 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_status(t_status *status)
{
	status->normal = 1;
	status->s_quote = 0;
	status->d_quote = 0;
}

void	get_tokens(char *line, t_status *status, t_token **token_list)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (status->normal && (line[i] == '\'' || line[i] == '"'))
		{
			handle_quotes(line[i], status);
			i++;
			continue;
		}
		else if (status->normal && line[i] == 32)
		{
			i++;
			continue;
		}
		else if (status->normal && is_operator(line[i]))
		{
			handle_operator(line, &i, token_list);
			continue;
		}
		else
			handle_word(line, &i, status, token_list);
	}
}

void	tokenize_line(char *line)
{
	t_status	status;
	t_token		*token_list;

	token_list = NULL;
	init_status(&status);
	get_tokens(line, &status, &token_list);
	print_tokens(token_list);
}
