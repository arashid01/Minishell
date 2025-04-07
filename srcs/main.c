/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:31:06 by amal              #+#    #+#             */
/*   Updated: 2025/04/08 02:20:03 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main()
{
	char	*line;
	
	while (1)
	{
		line = readline("minishell$ ");

		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break;
		}
		else
		{
			if (*line)
				add_history(line);
			ft_putstr_fd("You entered: ", 1);
			ft_putstr_fd(line, 1);
			ft_putstr_fd("\n", 1);
			free(line);
		}
	}
	rl_clear_history();
	return(0);
}