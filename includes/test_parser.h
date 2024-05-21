/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:25:14 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/21 19:39:13 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_PARSER_H
# define TEST_PARSER_H

# include "parser.h"
# include "libft.h"
# include <stdlib.h>

enum e_error_type
{
	NO_ERROR,
	NO_RESULT,
	WRONG_CMD,
	NO_ARGS,
	WRONG_ARGS,
	WRONG_AND_INDEX,
	WRONG_NEXT,
	WRONG_PIPE_IN,
	WRONG_PIPE_OUT,
	WRONG_REDIR
};
# ifndef TEST
#  define TEST_CASE ""
#  define EXPECTED {NULL}
#  define E_COUNT 1
# elif TEST == 11
#  define TEST_CASE "ec ho\"  'Hello  \"World'  x "
#  define EXPECTED {"ec", "ho  'Hello  World'",  "x", NULL}
#  define E_COUNT 4
# elif TEST == 12
#  define TEST_CASE "\"'\"''\"'\""
#  define EXPECTED {"'", "", "'", NULL}
#  define E_COUNT 4
# elif TEST == 13
#  define TEST_CASE "a\"'123'456\""
#  define EXPECTED {"a'123'456", NULL}
#  define E_COUNT 2
# elif TEST == 14
#  define TEST_CASE "\"'123'456\""
#  define EXPECTED {"'123'456", NULL}
#  define E_COUNT 2
# elif TEST == 15
#  define TEST_CASE "\"'\""
#  define EXPECTED {"'", NULL}
#  define E_COUNT 2
# elif TEST == 16
#  define TEST_CASE "''"
#  define EXPECTED {"", NULL}
#  define E_COUNT 2
# elif TEST == 17
#  define TEST_CASE "\"\""
#  define EXPECTED {"", NULL}
#  define E_COUNT 2
# elif TEST == 18
#  define TEST_CASE "'\"'"
#  define EXPECTED {"\"", NULL}
#  define E_COUNT 2
# elif TEST == 19
#  define TEST_CASE "''\"'\""
#  define EXPECTED {"'", NULL}
#  define E_COUNT 2
# elif TEST == 20
#  define TEST_CASE "\"no clue of ''what other test   \"to do'"
#  define EXPECTED {"no clue of ''what other test   to", "do'", NULL}
#  define E_COUNT 3
# endif
# define LEAKS_LINE(test_case) "parse_line(\"" #test_case "\")"


void	run_leaks(const char *test_name);
void	ft_free_results(t_instruction **result);
void	ft_feedback(int error, t_instruction *result, const char **exp_str);
int		ft_check_output(t_instruction *token, const char **expect);

#endif /* test_parser.h */