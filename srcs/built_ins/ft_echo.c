/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:21:17 by nora              #+#    #+#             */
/*   Updated: 2025/05/20 23:50:16 by nora             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;
	while (cmd->argv[i] && ft_strncmp(cmd->argv[i], "-n", 2) == 0)
	{
		int j = 2;
		while (cmd->argv[i][j] == 'n')
			j++;
		if (cmd->argv[i][j] != '\0')
			break;
		newline = 0;
		i++;
	}
	while (cmd->argv[i])
	{
		/*if (cmd->argv[i][0] == '$')
			expand_var(shell, cmd->argv[i] + 1);*/
	//	else
			write(1, cmd->argv[i], ft_strlen(cmd->argv[i]));
		if (cmd->argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	shell->exit_status = 0;
	return (0);
}
