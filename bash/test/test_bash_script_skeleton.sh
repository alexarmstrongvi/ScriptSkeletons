#!/bin/bash

function oneTimeSetUp() {
    non_empty_var="string"
    test_file="tmp_file.txt"
    test_output="tmp_output.txt"
    test_dir="tmp_dir"

    rm -rf $test_dir
    mkdir $test_dir
    cd $test_dir
    echo "Hello World" > $test_file
    cd ..
    #echo "DEBUG :: Area setup for $test_dir"
    #echo "DEBUG :: Directory structure for ${test_dir}/"
    #ls -R $test_dir | sed -e 's/^/DEBUG ::    /'
    echo
}
source bashTools.sh

function testMain() {
    cd $test_dir
    ../../bash_script_skeleton.sh -i "$test_file" -o "$test_output"

    assertTrue "Output file not created" \
        $(is_file $test_output; echo $?)
    #echo "DEBUG :: Output file contents:"
    #echo "$(cat $test_output)" | sed -e 's/^/DEBUG ::    /'
    assertEquals "Output file not correctly filled" \
        "Hello World" "$(tail -n1 $test_output)"
    cd ..
}

function oneTimeTearDown() {
    #echo "DEBUG :: Running tear down"
    rm -rf $test_dir
}
. shunit2