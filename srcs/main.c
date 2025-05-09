/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nora <nora@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:31:06 by amal              #+#    #+#             */
/*   Updated: 2025/05/09 19:43:30 by nora             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    init_minishell(t_shell *shell)
{
    char    *line;
    t_token *token_list;
    t_cmd   *cmd_list;

    while (1)
    {
        line = readline("minishell$ ");
        if (!line)
        {
            write(1, "exit\n", 5);
            break ;
        }
        if (line[0] == '\0' || is_standard_whitespace_string(line))
        {
             free(line);
             continue;
        }
        add_history(line);
        token_list = tokenize_line(line);
        print_tokens(token_list);
        cmd_list = parse_tokens(token_list);
        print_cmds(cmd_list);
        if (cmd_list)
        {
            if (expand_command(cmd_list, shell) != 0)
            {
                perror("minishell: expansion failed");
                free_cmd_list(cmd_list);
                free(line);
                shell->exit_status = 1;
                continue ;
            }
        }
        if (cmd_list && cmd_list->argv && cmd_list->argv[0] && cmd_list->next == NULL && parent_built_in(cmd_list->argv[0]))
        {
            shell->exit_status = run_builtin(cmd_list, shell);
        }
        else
        {
            execute_command(cmd_list, shell, STDIN_FILENO, STDOUT_FILENO);
        }
        free_cmd_list(cmd_list);
        free(line);
    }
    rl_clear_history();
    exit (shell->exit_status);
}

int main(int argc, char **argv, char **envp)
{
    (void) argc;
    (void) argv;
    t_shell shell;

    shell.envp = copy_env(envp);
    if (!shell.envp)
    {
        perror("minishell : failed to initialize environment");
        return (1);
    }
    shell.exit_status = 0;
    init_minishell(&shell);
    free_env(shell.envp);
    return (shell.exit_status);
}