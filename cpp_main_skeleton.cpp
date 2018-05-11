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
#include <string>

using std::string, std::cout, std::cerr;

////////////////////////////////////////////////////////////////////////////////
// Declarations
////////////////////////////////////////////////////////////////////////////////
/// @brief Print help information
void print_usage(string exec_name, string ofile_name_df, bool flag_df) {
    printf("============================================================\n");
    printf(" %s\n", exec_name.c_str());
    printf(" TODO : Brief description of program\n");
    printf("============================================================\n");
    printf("Required Parameters:\n");
    printf("\tInput file name\n");
    printf("\nOptional Parameters:\n");
    printf("\t-o, --output      Output file name [default: %s]\n", ofile_name_df.c_str());
    printf("\t-f, --flag        Boolean flag [default: %i]\n", flag_df);
    printf("\t-h, --help        Print this help message\n");
    printf("============================================================\n");
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Main function
///
/// Run with help option (-h, --help) to see available parameters
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
    ////////////////////////////////////////////////////////////////////////////
    // Get command line arguments
    // Adding arguments requires updating
    //    -  n_required_args
    //    -  initialization of arguments
    //    -  print_usage signature and implementation
    //    -  argument parser
    //    -  arugment configuation printer
    ////////////////////////////////////////////////////////////////////////////

    string exec_name = argv[0];

    // Configuration options
    uint n_required_args = 1; ///< Number of required arguments from user

    // Initialize optional arguments with defaults
    string ofile_name;
    string ofile_name_df = ofile_name = "output.txt";
    bool flag;
    bool flag_df = flag = false;

    // Look for help option
    for (int i = 0; i < argc; ++i) {
        string opt = argv[i];
        if (opt == "-h" || opt == "--help") {
            print_usage(exec_name, ofile_name_df, flag_df);
            return 0;
        }
    }

    // Check required arguments
    if (argc < n_required_args + 1) {
        cerr << "ERROR :: "
             << argc - 1 << " arguments found but "
             << n_required_args <<" required.\n";
        print_usage(exec_name, ofile_name_df, flag_df);
        return 1;
    }

    // Initialize required arguments
    string ifile_name = argv[1];

    // Parse for optional arguments
    for (int i = n_required_args + 1; i< argc; ++i) {
        // Grab arguments
        string opt = argv[i];
        string opt_value = argc > i+1 ? argv[i+1] : "";
        if (opt.at(0) != '-') continue;

        // Set optional arguments
        if (opt == "-o" || opt == "--output") {
            ofile_name = opt_value;
        } else if (opt == "-f" || opt == "--flag") {
            flag = true;
        } else if (opt == "-h" || opt == "--help") {
            print_usage(exec_name, ofile_name_df, flag_df);
            return 0;
        } else {
            cerr << "ERROR :: Unrecognized input argument: "
                 << opt << " -> " << opt_value << '\n';
        }
    }

    // Check optional arguments
    if (ifile_name.size() == 0) {
        cerr << "ERROR :: Input file name is blank\n";
        return 1;
    } else if (ofile_name == "output.txt") {
        cerr << "ERROR :: " << ofile_name << " is an unnacceptable name\n";
        return 1;
    } else if (flag == false) {
        cerr << "ERROR :: " << (flag ? "True" : "False") << " is a bad flag\n";
        return 1;
    }

    // Print argument configuration
    printf("============================================================\n");
    printf(" %s Settings\n", exec_name.c_str());
    printf("============================================================\n");
    printf("\tInput file name:  %s\n", ifile_name.c_str());
    printf("\tOutput file name: %s\n", ofile_name.c_str());
    printf("\tBoolean flag:     %i\n", flag);
    printf("============================================================\n");


    ////////////////////////////////////////////////////////////////////////////
    // Main implementation
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "Hello World\n";
    return 0;
}
