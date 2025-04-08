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
			if ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i + 1] == '<'))
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
