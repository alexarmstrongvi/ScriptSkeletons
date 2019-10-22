#!/usr/bin/env python
"""
================================================================================
TODO: Synopsis
Examples
    python categorize_samples.py
Author:
    Alex Armstrong <alarmstr@cern.ch>
================================================================================
"""

from __future__ import print_function
import sys, os, argparse


parser = argparse.ArgumentParser()
parser.add_argument('-i', '--input', help='Input file')
parser.add_argument('-f', '--flag', help='Flag')
args = parser.parse_args()

################################################################################
def main ():
    """ Main Function """

    global args
    print_hello_world()
    

################################################################################
# FUNCTIONS
def print_hello_world(param=''):
    print ("Hello World! " + param)

################################################################################
# Run main when not imported
if __name__ == '__main__':
    main()
