/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:43:48 by agiliber          #+#    #+#             */
/*   Updated: 2024/10/25 12:44:01 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_sig_status;

int	main(int ac, char **av, char **envp)
{
	t_cmd		*cmd_parsing;
	t_lexer		*tokens;
	t_env		*data;

	data = NULL;
	initiate_struc_envp(&data, envp);
	tokens = NULL;
	cmd_parsing = NULL;
	(void)ac;
	(void)av;
	remove_hdc_file();
	if (generate_minishell_prompt(data, tokens, cmd_parsing) == -1)
		return (-1);
	free_all(data->var);
	free(data);
	return (0);
}
