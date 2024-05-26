/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:25:14 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/26 13:51:13 by JFikents         ###   ########.fr       */
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
	WRONG_ARGS,
	WRONG_TYPE
};

# ifndef TEST
#  define TEST_CASE ""
#  define EXPECTED {NULL}
#  define EXP_TYPES {-1}
#  define E_COUNT 1
# endif
# if TEST == 1
#  define TEST_CASE ""
#  define EXPECTED {NULL}
#  define EXP_TYPES {-1}
#  define E_COUNT 1
# elif TEST == 2
#  define TEST_CASE NULL
#  define EXPECTED {NULL}
#  define EXP_TYPES {-1}
#  define E_COUNT 1
# elif TEST == 3
#  define TEST_CASE "echo Hello World"
#  define EXPECTED {"echo", "Hello", "World", NULL}
#  define EXP_TYPES {STRING, STRING, STRING, -1}
#  define E_COUNT 4
# elif TEST == 4
#  define TEST_CASE "echo \"Hello  World\""
#  define EXPECTED {"echo", "Hello  World", NULL}
#  define EXP_TYPES {STRING, DOUBLE_QUOTES, -1}
#  define E_COUNT 3
# elif TEST == 5
#  define TEST_CASE "echo \"Hello' World\""
#  define EXPECTED {"echo", "Hello' World", NULL}
#  define EXP_TYPES {STRING, DOUBLE_QUOTES, -1}
#  define E_COUNT 3
# elif TEST == 6
#  define TEST_CASE "echo \"Hello\" World\""
#  define EXPECTED {"echo", "Hello", "World\"", NULL}
#  define EXP_TYPES {STRING, DOUBLE_QUOTES, STRING, -1}
#  define E_COUNT 4
# elif TEST == 7 
#  define TEST_CASE "echo Hello\" World"
#  define EXPECTED {"echo", "Hello\"", "World", NULL}
#  define EXP_TYPES {STRING, STRING, STRING, -1}
#  define E_COUNT 4
# elif TEST == 8
#  define TEST_CASE "echo \"Hello\"World"
#  define EXPECTED {"echo", "HelloWorld", NULL}
#  define EXP_TYPES {STRING, STRING, -1}
#  define E_COUNT 3
# elif TEST == 9
#  define TEST_CASE "echo Hello\"World\"       "
#  define EXPECTED {"echo", "HelloWorld", NULL}
#  define EXP_TYPES {STRING, STRING, -1}
#  define E_COUNT 3
# elif TEST == 10
#  define TEST_CASE "echo              Hello\"World\"'stuck'        "
#  define EXPECTED {"echo", "HelloWorldstuck", NULL}
#  define EXP_TYPES {STRING, STRING, -1}
#  define E_COUNT 3
# elif TEST == 11
#  define TEST_CASE "ec ho\"  'Hello  \"World'  x "
#  define EXPECTED {"ec", "ho  'Hello  World'",  "x", NULL}
#  define EXP_TYPES {STRING, STRING, STRING, -1}
#  define E_COUNT 4
# elif TEST == 12
#  define TEST_CASE "\"'\"''\"'\""
#  define EXPECTED {"'", "", "'", NULL}
#  define EXP_TYPES {DOUBLE_QUOTES, SINGLE_QUOTES, DOUBLE_QUOTES, -1}
#  define E_COUNT 4
# elif TEST == 13
#  define TEST_CASE "a\"'123'456\""
#  define EXPECTED {"a'123'456", NULL}
#  define EXP_TYPES {STRING, -1}
#  define E_COUNT 2
# elif TEST == 14
#  define TEST_CASE "\"'123'456\""
#  define EXPECTED {"'123'456", NULL}
#  define EXP_TYPES {DOUBLE_QUOTES, -1}
#  define E_COUNT 2
# elif TEST == 15
#  define TEST_CASE "\"'\""
#  define EXPECTED {"'", NULL}
#  define EXP_TYPES {DOUBLE_QUOTES, -1}
#  define E_COUNT 2
# elif TEST == 16
#  define TEST_CASE "''"
#  define EXPECTED {"", NULL}
#  define EXP_TYPES {SINGLE_QUOTES, -1}
#  define E_COUNT 2
# elif TEST == 17
#  define TEST_CASE "\"\""
#  define EXPECTED {"", NULL}
#  define EXP_TYPES {DOUBLE_QUOTES, -1}
#  define E_COUNT 2
# elif TEST == 18
#  define TEST_CASE "'\"'"
#  define EXPECTED {"\"", NULL}
#  define EXP_TYPES {SINGLE_QUOTES, -1}
#  define E_COUNT 2
# elif TEST == 19
#  define TEST_CASE "''\"'\""
#  define EXPECTED {"'", NULL}
#  define EXP_TYPES {STRING, -1}
#  define E_COUNT 2
# elif TEST == 20
#  define TEST_CASE "\"no clue of ''what other test   \"to do'"
#  define EXPECTED {"no clue of ''what other test   to", "do'", NULL}
#  define EXP_TYPES {STRING, STRING, -1}
#  define E_COUNT 3
# endif
# define LEAKS_LINE(test_case) "parse_line(\"" #test_case "\")"


void	run_leaks(const char *test_name);
void	ft_feedback(int error, t_token *result, const char **exp_str,
			const int *exp_types);
int		ft_check_output(t_token *token, const char **expect,
			const int *exp_types);

#endif /* test_parser.h */