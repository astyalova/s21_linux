#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""

s21_command=(
    "./s21_grep"
    )
sys_command=(
    "leaks_right"
    )

flags=(
    "v"
    "c"
    "l"
    "n"
    "h"
   # "o"
)

tests=(
"s test_files/test_0_grep.txt FLAGS"
"for s21_grep.c FLAGS"
"-e for -e ^int s21_grep.c FLAGS"
"-e regex -e ^print s21_grep.c FLAGS -f test_files/test_ptrn_grep.txt"
"-e while -e void s21_grep.c Makefile FLAGS -f test_files/test_ptrn_grep.txt"
"-e intel -e int FLAGS test_files/test_7_grep.txt"
"-e int -e intel FLAGS test_files/test_7_grep.txt"
)

manual=(
"-n for test_files/test_1_grep.txt test_files/test_2_grep.txt"
"-n for test_files/test_1_grep.txt"
"-n -e ^\} test_files/test_1_grep.txt"
"-c -e /\ test_files/test_1_grep.txt"
"-ce ^int test_files/test_1_grep.txt test_files/test_2_grep.txt"
"-e ^int test_files/test_1_grep.txt"
"-nivh = test_files/test_1_grep.txt test_files/test_2_grep.txt"
"-e"
"-ie INT test_files/test_5_grep.txt"
"-echar test_files/test_1_grep.txt test_files/test_2_grep.txt"
"-ne = -e out test_files/test_5_grep.txt"
"-iv int test_files/test_5_grep.txt"
"-in int test_files/test_5_grep.txt"
"-c -l aboba test_files/test_1_grep.txt test_files/test_5_grep.txt"
"-v test_files/test_1_grep.txt -e ank"
#"-noe ) test_files/test_5_grep.txt"
"-l for test_files/test_1_grep.txt test_files/test_2_grep.txt"
#"-o -e int test_files/test_4_grep.txt"
"-e = -e out test_files/test_5_grep.txt"
"-noe ing -e as -e the -e not -e is test_files/test_6_grep.txt"
"-e ing -e as -e the -e not -e is test_files/test_6_grep.txt"
"-c -e . test_files/test_1_grep.txt -e '.'"
"-l for no_file.txt test_files/test_2_grep.txt"
"-si s21_grep.c -f no_pattern.txt"
"-f test_files/test_3_grep.txt test_files/test_5_grep.txt"
)

run_test() {
    param=$(echo "$@" | sed "s/FLAGS/$var/")
    valgrind --tool=memcheck --leak-check=yes -s "${s21_command[@]}" $param 2>&1 | grep -o 'ERROR SUMMARY: *[0-9]* errors from *[0-9]*' > "${s21_command[@]}".log
    DIFF="$(diff -s "${s21_command[@]}".log "${sys_command[@]}".log)"
    let "COUNTER++"
    if [ "$DIFF" == "Files "${s21_command[@]}".log and "${sys_command[@]}".log are identical" ]
    then
        let "SUCCESS++"
        echo -e "$COUNTER - \033[36mSUCCESS: $param\033[0m"
    else
        let "FAIL++"
        echo -e "$COUNTER - $param - \033[31mFAIL: $param\033[0m"
    fi
    rm -f "${s21_command[@]}".log
    # rm -f "${s21_command[@]}".log "${sys_command[@]}".log

}

echo "^^^^^^^^^^^^^^^^^^^^^^^"
echo "TESTS WITH NORMAL FLAGS"
echo "^^^^^^^^^^^^^^^^^^^^^^^"
printf "\n"
echo "#######################"
echo "MANUAL TESTS"
echo "#######################"
printf "\n"

for i in "${manual[@]}"
do
    var="-"
    run_test "$i"
done

printf "\n"
echo "#######################"
echo "AUTOTESTS"
echo "#######################"
printf "\n"
echo "======================="
echo "1 PARAMETER"
echo "======================="
printf "\n"

for var1 in "${flags[@]}"
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        run_test "$i"
    done
done
printf "\n"
echo "======================="
echo "2 PARAMETERS"
echo "======================="
printf "\n"

for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1 -$var2"
                run_test "$i"
            done
        fi
    done
done

echo "FAILED: $FAIL"
echo "SUCCESSFUL: $SUCCESS"
echo "ALL: $COUNTER"
printf "\n"
##############################