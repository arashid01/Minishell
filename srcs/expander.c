/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 03:43:43 by amal              #+#    #+#             */
/*   Updated: 2025/05/07 20:06:29 by nora             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	**copy_env(char **envp)
{
	int	count;
	int	i;
	char	**envp_copy;

	if (!envp)
		return(NULL);
	count = 0;
	while(envp[count])
		count++;
	envp_copy = malloc(sizeof(char *)*(count + 1));
	if (!envp_copy)
	{
		perror("minishell: copy_env: malloc failed");
		return (NULL);
	}
	i = 0;
	while(i < count)
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (!envp_copy[i])
		{
			while(i > 0)
			{
				i--;
				free(envp_copy[i]);
			}
			free(envp_copy);
			perror("minishell: copy_env: malloc failed");
			return (NULL);
		}
		i++;
	}
	envp_copy[count] = NULL;
	return (envp_copy);
}

void	free_env(char	**envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int ft_setenv(const char *name, const char *value, t_shell *shell)
{
	size_t	name_len;
	int	i;
	int	j;
	char *new_str;
	char **new_envp;
	
    if (!name || !value || !shell || !shell->envp || ft_strchr(name, '=') != NULL)
	{
		if (name && ft_strchr(name, '=') != NULL)
            write(2, "minishell: export: variable name cannot contain '=':\n", 53);
		else
            write(2, "minishell: setenv: invalid input\n", 33);
	}
	name_len = ft_strlen(name);
	i = 0;
	j = 0;
	while (shell->envp[i])
	{
		if (( ft_strncmp(shell->envp[i], name, name_len) == 0) && (shell->envp[i][name_len] == '='))
		{
			new_str = malloc(name_len + ft_strlen(value) + 2);
			if (!new_str)
			{
				perror("minishell: setenv: malloc failed\n");
				return (1);
			}
			ft_strlcpy(new_str, name, name_len + 1);
			new_str[name_len] = '=';
			ft_strlcpy(new_str + name_len + 1, value, ft_strlen(value) + 1);
			free (shell->envp[i]);
			shell->envp[i] = new_str;
			return (0);
		}
		i++;
	}
	new_str = malloc(name_len + ft_strlen(value) + 2);
	if (!new_str)
	{
		perror("minishell: setenv: malloc failed\n");
		return (1);
	}
	ft_strlcpy(new_str, name, name_len + 1);
	new_str[name_len] = '=';
	ft_strlcpy(new_str + name_len + 1, value, ft_strlen(value) + 1);
	while (shell->envp[j])
		j++;
	new_envp = malloc(sizeof(char *) * (j + 2));
	if (!new_envp)
	{
		free(new_str);
		perror("minishell: setenv: malloc failed\n");
		return (1);
	}
	i = 0;
	while (i < j)
	{
		new_envp[i] = shell->envp[i];
		i++;
	}
	new_envp[j] = new_str;
	new_envp[j + 1] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
	return (0);
}

int ft_unsetenv(const char *name, t_shell *shell)
{
	int	i;
	int	j;
	int	found_idx;
	size_t	name_len;
	char	**new_envp;
	
	if (!name || !shell || !shell->envp)
	{
		write(2, "minishell: unsetenv: invalid input\n", 35);
		return (1);
	}
	i = 0;
	j = 0;
	found_idx = -1;
	name_len = ft_strlen(name);
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], name, name_len) == 0 && (shell->envp[i][name_len] == '=' || shell->envp[i][name_len] == '\0'))
		{
			found_idx = i;
			break ;
		}
		i++;
	}
	if (found_idx == -1)
		return (0);
	free(shell->envp[found_idx]);
	new_envp = malloc(sizeof(char *) * i);
	if (!new_envp)
	{
		perror("minishell: unsetenv: malloc failed\n");
		return (1);
	}
	i = 0;
	while (shell->envp[i])
	{
		if (i != found_idx)
		{
			new_envp[j] = shell->envp[i];
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	free(shell->envp);
	shell->envp= new_envp;
	return (0);
}
