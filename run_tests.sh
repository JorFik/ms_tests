#! /bin/bash
source tests/utils_functions.sh

ERRNO=0
CC=cc
RM="rm -rf"
CFLAGS="-Wall -Wextra -Werror -Wunreachable-code"
INCLUDES="-Iincludes -Ilib/libft/includes -Itests/includes"
LIBRARIES="-Llib/libft -lft"
# COLORS ARE DEFINED IN tests/utils_functions.sh

# DEBUG MODE
DEBUG="-g3"
if [[ "$1" == "d" || "$2" == "d" ]]; then
	CFLAGS="$CFLAGS $DEBUG"
	echo -e "$BOLD_YELLOW Debug mode enabled$DEFAULT"
fi
if [[ "$(uname)" == "Linux" ]]; then
	MANUALLY_ADDED_LIBFT="lib/libft/libft.a"
fi



function run_parser_test
{
	local PARSER_FILES="src/parser/parser.c src/parser/lexer.c\
	src/parser/parser_utils.c src/parser/ft_tokenize_pipe.c\
	tests/src/unit_tests_utils.c tests/src/test_parser.c"
	local LOG_PATH="tests/logs/result_parser.log"
	local EXEC="a.out"

	make -s lib/libft/libft.a
	for TEST_NUM in {1..26};
	do
		$CC $CFLAGS $INCLUDES $LIBRARIES $PARSER_FILES -DTEST=$TEST_NUM $MANUALLY_ADDED_LIBFT 2>> $LOG_PATH
		check_compilation $EXEC $LOG_PATH >> $LOG_PATH
		if [[ $? -ne 0 ]]; then
			ERRNO=$(($ERRNO+1))
			continue
		fi
		echo -e "Test $TEST_NUM" >> $LOG_PATH
		if ! $("./"$EXEC >> $LOG_PATH); then
			echo -e "\tExecution for $EXEC failed" >> $LOG_PATH
		fi
		run_valgrind parser $TEST_NUM
		echo >> $LOG_PATH
		$RM $EXEC
	done
	if [[ $1 -ge 1 && $1 -le 26 ]]; then
		$CC $CFLAGS $INCLUDES $LIBRARIES $PARSER_FILES -DTEST=$1 $MANUALLY_ADDED_LIBFT 2> $LOG_PATH
		echo -e "$BOLD_YELLOW Test $1 ready for debug$DEFAULT"
	fi
	feedback
}

function run_builtin_test
{
	local LOG_PATH="tests/logs/minishell_builtins_results.log"
	local EXEC="builtin_test"

	make -s $EXEC 2> $LOG_PATH 1> /dev/null
	check_compilation $EXEC $LOG_PATH
	if [[ $? -ne 0 ]] ; then
		ERRNO=$(($ERRNO+1))
		echo -e "$CYAN\tFor more information check $LOG_PATH"
		echo -ne "$DEFAULT"
		return 1
	fi
	if ! $("./"$EXEC > $LOG_PATH 2>> $LOG_PATH); then
		echo -e "\tExecution for $EXEC failed" >> $LOG_PATH
	fi
	check_log builtin $LOG_PATH
	ERRNO=$(($ERRNO+$?))
	make -s fclean_test > /dev/null
}

function run_exec_test
{
	local TEST_EXEC=("tests/e_argv_test")
	local LOG_PATH="tests/logs/results_exec.log"

	make -C tests 2>> $LOG_PATH 1> /dev/null
	for exec in "$TEST_EXEC"; do
		check_compilation $exec $LOG_PATH
		if [[ $? -ne 0 ]]; then
			ERRNO=$(($ERRNO+1))
			echo "Compilation failed for $exec" >> $LOG_PATH
			continue
		fi
		echo -e "\t~~~~~~~~~~~~\t\t\t\t$exec\t\t\t\t~~~~~~~~~~~~\n" >> $LOG_PATH
		if ! $("./"$exec >> $LOG_PATH); then
			echo -e "\tExecution for $exec failed" >> $LOG_PATH
		fi
		echo -e "\n\t~~~~~~~~~~~~\t\t\tEND of $exec\t\t\t~~~~~~~~~~~~" >> $LOG_PATH
	done
	check_log exec $LOG_PATH
	ERRNO=$(($ERRNO+$?))
	make -C tests fclean 1> /dev/null
}

if [[ $1 != "SOURCE" ]]; then
	# check_norminette
	prepare_logs_dir
	run_builtin_test
	# start_log tests/logs/result_parser.log
	# run_parser_test
	# end_log tests/logs/result_parser.log
	start_log tests/logs/results_exec.log
	run_exec_test
	end_log tests/logs/results_exec.log
	if [[ $ERRNO -ne 0 ]]; then
		exit $ERRNO
	fi
fi