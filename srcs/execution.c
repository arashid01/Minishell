/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:23:25 by amal              #+#    #+#             */
/*   Updated: 2025/04/22 17:12:33 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*find_path(char **envp)
{
	while (*envp)
	{
		if ((ft_strncmp(*envp, "PATH=", 5) == 0))
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*build_path(char *dir, char *cmd)
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

void	execute_command_recursive(t_cmd *cmd, char **envp, int in_fd)
{
	int		fds[2];
	pid_t	pid;

	if (!cmd)
		return;
	if (cmd->next && pipe(fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		dup2(in_fd, STDIN_FILENO);
		if (cmd->next)
		{
			dup2(fds[1], STDOUT_FILENO);
			close(fds[0]);
			close(fds[1]);
		}
		close(in_fd);
		execve(find_exe(cmd->argv[0], envp), cmd->argv, envp);
		perror("execve");
		exit(1);
	} 
	else
		close(in_fd);
	if (cmd->next)
	{
		close(fds[1]);
		execute_command_recursive(cmd->next, envp, fds[0]);
		close(fds[0]);
	} 
	else
		waitpid(pid, NULL, 0);
}

void	execute_pipeline_recursive(t_cmd *cmd_list, char **envp)
{
	int		fds[2];
	pid_t	pid;
	
	if (!cmd_list)
		return;
	if (cmd_list->next && pipe(fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (cmd_list->next)
		{
			dup2(fds[1], STDOUT_FILENO);
			close(fds[0]);
			close(fds[1]);
		}
		execve(find_exe(cmd_list->argv[0], envp), cmd_list->argv, envp);
		perror("execve");
		exit(1);
	}
	else
	{
		if (cmd_list->next) {
			close(fds[1]);
			execute_command_recursive(cmd_list->next, envp, fds[0]);
			close(fds[0]);
		}
		else
			waitpid(pid, NULL, 0);
	}
	if (!cmd_list->next)
		while (wait(NULL) > 0);
}
