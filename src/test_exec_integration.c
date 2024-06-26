/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec_integration.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:58:57 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/25 12:24:17 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_exec.h"

static int	init_environ(void)
{
	extern char	**environ;
	extern int	errno;
	int			env_var_count;
	char		**new_env;

	errno = 0;
	env_var_count = 0;
	while (environ[env_var_count])
		env_var_count++;
	new_env = ft_calloc(env_var_count + 1, sizeof(char *));
	if (!new_env)
		return (EXIT_FAILURE);
	env_var_count = 0;
	while (environ[env_var_count])
	{
		new_env[env_var_count] = ft_strdup(environ[env_var_count]);
		if (!new_env[env_var_count])
			return (ft_free_2d_array((void ***)&new_env, -1), EXIT_FAILURE);
		env_var_count++;
	}
	environ = new_env;
	return (0);
}

int	main(void)
{
	t_token		*input_token[1];

	if (init_environ())
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
