#!/usr/bin/env python
"""
================================================================================
TODO: Synopsis
Examples
    python <TODO:script name>
TODO: Description (for long scripts)

Author: 
    Alex Armstrong <alarmstr@cern.ch>
TODO: License:
    This script is in the public domain, free from copyrights or restrictions.
    Copyright: (C) <TODO:date>; University of California, Irvine 
================================================================================
"""

import sys, os, traceback, argparse
import time

################################################################################
def main ():
    """ Main Function """
    
    global args
    check_args(args)
    check_environment()

    print "required user input = ", args.req_input
    print "optional user input = ", args.user_input
    print_hello_world()

################################################################################
# FUNCTIONS
def check_args(args):
    """ Check the input arguments are as expected """
    if args.ifile_name and not os.path.exists(args.ifile_name):
        print "ERROR :: Cannot find input file:", args.ifile_name
        sys.exit()
    if os.path.exists(args.ofile_name):
        of = args.ofile_name
        if not os.path.exists("OLD_%s"%of):
            print "Renaming old output file %s -> OLD_%s"%(of, of)
            mv_cmd = 'mv %s OLD_%s'%(of, of)
            subprocess.call(mv_cmd, shell=True)
        else:
            print "WARNING :: Output file already exists: %s"%of
            print "\tConsider deleting it or its backup (OLD_%s)"%of
            sys.exit()

def check_environment():
    """ Check if the shell environment is setup as expected """
    if not os.environ['USER']:
        print "ERROR :: USER variable not set"
        sys.exit()
        

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
# Run main when not imported
if __name__ == '__main__':
    try:
        start_time = time.time()
        parser = argparse.ArgumentParser(
                description=__doc__,
                formatter_class=argparse.RawDescriptionHelpFormatter)
        parser.add_argument('-f', '--ifile_name', 
                            #required=True,
                            help='Input file name')
        parser.add_argument('-o', '--ofile_name', 
                            default='output.txt', 
                            help='o')
        parser.add_argument('--dry_run')
        parser.add_argument('-v', '--verbose', 
                            action='store_true', default=False, 
                            help='verbose output')
        args = parser.parse_args()
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
