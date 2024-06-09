/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:51:36 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/09 13:59:59 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_EXEC_H
# define TEST_EXEC_H

# include "minishell.h"

# define TEST_COUNT 3

char				**transform_to_array(t_token *token);
char				***test_transform_to_array(const char ***expected_argvs,
						t_token **input_token);
const t_token_type	**test_token_declaration(void);
const char			***test_cases_declaration(void);

// Token utils
t_token				*create_token_head(const char *value, t_token_type type);
t_token				*create_next_token(t_token *token, const char *value,
						t_token_type type);

#endif