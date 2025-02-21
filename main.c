#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "users.h"
#include "processes.h"
#include "logger.h"

void print_help() {
    printf("Usage: myutil [OPTIONS]\n");
    printf("  -u, --users        Show list of users and home directories\n");
    printf("  -p, --processes    Show list of running processes\n");
    printf("  -h, --help         Show this help message\n");
    printf("  -l, --log PATH     Log output to file at PATH\n");
    printf("  -e, --errors PATH  Log errors to file at PATH\n");
}

int main(int argc, char *argv[]) {
    int option;
    int users_flag = 0, processes_flag = 0;

    struct option long_options[] = {
        {"users", no_argument, NULL, 'u'},
        {"processes", no_argument, NULL, 'p'},
        {"help", no_argument, NULL, 'h'},
        {"log", required_argument, NULL, 'l'},
        {"errors", required_argument, NULL, 'e'},
        {NULL, 0, NULL, 0}
    };

    while ((option = getopt_long(argc, argv, "uph:l:e:", long_options, NULL)) != -1) {
        switch (option) {
            case 'u':
                users_flag = 1;
                break;
            case 'p':
                processes_flag = 1;
                break;
            case 'h':
                print_help();
                return 0;
            case 'l':
                log_file = fopen(optarg, "w");
                if (!log_file) {
                    fprintf(stderr, "Error: Unable to open log file: %s\n", optarg);
                    return 1;
                }
                break;
            case 'e':
                error_file = fopen(optarg, "w");
                if (!error_file) {
                    fprintf(stderr, "Error: Unable to open error log file: %s\n", optarg);
                    return 1;
                }
                break;
            default:
                print_help();
                return 1;
        }
    }

    if (users_flag) list_users();
    if (processes_flag) list_processes();

    if (log_file) fclose(log_file);
    if (error_file) fclose(error_file);

    return 0;
}

