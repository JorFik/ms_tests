/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:51:36 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/20 18:35:21 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_EXEC_H
# define TEST_EXEC_H

# include "minishell.h"

# define TEST_COUNT 4
# define ARGV_ERROR "\t\tTest %d failed\n\t\tCmd->argv isn't initialize\n"
# define MORE_LESS_CMD "\t\tTest %d failed\n\t\t+/- t_cmd expected\n"
# define FD_ERROR "\t\tTest %d failed\n\t\tExpected fd: %d\n\t\tOutput fd: %d\n"
# define FILE_ERROR \
	"\t\tTest %d failed\n\t\tExpected file: %s\n\t\tOutput file: %s\n"

enum	e_flags_check_pipe
{
	PIPING_OUT = 1,
	PIPING_IN
};

typedef struct s_expected_redir
{
	char					*file_name;
	int						fd;
	struct s_expected_redir	*next;
	struct s_expected_redir	*prev;
}	t_exp_redir;

// Tested functions
char				**transform_to_array(t_token *token);
t_cmd				*divide_tokens(t_token *token);
int					get_fd(t_cmd *cmd);
char				*get_file_name(t_cmd *cmd);

// Test transform to array
t_cmd				**test_transform_to_array(t_cmd **cmd_input);
const t_token_type	**declare_test_token_type(void);
const char			***declare_test_strings(void);

// Test divide tokens
t_cmd				**test_divide_tokens(const t_token **input_token);
const t_cmd			**create_all_expected_cmds(void);
void				free_expected_cmd(t_cmd ***expected_cmd);
void				free_cmds(t_cmd **cmd);

// Test redir
int					test_redir(t_cmd **cmd_input);
void				free_exp_redir(t_exp_redir **exp_redir);

// Token utils
t_token				*create_token_head(const char *value, t_token_type type);
t_token				*create_next_token(t_token *token, const char *value,
						t_token_type type);
void				restart_token(t_token **token);

// Utils
void				leaks(void);
void				run_leaks(const char *test_name);

#endif