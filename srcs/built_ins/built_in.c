/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:21:04 by nora              #+#    #+#             */
/*   Updated: 2025/05/11 04:39:11 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin_cmd(t_cmd *cmd)
{
	int		i;
	char	*builtins[7];

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	i = 0;
	while (i < 7)
	{
		// ask Yacoub later about strlen or -1
		if (ft_strncmp(cmd->argv[0], builtins[i], -1) == 0)
			return (1);
		i++;
	}
	return (0);
}
int	execute_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strncmp(cmd->argv[0], "echo", -1) == 0)
	{
		ft_echo(cmd->argv);
		return (0);
	}
	return (1);
}