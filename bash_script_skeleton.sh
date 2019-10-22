#!/bin/bash
################################################################################
# Outline came mostly from Kfir Lavi at his blog "Say what?"
# see http://www.kfirlavi.com/blog/2012/11/14/defensive-bash-programming/
################################################################################
#let script exit if a command fails
set -o errexit 
#let script exit if an unsed variable is used
set -o nounset


# Declare globals
RUN_DIR=$PWD
PROG_NAME="$(basename $0)"
PROG_DIR="$(dirname $0)"
PROG_PATH="$(cd "$PROG_DIR"; pwd)"
ARGS="$@"

if [ $PROG_PATH != "$PWD" ]; then
    cd $PROG_PATH
fi

################################################################################
# Useful functions
################################################################################
source bashTools.sh # from LexTools (https://github.com/alexarmstrongvi/LexTools)

################################################################################
# Usage information
function usage() {
        # NOTE: cat <<-EOF only works if tabs are used for the following lines 
        #       of text. Spaces will cause problems
	cat <<- EOF
	############################################################################
	#    ${PROG_NAME}
	#
	#    TODO: Description of program. Current skeleton loops over lines of
	#    input file and stores them in output file
	#
	#
	#    OPTIONS:
	#       Required:
	#       -i    input file name
	#
	#       Optional:
	#       -o    output file name [default: output.txt]
	#       -r    replace/overwrite output file if it already exists
	#       -t    run unit test to check the program
	#       -v    run in verbose mode
	#       -h    show this help
	#
	#    Examples:
	#       Run unit tests:
	#       $PROG_NAME -t
	#
	#       Run:
	#       $PROG_NAME -i input.txt
	############################################################################
	EOF
}

function print_configuration() {
	cat <<- EOF
	########################################################################
	#   ${PROG_NAME} Configuration
	#
	#   Run cmd: ${PROG_DIR}/${PROG_NAME} $ARGS
	#   Run from: $RUN_DIR
	#
	#   Input file name:  $INPUT_FILE_NAME
	#   Output file name: $OUTPUT_FILE_NAME
	#   Overwrite output file:  $REPLACE
	#   Run tests:  $RUN_TESTS
	#   Verbose:    $VERBOSE
	#   Debug mode: $DEBUG
	#
	########################################################################
	EOF
}
################################################################################
# Comamand line argument parsing
function cmdline()
{
    while getopts "i:o:rtvdh:" OPTION; do
        case $OPTION in
            i) INPUT_FILE_NAME=$OPTARG ;;
            o) OUTPUT_FILE_NAME=$OPTARG ;;
            r) REPLACE=true ;;
            t) RUN_TESTS=true ;;
            v) VERBOSE=true ;;
            d)
                DEBUG='-x'
                set -x
                ;;
            h)
                usage
                exit 0
                ;;
            \?)
            echo "Invalid option: -$OPTARG"
            exit 1;
            ;;
        esac
    done

    ############################################################################
    # Set defaults
    if is_empty $OUTPUT_FILE_NAME; then
        OUTPUT_FILE_NAME="output.txt"
    fi

    # Check arguments if not running tests
    if is_empty $RUN_TESTS; then
        if is_empty ${RUN_DIR}/${INPUT_FILE_NAME}; then
            echo "ERROR :: No input file provided"
            exit 1
        elif is_not_file ${RUN_DIR}/${INPUT_FILE_NAME}; then
            echo -e "ERROR :: Unable to find $INPUT_FILE_NAME in \n\t ${RUN_DIR}"
            exit 1
        elif is_file $OUTPUT_FILE_NAME && is_empty $REPLACE; then
            echo "ERROR :: $OUTPUT_FILE_NAME already exists."
            echo "ERROR :: Either delete/rename $OUTPUT_FILE_NAME or use -r flag"
            exit 1
        fi

        ## Print configuration
        if is_true $VERBOSE; then
            print_configuration
        fi
    fi
}

################################################################################
# Main
################################################################################
function main() {
    # Create output file
    echo "${PROG_DIR}/${PROG_NAME} $ARGS" > $OUTPUT_FILE_NAME

    # Loop over input file
    while IFS='' read -r line || [[ -n "$line" ]]; do
        # Skip blank lines or lines starting with #
        if is_empty "$line" || [[ ${line:0:1} == "#" ]]; then
            continue
        fi

        # Apply command to each line
        cmd="echo $line"
        $cmd >> ${RUN_DIR}/${OUTPUT_FILE_NAME}
    done < "${RUN_DIR}/${INPUT_FILE_NAME}"
}

################################################################################
# Run main program
if is_true $VERBOSE; then
    echo ">> Running $PROG_NAME"
fi
cmdline $ARGS
if is_true $RUN_TESTS; then
    source "test_$PROG_NAME"
else
    main
fi

# Return to original directory if there was a change
if is_not_empty $RUN_DIR && [ "$RUN_DIR" != "$PWD" ]; then
    cd $RUN_DIR
fi
if is_true $VERBOSE; then
    echo "Output stored at ${RUN_DIR}/${OUTPUT_FILE_NAME}"
    echo "<< Successfully ran $PROG_NAME"
fi
set +x
exit 0
