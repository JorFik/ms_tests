#! /bin/bash


RM="rm -rf"
# COLORS
BOLD_RED="\033[1;31m"
BOLD_GREEN="\033[1;32m"
BOLD_YELLOW="\033[1;33m"
ITALIC_YELLOW="\033[3;33m"
RED="\033[0;31m"
YELLOW="\033[0;33m"
GREEN="\033[0;32m"
CYAN="\033[0;34m"
DEFAULT="\033[0;0m"

function prepare_logs_dir
{
	if [[ ! -d "tests/logs" ]]; then
		mkdir -p tests/logs
	fi
}

function check_norminette
{
	normerror=$(norminette | grep -E "Error:|Error!")
	if [ -n "$normerror" ]; then
		echo -e "$BOLD_RED Norminette error(s) detected, please fix it/them before running the pushing to vogsphere.$DEFAULT"
		echo -e $RED && norminette | grep -E "Error:|Error!" && echo -e $DEFAULT
	fi
}

function feedback
{
	failed=$(grep "Failed" tests/logs/result_parser.log)
	if [ -z "$failed" ]; then
		echo -e "$BOLD_GREEN All tests passed successfully.$DEFAULT"
		return
	fi
	echo -e "$BOLD_RED 1 or more test failed:$DEFAULT"
	(echo -ne "$RED"
	grep "Failed" tests/logs/result_parser.log
	echo -ne "$DEFAULT") | awk '{print "\t", $0}'
	echo -e "$CYAN\tFor more information see tests/logs/result_parser.log$DEFAULT"
	return 1
}


function run_valgrind
{
	local EXECUTABLE=$1
	local TEST_NAME=$2
	local VALGRIND_LOG="tests/logs/valgrind_$3.log"
	local LOG_PATH=$4

	if [[ "$(uname)" == "Linux" ]]
	then
		LEAKS=$(valgrind --leak-check=full --show-leak-kinds=all -s  ./$EXECUTABLE 2>&1 | grep "ERROR SUMMARY:" | awk '{print $4}')
		if [[ $LEAKS != 0 ]]
		then
			valgrind --leak-check=full --show-leak-kinds=all -s ./$EXECUTABLE 2> $VALGRIND_LOG
			echo -e "$BOLD_RED Memory leaks detected in test $TEST_NAME$DEFAULT"
			echo -e "$ITALIC_YELLOW Check $VALGRIND_LOG for more information$DEFAULT"
			echo -e "\t\tLeak test failed in $TEST_NAME" >> $LOG_PATH
			echo -e "\tCheck $VALGRIND_LOG for more information" >> $LOG_PATH
		else
			echo -e "\tLeak test in $TEST_NAME: PASS" >> $LOG_PATH
		fi
	fi
}

function start_log
{
	echo -e "===============\t\t\t\t$(date +%d\ %b\ %Y\ @\ %T)\t\t\t\t===============\n" > $1
}

function end_log
{
	echo -e "\n================\t\t\t\tEND of the log\t\t\t\t\t================" >> $1
}

function check_compilation
{
	local LOG_PATH=$2
	local EXECUTABLE=$1

	if [[ ! -x $EXECUTABLE ]] ; then
		echo -ne "$BOLD_RED"
		echo "Failed compilation for $EXECUTABLE"
		echo -ne "$DEFAULT"
		echo >> $LOG_PATH
		return 1
	fi
	return
}

function check_log
{
	local LOG_PATH=$2
	local TEST_NAME=$1

	if [[ "$(cat $LOG_PATH | grep -c "failed")" > 0 ]]; then
		echo -ne "$BOLD_RED"
		echo "Failed one or more $TEST_NAME tests"
		echo -e "$CYAN\tFor more information check $LOG_PATH"
		echo -ne "$DEFAULT"
		return 1
	fi
	echo -ne "$BOLD_GREEN"
	echo "All $TEST_NAME tests passed successfully"
	echo -ne "$DEFAULT"
}