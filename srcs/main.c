/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:31:06 by amal              #+#    #+#             */
/*   Updated: 2025/04/15 12:16:10 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_minishell(char **envp)
{
	char	*line;
	
	(void)envp;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		
		add_history(line);
	}
	if (line)
		free(line);
	rl_clear_history();
	exit (1);
}

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	
	//init_minishell(envp);
	expand_var(envp, "USER");
	
	return (0);
}



