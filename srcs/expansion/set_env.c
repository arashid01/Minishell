/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:22:48 by amal              #+#    #+#             */
/*   Updated: 2025/05/20 20:23:36 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **copy_env(char **envp)
{
	int count = 0, i = 0;
	char **envp_copy;

	if (!envp)
		return (NULL);
	while (envp[count])
		count++;
	envp_copy = malloc(sizeof(char *) * (count + 1));
	if (!envp_copy)
		return (NULL);
	while (i < count)
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (!envp_copy[i])
		{
			while (--i >= 0)
				free(envp_copy[i]);
			free(envp_copy);
			return (NULL);
		}
		i++;
	}
	envp_copy[count] = NULL;
	return (envp_copy);
}

void free_env(char **envp)
{
	int i = 0;
	if (!envp)
		return;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

int ft_setenv(const char *name, const char *value, t_shell *shell)
{
	size_t name_len;
	int i = 0, j = 0;
	char *new_str, **new_envp;

	if (!name || !value || !shell || !shell->envp || ft_strchr(name, '='))
		return (write(2, "minishell: export: invalid name\n", 33), 1);
	name_len = ft_strlen(name);
	while (shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], name, name_len) && shell->envp[i][name_len] == '=')
		{
			new_str = malloc(name_len + ft_strlen(value) + 2);
			if (!new_str)
				return (1);
			ft_strlcpy(new_str, name, name_len + 1);
			new_str[name_len] = '=';
			ft_strlcpy(new_str + name_len + 1, value, ft_strlen(value) + 1);
			free(shell->envp[i]);
			shell->envp[i] = new_str;
			return (0);
		}
		i++;
	}
	while (shell->envp[j]) j++;
	new_envp = malloc(sizeof(char *) * (j + 2));
	if (!new_envp)
		return (1);
	new_str = malloc(name_len + ft_strlen(value) + 2);
	if (!new_str)
		return (free(new_envp), 1);
	ft_strlcpy(new_str, name, name_len + 1);
	new_str[name_len] = '=';
	ft_strlcpy(new_str + name_len + 1, value, ft_strlen(value) + 1);
	for (i = 0; i < j; i++)
		new_envp[i] = shell->envp[i];
	new_envp[j] = new_str;
	new_envp[j + 1] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
	return (0);
}

int ft_unsetenv(const char *name, t_shell *shell)
{
	int		i;
	int		j;
	int		count;
	char	**new_envp;
	size_t	name_len;

	i = 0;
	j = 0;
	count = 0;
	if (!name || !shell || !shell->envp)
		return (1);
	name_len = ft_strlen(name);
	while (shell->envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * count);
	if (!new_envp)
		return (1);
	while (shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], name, name_len) &&
			shell->envp[i][name_len] == '=')
			free(shell->envp[i]);
		else
			new_envp[j++] = shell->envp[i];
		i++;
	}
	new_envp[j] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
	return (0);
}