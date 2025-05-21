/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:21:04 by nora              #+#    #+#             */
/*   Updated: 2025/05/20 19:57:39 by amal             ###   ########.fr       */
=======
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:21:04 by nora              #+#    #+#             */
/*   Updated: 2025/05/17 10:00:46 by nora             ###   ########.fr       */
>>>>>>> 17ac939e4a79c7effc42b1f94a297570d742bc72
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
int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
<<<<<<< HEAD

	if (ft_strncmp(cmd->argv[0], "echo", -1) == 0)
		return (ft_echo(cmd, shell));
	if (ft_strncmp(cmd->argv[0], "cd", -1) == 0)
		return (ft_cd(cmd, shell));
	if (ft_strncmp(cmd->argv[0], "pwd", -1) == 0)
		return (ft_pwd(cmd, shell));
	if (ft_strncmp(cmd->argv[0], "export", -1) == 0)
		return (ft_export(cmd, shell));
	if (ft_strncmp(cmd->argv[0], "env", -1) == 0)
		return (ft_env(cmd, shell));
	if (ft_strncmp(cmd->argv[0], "unset", -1) == 0)
		return (ft_unset(cmd, shell));
	if (ft_strncmp(cmd->argv[0], "exit", -1) == 0)
		ft_exit(cmd, shell);

=======
	if (ft_strncmp(cmd->argv[0], "echo", -1) == 0)
	{
		ft_echo(cmd, shell);
		return (0);
	}
	if (ft_strncmp(cmd->argv[0], "cd", -1) == 0)
	{
		ft_cd(cmd, shell);
		return (0);
	}
	if (ft_strncmp(cmd->argv[0], "pwd", -1) == 0)
	{
		ft_pwd(cmd, shell);
		return (0);
	}
	if (ft_strncmp(cmd->argv[0], "export", -1) == 0)
	{
		ft_export(cmd, shell);
		return (0);
	}
	if (ft_strncmp(cmd->argv[0], "env", -1) == 0)
	{
		ft_env(cmd, shell);
		return (0);
	}
	if (ft_strncmp(cmd->argv[0], "unset", -1) == 0)
	{
		ft_unset(cmd, shell);
		return (0);
	}
	if (ft_strncmp(cmd->argv[0], "exit", -1) == 0)
	{
		ft_exit(cmd, shell);
		return (0);
	}
>>>>>>> 17ac939e4a79c7effc42b1f94a297570d742bc72
	return (1);
}
