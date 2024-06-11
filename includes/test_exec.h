/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:51:36 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/11 19:26:28 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_EXEC_H
# define TEST_EXEC_H

# include "minishell.h"

# define TEST_COUNT 3

enum	e_flags_check_pipe
{
	PIPING_OUT = 1,
	PIPING_IN
};

char				**transform_to_array(t_token *token);
char				***test_transform_to_array(const char ***expected_argvs,
						t_token **input_token);
const t_token_type	**declare_test_token_type(void);
const char			***declare_test_strings(void);

// Test divide tokens
t_cmd				**test_divide_tokens(const t_token **input_token);
const t_cmd			**create_all_expected_cmds(void);
void				free_expected_cmd(t_cmd ***expected_cmd);

// Token utils
t_token				*create_token_head(const char *value, t_token_type type);
t_token				*create_next_token(t_token *token, const char *value,
						t_token_type type);

#endif