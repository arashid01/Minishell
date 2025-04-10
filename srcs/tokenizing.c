/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:30:43 by amal              #+#    #+#             */
/*   Updated: 2025/04/10 05:32:28 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	count_tokens(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			if ((line[i] == '>' && line[i + 1] == '>')
				|| (line[i] == '<' && line[i + 1] == '<'))
				i += 2;
			else
				i++;
			count++;
		}
		else
		{
			while (line[i] && line[i] != ' ' && !is_operator(line[i]))
				i++;
			count++;
		}
	}
	return (count);
}

char	**tokenize(char *line)
{
	int		i;
	int		j;
	int		start;
	char	**tokens;

	i = 0;
	j = 0;
	tokens = malloc(sizeof(char *) * (count_tokens(line) + 1));
	if (!tokens)
		return (NULL);
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			if ((line[i] == '>' && line[i + 1] == '>') 
				|| (line[i] == '<' && line[i + 1] == '<'))
			{
				tokens[j++] = ft_substr(line, i, 2);
				i += 2;
			}
			else
			{
				tokens[j++] = ft_substr(line, i, 1);
				i++;
			}
		}
		else
		{
			start = i;
			while (line[i] && line[i] != ' ' && !is_operator(line[i]))
				i++;
			tokens[j++] = ft_substr(line, start, i - start);
		}
	}
	tokens[j] = NULL;
	return (tokens);
}

int	get_token_type(char *str)
{
	if (!ft_strncmp(str, "|", 1))
		return (T_PIPE);
	if (!ft_strncmp(str, "<", 1))
		return (T_REDIR_IN);
	if (!ft_strncmp(str, ">", 1))
		return (T_REDIR_OUT);
	if (!ft_strncmp(str, ">>", 2))
		return (T_REDIR_AP);
	if (!ft_strncmp(str, "<<", 2))
		return (T_HEREDOC);
	return (T_WORD);
}

t_token	*build_token_list(char **str_tokens, int count)
{
	t_token	*tokens;
	int		i;

	tokens = malloc(sizeof(t_token) * count);
	if (!tokens)
		return (NULL);
	i = 0;
	while (i < count)
	{
		tokens[i].value = str_tokens[i];
		tokens[i].type = get_token_type(str_tokens[i]);
		i++;
	}
	return (tokens);
}