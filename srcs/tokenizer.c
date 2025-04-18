/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:41:48 by amal              #+#    #+#             */
/*   Updated: 2025/04/18 12:39:41 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	save_operator(char *line, int start, int end, t_token **token_list)
{
	t_token	*new;
	t_token	*runner;
	int		len;
	
	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	len = end - start;
	new->val = save_token(&line[start], len);
	new->next = NULL;
	if (ft_strncmp(new->val, ">>", 2) == 0)
		new->type = REDIR_APPEND;
	else if (ft_strncmp(new->val, "<<", 2) == 0)
		new->type = HEREDOC;
	else if (new->val[0] == '>')
		new->type = REDIR_OUT;
	else if (new->val[0] == '<')
		new->type = REDIR_IN;
	else if (new->val[0] == '|')
		new->type = PIPE;
	else
	{
		new->type = -1;
		printf("Unknown operator"); //remove later and handle -1
	}
	if (*token_list == NULL)
		*token_list = new;
	else
	{
		runner = *token_list;
		while (runner->next)
			runner = runner->next;
		runner->next = new;
	}
}

void	save_word(char *line, int start, int end, t_token **token_list)
{
	t_token	*new;
	t_token	*runner;
	int		len;
	
	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	if (line[end - 1] == '\'' || line [end - 1] == '"')
		end--;
	len = end - start;
	new->val = save_token(&line[start], len);
	new->type = WORD;
	new->next = NULL;
	if (*token_list == NULL)
		*token_list = new;
	else
	{
		runner = *token_list;
		while (runner->next)
			runner = runner->next;
		runner->next = new;
	}
}

void	init_status(t_status *status)
{
	status->normal = 1;
	status->s_quote = 0;
	status->d_quote = 0;
}

void	tokenize_line(char *line)
{
	int			i;
	int			start;
	t_status	status;
	t_token		*token_list;

	i = 0;
	token_list = NULL;
	init_status(&status);
	while (line[i])
	{
		if (status.normal == 1 && line[i] == '\'')
		{
			status.normal = 0;
			status.s_quote = 1;
			i++;
			continue;
		}
		else if (status.s_quote == 1 && line[i] == '\'')
		{
			status.normal = 1;
			status.s_quote = 0;
			i++;
			continue;
		}
		else if (status.normal == 1 && line[i] == '"')
		{
			status.normal = 0;
			status.d_quote = 1;
			i++;
			continue;
		}
		if (status.normal == 1 && line[i] == 32)
		{
			i++;
			continue;
		}
		if (status.normal == 1 && is_operator(line[i]))
		{
			start = i;
			if ((line[i] == '>' && line [i + 1] == '>') 
				|| (line[i] == '<' && line [i + 1] == '<'))
				i += 2;
			else
				i++;
			save_operator(line, start, i, &token_list);
			continue;
		}
		start = i;
		while (line[i])
		{
			if (status.normal == 1 && (line[i] == 32 || is_operator(line[i])))
				break;
			if (status.normal == 1 && line[i] == '\'')
			{
				status.normal = 0;
				status.s_quote = 1;
			}
			else if (status.s_quote == 1 && line[i] == '\'')
			{
				status.normal = 1;
				status.s_quote = 0;
			}
			else if (status.normal == 1 && line[i] == '"')
			{
				status.normal = 0;
				status.d_quote = 1;
			}
			else if (status.d_quote == 1 && line[i] == '"')
			{
				status.normal = 1;
				status.d_quote = 0;
			}
				i++;
		}
		save_word(line, start, i, &token_list);
	}
	print_tokens(token_list);
}
