/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:50:26 by nora              #+#    #+#             */
/*   Updated: 2025/05/23 17:26:41 by amal             ###   ########.fr       */
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
