/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 03:43:43 by amal              #+#    #+#             */
/*   Updated: 2025/05/21 10:38:31 by nora             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*strjoin_and_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

char	*expand_exit_status(char *str, int exit_status)
{
	char	*res;
	char	*code;
	char	*pos;
	int		len;

	pos = ft_strnstr(str, "$?", ft_strlen(str));
	if (!pos)
		return (ft_strdup(str));
	code = ft_itoa(exit_status);
	if (!code)
		return (NULL);
	len = ft_strlen(str) - 2 + ft_strlen(code);
	res = malloc(len + 1);
	if (!res)
	{
		free(code);
		return (NULL);
	}
	int i = 0;
	while (&str[i] != pos)
	{
		res[i] = str[i];
		i++;
	}
	ft_strlcpy(res + i, code, len + 1 - i);
	i += ft_strlen(code);
	ft_strlcpy(res + i, pos + 2, len + 1 - i);
	free(code);
	return (res);
}

char *expand_var(t_shell *shell, const char *var)
{
    int i;
    int var_len;

    if (!var || !shell || !shell->envp)
	return (NULL);
    i = 0;
	var_len = ft_strlen(var);
    while (shell->envp[i])
    {
        if ((ft_strncmp(shell->envp[i], var, var_len) == 0) 
            && (shell->envp[i][var_len] == '='))
        {
            char *val = ft_strchr(shell->envp[i], '=') + 1;
            return ft_strdup(val);
        }
        i++;
    }
    return (NULL);
}

char *expand_variables(t_shell *shell, char *input, int exit_status)
{
    int i = 0;
    char *result = ft_strdup("");
    char *temp;
    int start;
    char *var_name;

   if (!result)
        return (NULL);
    while (input[i])
    {
        if (input[i] == '\'')
        {
            start = i++;
            while (input[i] && input[i] != '\'')
                i++;
            if (input[i])
                i++;
            temp = ft_substr(input, start, i - start);
            if (!temp)
                return (free(result), NULL);
            result = strjoin_and_free(result, temp);
        }
        else if (input[i] == '"')
        {
            start = ++i;
            while (input[i] && input[i] != '"')
                i++;
            temp = ft_substr(input, start, i - start);
            if (!temp)
                return (free(result), NULL);
            temp = expand_variables(shell, temp, exit_status);
            if (!temp)
                return (free(result), NULL);
            result = strjoin_and_free(result, temp);
            if (input[i])
                i++;
        }
        else if (input[i] == '$')
        {
            i++;
            if (input[i] == '?')
            {
                temp = ft_itoa(exit_status);
                if (!temp)
                    return (free(result), NULL);
                result = strjoin_and_free(result, temp);
                i++;
            }
            else if (input[i] == '{')
            {
                int brace_start = ++i;
                while (input[i] && input[i] != '}')
                    i++;
                if (input[i] == '}')
                {
                    var_name = ft_substr(input, brace_start, i - brace_start);
                    i++;
                }
                else
                {
                    result = strjoin_and_free(result, ft_strdup("${"));
                    continue;
                }
                temp = expand_var(shell, var_name);
                free(var_name);
                if (!temp)
                    temp = ft_strdup("");
                if (!temp)
                    return (free(result), NULL);
                result = strjoin_and_free(result, temp);
            }
            else if (ft_isalpha(input[i]) || input[i] == '_')
            {
                start = i;
                while (ft_isalnum(input[i]) || input[i] == '_')
                    i++;
                var_name = ft_substr(input, start, i - start);
                if (!var_name)
                    return (free(result), NULL);
                temp = expand_var(shell, var_name);
                free(var_name);
                if (!temp)
                    temp = ft_strdup("");
                if (!temp)
                    return (free(result), NULL);
                result = strjoin_and_free(result, temp);
            }
            else
            {
                temp = ft_strdup("$");
                if (!temp)
                    return (free(result), NULL);
                result = strjoin_and_free(result, temp);
            }
        }
        else
        {
            temp = ft_substr(input, i++, 1);
            if (!temp)
                return (free(result), NULL);
            result = strjoin_and_free(result, temp);
        }
    }
    return (result);
}