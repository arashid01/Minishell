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