/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_error_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 07:43:18 by kali              #+#    #+#             */
/*   Updated: 2024/10/08 10:00:51 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	redir_err(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	if (is_redirection(current->type))
	{
		if (current->next && is_redirection(current->next->type))
		{
			print_error(LEX_ERR, current->next->data);
			return (1);
		}
		else if (!current->next)
		{
			print_error(LEX_ERR, "newline");
			return (1);
		}
	}
	return (0);
}

int	check_quotes(char *str)
{
	int	single_q;
	int	double_q;

	single_q = 0;
	double_q = 0;
	while (*str)
	{
		if (*str == '\'' && double_q == 0)
			single_q = !single_q;
		else if (*str == '"' && single_q == 0)
			double_q = !double_q;
		str++;
	}
	if (single_q % 2 || double_q % 2)
	{
		print_error(LEX_ERR, "quote");
		return (1);
	}
	return (0);
}

int	pipes_err(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	if (!ft_strcmp("||", current->data))
	{
		print_error(LEX_ERR, "||");
		return (1);
	}
	if (current->type == E_PIPE)
	{
		if (!current->prev || !current->next || \
			current->next->type == E_PIPE || current->prev->type == E_PIPE)
		{
			print_error(LEX_ERR, current->data);
			return (1);
		}
	}
	return (0);
}

int	ampersand_err(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	if (current->type == E_AMPERSAND)
	{
		print_error(LEX_ERR, current->data);
		return (1);
	}
	return (0);
}

int	lex_error(t_lexer *head)
{
	t_lexer	*current;
	t_lexer	*tmp;

	current = head;
	if (!head)
		return (1);
	if ((!ft_strcmp(";", head->data) || \
		!ft_strcmp("!", head->data)) && !head->next)
		return (1);
	tmp = remove_space_tokens(head);
	while (tmp)
	{
		if (tmp->type == E_PIPE)
		{
			if (pipes_err(tmp))
				return (1);
		}
		else if (tmp->type == E_AMPERSAND)
		{
			if (ampersand_err(tmp))
				return (1);
		}
		else if (is_redirection(tmp->type))
		{
			if (redir_err(tmp))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
