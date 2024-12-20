/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:07:57 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/25 12:43:10 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_fork(t_cmd **parsing, t_env **data)
{
	int		pid;

	if (check_if_builtins((*parsing)->str[0]) && (*parsing)->next == NULL
		&& (*parsing)->redir_nb == 0)
	{
		if (builtins(parsing, data) == -1)
			return (perror("builtins"), -1);
		g_sig_status = 0;
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"), -1);
		if (pid == 0)
		{
			setup_child_signals();
			if (exec_cmd_minishell(parsing, data) == -1)
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		if (pid != 0)
			signal(SIGINT, SIG_IGN);
		waitpid(pid, &g_sig_status, 0);
	}
	return (0);
}

int	exec_cmd_minishell(t_cmd **parsing, t_env **data)
{
	if ((*parsing)->next == NULL)
	{
		if (exec_cmd(parsing, data) == -1)
			return (perror("exec_cmd"), -1);
	}
	else
	{
		if (exec_multiple_cmd(parsing, data) == -1)
			return (perror("exec_multiple_cmd"), -1);
	}
	return (0);
}

int	exec_cmd(t_cmd **parsing, t_env **data)
{
	if ((*parsing)->redir_nb > 0)
	{
		if (fork_redirection(parsing, data) == -1)
			return (perror("fork_redirection"), -1);
	}
	else
	{
		if (exec_single_cmd(parsing, data) == -1)
			return (perror("exec_single_cmd"), -1);
	}
	return (0);
}

int	exec_single_cmd(t_cmd **parsing, t_env **data)
{
	if ((*parsing)->hdc_count != 0
		&& check_if_builtins((*parsing)->hdc->command[0]))
	{
		if (builtins(parsing, data) == -1)
			return (perror("builtins"), -1);
	}
	else if (check_if_builtins((*parsing)->str[0]))
	{
		if (builtins(parsing, data) == -1)
			return (perror("builtins"), -1);
	}
	else
	{
		if (check_cmd_minishell(parsing, (*data)->var) == -1)
			return (perror("check_cmd_minishell"), -1);
	}
	return (0);
}
