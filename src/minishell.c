/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumutlu <mumutlu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:25:46 by mumutlu           #+#    #+#             */
/*   Updated: 2023/11/15 15:25:47 by mumutlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(t_env *minienv)
{
	int		exit_status;
	char	*input;
	char	**commands;

	exit_status = EXIT_SUCCESS;
	while (1)
	{
		define_main_signals();
		input = prompt_input(minienv);
		if (has_input_error(input, &exit_status, minienv))
			continue ;
		handle_expansions(&input, minienv, exit_status);
		if (!has_pipe(input))
			exit_status = execute_one_command(input, &minienv);
		else
		{
			commands = split_commands(input);
			free(input);
			exit_status = execute_multiple_commands(commands, &minienv);
			free_array(commands);
		}
	}
	return (exit_status);
}
