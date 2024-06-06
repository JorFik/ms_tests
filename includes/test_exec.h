/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:51:36 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/06 19:32:35 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_EXEC_H
# define TEST_EXEC_H

# include "minishell.h"

# define TEST_COUNT 3

char	**transform_to_array(t_token *token);
char	***test_transform_to_array(const char ***expected_argvs,
			t_token **input_token);

#endif