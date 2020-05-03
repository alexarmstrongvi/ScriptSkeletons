////////////////////////////////////////////////////////////////////////////////
/// Copyright (c) <TODO: year> by Alex Armstrong
///
/// @file cpp_main_skeleton.cpp
/// @author Alex Armstrong <alarmstr@cern.ch>
/// @date <TODO: 1 Jan 1111>
/// @brief <TODO: file description>
///
/// "Detailed description" goes here
/// @see http://www.stack.nl/~dimitri/doxygen/manual/commands.html
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using std::cout;
using std::cerr;
#include <string>
using std::string;

////////////////////////////////////////////////////////////////////////////////
// Declarations
////////////////////////////////////////////////////////////////////////////////
/// @brief Command line argument parser
struct Args {
    ////////////////////////////////////////////////////////////////////////////
    // Initialize arguments
    ////////////////////////////////////////////////////////////////////////////
    string PROG_NAME;  // always required

    // Required arguments
    string ifile_name;  ///< Input file name

    // Optional arguments with defaults
    string ofile_name = "output.txt";  ///< Output file name
    bool flag = false;  ///< Boolean flag

    ////////////////////////////////////////////////////////////////////////////
    // Print information
    ////////////////////////////////////////////////////////////////////////////
    void print_usage() const {
        printf("===========================================================\n");
        printf(" %s\n", PROG_NAME.c_str());
        printf(" TODO : Brief description of executable\n");
        printf("===========================================================\n");
        printf("Required Parameters:\n");
        printf("\t-i, --input       Input file name\n");
        printf("\nOptional Parameters:\n");
        printf("\t-o, --output      Output file name\n");
        printf("\t-f, --flag        Boolean flag\n");
        printf("\t-h, --help        Print this help message\n");
        printf("===========================================================\n");
    }

    void print() const {
        printf("===========================================================\n");
        printf(" %s Configuration\n", PROG_NAME.c_str());
        printf("===========================================================\n");
        printf("\tInput file name:  %s\n", ifile_name.c_str());
        printf("\tOutput file name: %s\n", ofile_name.c_str());
        printf("\tBoolean flag:     %i\n", flag);
        printf("===========================================================\n");
    }

    ////////////////////////////////////////////////////////////////////////////
    // Parser
    ////////////////////////////////////////////////////////////////////////////
    bool parse(int argc, char* argv[]) {
        PROG_NAME = argv[0];

        // Parse arguments
        for (int i = 0; i< argc; ++i) {
            // Grab arguments
            string arg = argv[i];
            string arg_value = argc > i+1 ? argv[i+1] : "";
            // Skip if arg set to arg value and not arg name
            if (arg.at(0) != '-') continue;

            // Check for required arguments
            if (arg == "-i" || arg == "--input") {
                ifile_name = arg_value;
            } else if (arg == "-o" || arg == "--output") {
                ofile_name = arg_value;
            } else if (arg == "-f" || arg == "--flag") {
                flag = true;
            } else if (arg == "-h" || arg == "--help") {
                print_usage();
                return false;
            } else {
                cerr << "ERROR :: Unrecognized input argument: "
                     << arg << " -> " << arg_value << '\n';
                print_usage();
            }
        }

        // Check arguments
        if (ifile_name.size() == 0) {
            cerr << "ERROR :: No input file given\n";
            return false;
        } else if (ofile_name == "output.txt") {
            cerr << "ERROR :: " << ofile_name << " is an unnacceptable name\n";
            return false;
        } else if (flag == false) {
            cerr << "ERROR :: " << (flag ? "True" : "False") << " is a bad flag\n";
            return false;
        }
        return true;
    }
} args;

////////////////////////////////////////////////////////////////////////////////
/// @brief Main function
///
/// Run with help option (-h, --help) to see available parameters
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
    cout << "\n====== RUNNING " << argv[0] << " ====== \n";
    if (args.parse(argc, argv)) {
        // Finished parsing arguments
        args.print();
    } else {
        // Failed to parse arguments or help requested
        return 1;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Main implementation
    ////////////////////////////////////////////////////////////////////////////
    cout << "Accessing args flag: " << args.flag << '\n';
    cout << "\n====== SUCCESSFULLY RAN " << argv[0] << " ====== \n";
    return 0;
}
