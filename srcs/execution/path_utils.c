/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:55:01 by amal              #+#    #+#             */
/*   Updated: 2025/05/11 23:11:13 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_path(char **envp)
{
	while (*envp)
	{
		if ((ft_strncmp(*envp, "PATH=", 5) == 0))
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

static char	*build_path(char *dir, char *cmd)
{
	char	*temp;
	char	*cmd_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		ft_error("Memory allocation failed");
	cmd_path = ft_strjoin(temp, cmd);
	free(temp);
	if (!cmd_path)
		ft_error("Memory allocation failed");
	return (cmd_path);
}

char	*find_exe(char *cmd, char **envp)
{
	char	**dir;
	char	*path;
	char	*cmd_path;
	int		i;

	path = find_path(envp);
	if (!path)
		ft_error("PATH not found");
	dir = ft_split(path, ':');
	i = 0;
	while (dir[i])
	{
		cmd_path = build_path(dir[i], cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			free_arr(dir);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_arr(dir);
	return (NULL);
}
