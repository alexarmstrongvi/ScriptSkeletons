#!/usr/bin/env python
"""
================================================================================
TODO: Synopsis
Examples
    python <TODO:script name>
TODO: Description (for long scripts)

Author:
    Alex Armstrong <alarmstr@cern.ch>
License:
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details (https://www.gnu.org/licenses/)
================================================================================
"""


from __future__ import print_function
import sys, os, traceback, argparse
import time
import logging

# User Argument defaults and help information
_help_ifile_names = 'Input file name'
_df_ofile_name = 'output.txt'
_help_ofile_name = 'Output file name'
_help_log_level = 'Logging level'
_df_log_level = logging.INFO

# Configure logging
_log_format = '%(levelname)8s :: %(message)s'
#log_format = '%(levelname)8s :: (%(filename)s:%(funcName)s:L%(lineno)d) %(message)s' # Useful for debugging


################################################################################
def main ():
    """ Main Function """

    global args
    check_environment()
    check_inputs(args)

    # Do the magic
    print_hello_world()
    if args.ofile_name:
        with open(args.ofile_name, 'w') as ofile:
            write_str = "Hello World"
            ofile.write(write_str)

################################################################################
# FUNCTIONS
def check_inputs(args):
    """ Check the input arguments are as expected """

    for f in args.ifile_names:
        if not os.path.exists(f):
            logging.error("Cannot find input file:", f )
            sys.exit()
    else:
        logging.info("Reading in %d input file(s)" % len(args.ifile_names))

    # Check if output file exists
    # If so, check with user if they want to overwrite it
    if os.path.exists(args.ofile_name):
        usr_msg =  "Output file already exists: %s\n" % args.ofile_name
        usr_msg += "Would you like to overwrite it? [Y/N] "
        overwrite_op = raw_input(usr_msg)

        # Only accept Y or N
        while overwrite_op not in ["Y","N"]:
            usr_msg = "Unacceptable answer: %s\n" % overwrite_op
            usr_msg += "Would you like to overwrite it? [Y/N] "
            overwrite_op = raw_input(usr_msg)

        if overwrite_op == "N":
            logging.info("Try using a different output file name"
                        +"deleting the old file, or"
                        +"changing the name of the old file.")
            sys.exit()

def check_environment():
    """ Check if the shell environment is setup as expected """
    python_ver = sys.version_info[0] + 0.1*sys.version_info[1]
    assert python_ver >= 2.7, ("Running old version of python\n", sys.version)


def print_hello_world(param=''):
    """
    function synopsis
    args:
        param (type) - description
    return:
        (type) - description
    """
    print ("Hello World! " + param)
    return True if param else False
################################################################################

def get_args():
    parser = argparse.ArgumentParser(
            description=__doc__,
            formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('ifile_names',
                        nargs='+',
                        help=_help_ifile_names)
    parser.add_argument('-o', '--ofile-name',
                        default=_df_ofile_name,
                        help=_help_ofile_name)
    parser.add_argument('-l', '--log-level',
                        default=_df_log_level,
                        help=_help_log_level)
    args = parser.parse_args()
    return args

################################################################################
# Run main when not imported
if __name__ == '__main__':
    try:
        start_time = time.time()
        args = get_args()
        logging.basicConfig(level=args.log_level.upper(), format=_log_format)
        logging.info('>'*40)
        logging.info("Running " + " ".join(sys.argv[1:]))
        logging.debug(time.asctime())

        main()

        logging.debug(time.asctime())
        run_time = (time.time() - start_time)
        logging.info('TOTAL TIME: %fs'% run_time)
        logging.info('<'*40)
    except KeyboardInterrupt, e: # Ctrl-C
        logging.warning('Program ended by keyboard interruption')
        raise e
    except SystemExit, e: # sys.exit()
        logging.warning('Program ended by system exit')
        raise e
    except Exception, e:
        logging.critical('UNEXPECTED EXCEPTION')
        print(str(e))
        traceback.print_exc()
        os._exit(1)
