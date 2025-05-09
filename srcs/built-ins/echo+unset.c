/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo+unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:21:17 by nora              #+#    #+#             */
/*   Updated: 2025/05/07 20:41:49 by nora             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_echo(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	new_line;
	(void)shell;

	if (!cmd || !cmd->argv)
	{
		write(2, "minishell: echo: invalid input\n", 31);
		return (1);
	}
	i = 1;
	new_line = 1;
    while (cmd->argv[i] && ft_strlen(cmd->argv[i]) == 2 && ft_strncmp(cmd->argv[i], "-n", 2) == 0)
	{
		new_line = 0;
		i++;
	}
	while (cmd->argv[i])
	{
		write(1, cmd->argv[i], ft_strlen(cmd->argv[i]));
		if (cmd->argv[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (new_line == 1)
		write(1, "\n", 1);
	return (0);
}


int ft_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	status;
	char *arg;

	if (!cmd || !cmd->argv || !shell || !shell->envp)
	{
		write(2, "minishell: unset: invalid input or environment\n", 47);
		shell->exit_status = 1;
		return (1);
	}
	if (cmd->argv[1] == NULL)
	{
		shell->exit_status = 0;
		return (0);
	}
	i = 1;
	status = 0;
	while (cmd->argv[i])
	{
		arg = cmd->argv[i];
		if (!is_valid_env_name(arg))
        {
            write(2, "minishell: unset: '", 19);
            write(2, arg, ft_strlen(arg));
            write(2, "': not a valid identifier\n", 26);
            status = 1;
        }
		else
		{
			if(ft_unsetenv(arg, shell) != 0)
			status = 1;
		}
		i++;
	}
	shell->exit_status = status;
	return (status);
}
