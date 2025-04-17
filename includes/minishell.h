/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:31:38 by amal              #+#    #+#             */
/*   Updated: 2025/04/17 11:53:19 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WORD 1 //commands and args
# define PIPE 2 // |
# define APPEND 3 // <
# define OVERWRITE 4 // >
# define REDIR_APPEND 5 // >>
# define HEREDOC 6 // <<

typedef	struct s_status
{
	int	normal;
	int	s_quote;
	int	d_quote;
} t_status;

typedef struct s_token
{
	int				type;
	char			*val;
	struct s_token	*next;
} t_token;

char	*expand_var(char **envp, char *var);

#endif