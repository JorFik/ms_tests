/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec_integration.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:58:57 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/11 13:51:28 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_exec.h"

static int	init_minishell(void)
{
	extern char	**environ;
	extern int	errno;

	errno = 0;
	environ = dup_environ();
	if (environ == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	t_token		*input_token[1];

	if (init_minishell())
	{
		perror("minishell: Error initializing environment");
		return (EXIT_FAILURE);
	}
	unlink("test_file1");
	unlink("test_file2");
	unlink(".here_doc.tmp");
	unlink("test_file4");
	input_token[0] = NULL;
	input_token[0] = create_next_token(input_token[0], "echo", STRING);
	input_token[0] = create_next_token(input_token[0], "Hello", STRING);
	input_token[0] = create_next_token(input_token[0], ">", REDIR_TO);
	input_token[0] = create_next_token(input_token[0], "test_file1", STRING);
	input_token[0] = create_next_token(input_token[0], "2>", REDIR_TO);
	input_token[0] = create_next_token(input_token[0], "test_file2", STRING);
	input_token[0] = create_next_token(input_token[0], "|", PIPE);
	input_token[0] = create_next_token(input_token[0], "cat", STRING);
	input_token[0] = create_next_token(input_token[0], "<<", HERE_DOC);
	input_token[0] = create_next_token(input_token[0], "EOF3", STRING);
	input_token[0] = create_next_token(input_token[0], ">>", APPEND_TO);
	input_token[0] = create_next_token(input_token[0], "test_file4", STRING);
	while (input_token[0]->prev)
		input_token[0] = input_token[0]->prev;
	exec(input_token[0]);
	return (clean_up(), EXIT_SUCCESS);
}
