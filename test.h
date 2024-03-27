/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:49:22 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/27 15:23:42 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "minishell.h"

# ifndef RED
#  define RED "\033[0;31m"
# endif

# ifndef GREEN
#  define GREEN "\033[0;32m"
# endif

# ifndef DEFAULT
#  define DEFAULT "\x1b[0m"
# endif

void	test_builtins(void);
void	print_feedback(char *test, char *output, char *expected);

void	echo_test_1(int read_output_fd);
void	echo_test_2(int read_output_fd);
void	echo_test_3(int read_output_fd);
void	echo_test_4(int read_output_fd);
void	echo_test_5(int read_output_fd);
void	echo_test_6(int read_output_fd);

void	exit_test_1(int read_output_fd, int status);

#endif