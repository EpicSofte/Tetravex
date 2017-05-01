#pragma once

#include <getopt.h>
#include <iostream>
#include <cstdint>
#include <vector>
#include <tuple>
#include "tetravex.hh"

/*
**    WARNING:
**    This file is not to be edited. It provides functions which automatically
**    parse the input according to the given specifications of the subject.
*/

// Error flags:
#define ERROR_NO_SOL    1
#define ERROR_BAD_USAGE 2
#define ERROR_BAD_FILE  3

template <class T>
using Tuple = std::tuple<int, T>;

struct Cli_opt
{
    size_t size = 0;
    std::string output;
    std::string input;
    bool flag_size = false;
    bool flag_out = false;
    bool flag_in = false;
};

void print_usage(bool error);
Tuple<Cli_opt> check_validity_cli(Cli_opt opt);
Tuple<Cli_opt> parse_cli(int argc, char **argv);
template <class T> int run_epivex(int argc, char** argv);

inline void
print_usage(std::ostream& stream)
{
    stream  << "Options:\n"
            << "  -h [ --help ]              "
            << "Display the help\n"
            << "  -o [ --output ] arg        "
            << "Generate/solve puzzle in file arg.vex\n"
            << "  -i [ --input ]  arg        "
            << "Solve puzzle in file arg.vex\n"
            << "  -s [ --size ]   arg        "
            << "Size of the tetravex (>0)\n";
}


inline Tuple<Cli_opt>
check_validity_cli(const std::tuple<int, Cli_opt>& cli_opt)
{
    if (std::get<0>(cli_opt) != 0)
        return cli_opt;

    auto opt = std::get<1>(cli_opt);
    int error = 0;

    if ((!opt.flag_out && opt.flag_in)
        || (!opt.flag_out && opt.flag_size)
        || (opt.flag_size && opt.size < 1))
    {
        print_usage(std::cerr);
        error = ERROR_BAD_USAGE;
    }
    else if (opt.flag_size && opt.flag_in)
    {
        std::cerr << "Incompatible options: <size> & <input>." << std::endl;
        error = ERROR_BAD_USAGE;
    }

    return std::make_tuple(error, opt);
}

inline Tuple<Cli_opt>
parse_cli(int argc, char **argv)
{
    Cli_opt cli_opt;
    static struct option options[] = {
            {"help", no_argument, 0, 'h'},
            {"size", required_argument, 0, 's'},
            {"output", required_argument, 0, 'o'},
            {"input", required_argument, 0, 'i'},
            {0, 0, 0, 0}
    };

    int opt = 0;
    int long_index = 0;
    while ((opt = getopt_long(argc, argv,"hs:o:i:",
                              options, &long_index )) != -1)
    {
        switch (opt)
        {
            case 'h':
                print_usage(std::cout);
                exit(0);
            case 's':
                cli_opt.size = atoi(optarg);
                cli_opt.flag_size = true;
                break;
            case 'o':
                cli_opt.output = optarg;
                cli_opt.flag_out = true;
                break;
            case 'i':
                cli_opt.input = optarg;
                cli_opt.flag_in = true;
                break;
            default:
                print_usage(std::cerr);
                return std::make_tuple(ERROR_BAD_USAGE, cli_opt);
        }
    }

    return std::make_tuple(0, cli_opt);
}


template <class T>
inline int
run_epivex(int argc, char** argv)
{
    int error;
    Cli_opt opt;
    std::tie(error, opt) = check_validity_cli(parse_cli(argc, argv));

    if (error != 0)
        return error;
    if (opt.flag_in)
    {
        Tetravex<T> tetravex(opt.size);
        error = tetravex.read(opt.input);
        if (error != 0)
            return error;
        return tetravex.solve(opt.output);
        return 0;
    }

    auto tetravex = generate<int>(opt.size);
    return tetravex.write(opt.output);
}
