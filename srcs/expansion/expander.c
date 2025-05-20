/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 03:43:43 by amal              #+#    #+#             */
/*   Updated: 2025/05/20 20:41:20 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*expand_var(t_shell *shell, const char *var)
{
	int		i;
	int		var_len;
	char	*val;

	if (!var || !shell || !shell->envp)
		return (NULL);
	i = 0;
	var_len = ft_strlen(var);
	while (shell->envp[i])
	{
		if ((ft_strncmp(shell->envp[i], var, var_len) == 0) 
				&& (shell->envp[i][var_len] == '='))
		{
			ft_printf("%s is found\n", var);
			val = ft_strchr(shell->envp[i], '=') + 1;
			ft_printf("%s\n", val);
			return (val);
		}
		else
			i++;
	}
	ft_printf("Var not found\n");
	return (NULL);
}

