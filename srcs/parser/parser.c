/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:35:41 by amal              #+#    #+#             */
/*   Updated: 2025/05/20 06:47:27 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type == WORD)
	{
		count++;
		token = token->next;
	}
	return (count);
}

char	**build_argv(t_token **token)
{
	int		i;
	int		argc;
	char	**argv;

	i = 0;
	argc = count_args(*token);
	argv = malloc (sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	while (*token && (*token)->type == WORD)
	{
		argv[i++] = ft_strdup((*token)->val);
		*token = (*token)->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	handle_heredoc(const char *delimiter, char **temp_file)
{
	int		fd;
	int		pid;
	int		status;
	char	*line;

	*temp_file = ft_strdup("/tmp/.heredoc_tmp");
	if (!*temp_file)
		ft_error("heredoc");

	pid = fork();
	if (pid < 0)
		ft_error("fork");

	if (pid == 0)
	{
		setup_heredoc_signals();

		fd = open(*temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			ft_error("open");

		while (1)
		{
			line = readline("> ");
			if (!line || ft_strncmp(line, delimiter, -1) == 0)
			{
				free(line);
				break;
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		close(fd);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			unlink(*temp_file);
			free(*temp_file);
			*temp_file = NULL;
		}
	}
}

t_cmd	*parse_tokens(t_token *token_list)
{
	t_cmd	*cmd;
	
	if (!token_list)
		return (NULL);
	cmd = calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = build_argv(&token_list);
	while (token_list)
	{
		if (token_list->type == HEREDOC
			&& token_list->next && token_list->next->type == WORD)
		{
			handle_heredoc(token_list->next->val, &cmd->infile);
			token_list = token_list->next->next;
		}
		else if ((token_list->type == REDIR_IN || token_list->type == REDIR_OUT
					|| token_list->type == REDIR_APPEND) && token_list->next && token_list->next->type == WORD)
		{
			if (token_list->type == REDIR_IN)
				cmd->infile = ft_strdup(token_list->next->val);
			else if (token_list->type == REDIR_OUT)
			{
				cmd->outfile = ft_strdup(token_list->next->val);
				cmd->append = 0;
			}
			else if (token_list->type == REDIR_APPEND)
			{
				cmd->outfile = ft_strdup(token_list->next->val);
				cmd->append = 1;
			}
			token_list = token_list->next->next;
		}
		else if (token_list->type == PIPE)
		{
			cmd->has_pipe = 1;
			token_list = token_list->next;
			cmd->next = parse_tokens(token_list);
			break ;
		}
		else
			token_list = token_list->next;
	}
	return (cmd);
}

void print_cmds(t_cmd *cmd)
{
	int i = 0;
	while (cmd)
	{
		printf("Command:\n");
		while (cmd->argv[i])
		{
			printf("  Arg[%d]: %s\n", i, cmd->argv[i]);
			i++;
		}
		printf("  Has pipe: %d\n\n", cmd->has_pipe);
		i = 0;
		cmd = cmd->next;
	}
}
