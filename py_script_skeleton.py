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
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
================================================================================
"""



import sys, os, traceback, argparse
import time
import subprocess

# User Argument defaults and help information
_help_ifile_name = 'Input file name'
_df_ofile_name = 'output.txt'
_help_ofile_name = 'Output file name'
_df_verbose = False
_help_verbose = 'verbose output'


################################################################################
def main ():
    """ Main Function """

    global args
    check_environment()
    check_inputs(args)

    # Do the magic
    print_hello_world()

################################################################################
# FUNCTIONS
def check_inputs(args):
    """ Check the input arguments are as expected """

    if args.ifile_name and not os.path.exists(args.ifile_name):
        print "ERROR :: Cannot find input file:", args.ifile_name
        sys.exit()
    if os.path.exists(args.ofile_name):
        of = args.ofile_name
        if not os.path.exists("%s.bu"%of):
            print "Renaming old output file %s -> %s.bu"%(of, of)
            mv_cmd = 'mv %s %s.bu'%(of, of)
            subprocess.call(mv_cmd, shell=True)
        else:
            print "WARNING :: Output file already exists: %s"%of
            print "\tConsider deleting it or its backup (%s.bu)"%of
            sys.exit()

def check_environment():
    """ Check if the shell environment is setup as expected """
    assert os.environ['USER'], "USER variable not set"

    python_ver = sys.version_info[0] + 0.1*sys.version_info[1]
    assert python_ver >= 2.7, ("Running old version of python\n", sys.version)


def print_hello_world(param=''):
    """
    function synopsis
    args:
        param (type) - description [default: '']
    returns:
        (type) - description
    """
    print "Hello World! " + param
    return True if param else False
################################################################################

def get_args():
    parser = argparse.ArgumentParser(
            description=__doc__,
            formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('-f', '--ifile_name',
                        #required=True,
                        help=_help_ifile_name)
    parser.add_argument('-o', '--ofile_name',
                        default=_df_ofile_name,
                        help=_help_ofile_name)
    parser.add_argument('-v', '--verbose',
                        action='store_true', default=_df_verbose,
                        help=_help_verbose)
    args = parser.parse_args()
    return args

################################################################################
# Run main when not imported
if __name__ == '__main__':
    try:
        start_time = time.time()
        # TODO: Add ability to check standard input so things can be piped
        args = get_args()
        if args.verbose:
            print '>'*40
            print 'Running {}...'.format(os.path.basename(__file__))
            print time.asctime()
        main()
        if args.verbose:
            print time.asctime()
            time = (time.time() - start_time)
            print 'TOTAL TIME: %fs'%time,
            print ''
            print '<'*40
    except KeyboardInterrupt, e: # Ctrl-C
        print 'Program ended by keyboard interruption'
        raise e
    except SystemExit, e: # sys.exit()
        print 'Program ended by system exit'
        raise e
    except Exception, e:
        print 'ERROR, UNEXPECTED EXCEPTION'
        print str(e)
        traceback.print_exc()
        os._exit(1)
