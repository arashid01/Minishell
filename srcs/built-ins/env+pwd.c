/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env+pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:58:52 by nora              #+#    #+#             */
/*   Updated: 2025/05/07 20:10:37 by nora             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_env(t_cmd *cmd, t_shell *shell)
{
	int	i;
	
	if (!cmd || !cmd->argv || !shell || !shell->envp)
	{
        write(2, "minishell: env: invalid input or environment\n", 45);
		return (1);
	}
	if (cmd->argv[1] != NULL)
    {
        write(2, "minishell: env: too many arguments\n", 35);
		return (1);
    }
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strchr(shell->envp[i], '=') != NULL)
		{
			write(1, shell->envp[i], ft_strlen(shell->envp[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}
int ft_pwd(t_cmd *cmd, t_shell *shell)
{
	char	buffer[1024];

	(void)shell;
	if (!cmd || !cmd->argv)
	{
		write(2, "minishell: pwd: invalid input\n", 30);
		return (1);
	}
	 if (cmd->argv[1] != NULL)
    {
        write(2, "minishell: pwd: too many arguments\n", 35);
        return (1);
    }
	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		perror("minishell: pwd: getcwd");
		return (1);
	}
	write(1,buffer, ft_strlen(buffer));
	write(1, "\n", 1);
	return (0);
}

int ft_exit(t_cmd *cmd, t_shell *shell)
{
	long long exit_value;
	int	exit_status;
	int	is_numeric;

	if (!cmd || !cmd->argv)
	{
		write(2, "minishell: exit: invalid input\n", 31);
		exit (1);
	}
	write (2, "exit\n", 5);
	if (cmd->argv[1] == NULL)
		exit(shell->exit_status);
	if (cmd->argv[2] != NULL)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		shell->exit_status = 1;
		return (1);
	}
	exit_value = ft_atolli(cmd->argv[1], &is_numeric);
	if (is_numeric == 0)
	{
		exit_status = (exit_value % 256 + 256) % 256;
		exit(exit_status);
	}
	else
	{
		write(2, "minishell: exit: ", 17);
        write(2, cmd->argv[1], ft_strlen(cmd->argv[1]));
        write(2, ": numeric argument required\n", 28);
		exit_status = 255;
		exit(exit_status);
	}
	return(0);
}
