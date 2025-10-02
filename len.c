#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>

typedef struct {
    int total;
    int letters;
    int digits;
    int spaces;
    int special;
} char_stats;

void analyze_char(int c, char_stats *stats) {
    stats->total++;
    if (isalpha(c)) {
        stats->letters++;
    } else if (isdigit(c)) {
        stats->digits++;
    } else if (isspace(c)) {
        stats->spaces++;
    } else {
        stats->special++;
    }
}

void print_summary(const char_stats *stats) {
    printf("┌──────────┬───────┐\n");
    printf("│ Type     │ Count │\n");
    printf("├──────────┼───────┤\n");
    printf("│ Total    │ %5d │\n", stats->total);
    printf("│ Letters  │ %5d │\n", stats->letters);
    printf("│ Digits   │ %5d │\n", stats->digits);
    printf("│ Spaces   │ %5d │\n", stats->spaces);
    printf("│ Special  │ %5d │\n", stats->special);
    printf("└──────────┴───────┘\n");
}

int len_from_args(int argc, char *argv[], int start_index, char_stats *stats) {
    if (stats) memset(stats, 0, sizeof(char_stats));
    
    int length = 0;
    for (int i = start_index; i < argc; i++) {
        for (int j = 0; argv[i][j]; j++) {
            length++;
            if (stats) analyze_char((unsigned char)argv[i][j], stats);
        }
        if (i < argc - 1) {
            length++;
            if (stats) analyze_char(' ', stats);
        }
    }
    return length;
}

int len_from_stdin(char_stats *stats) {
    if (stats) memset(stats, 0, sizeof(char_stats));
    
    int length = 0;
    int c;
    while ((c = getchar()) != EOF) {
        length++;
        if (stats) analyze_char(c, stats);
    }
    return length;
}

int len_from_file(const char *filename, char_stats *stats) {
    if (stats) memset(stats, 0, sizeof(char_stats));
    
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "len: cannot open file '%s': %s\n", filename, strerror(errno));
        return -1;
    }

    int length = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        length++;
        if (stats) analyze_char(c, stats);
    }

    fclose(file);
    return length;
}

static void print_usage(void) {
    fprintf(stderr, "Usage: len [OPTIONS] [text...]\n");
    fprintf(stderr, "\nOptions:\n");
    fprintf(stderr, "  -f FILE    Read from file\n");
    fprintf(stderr, "  -s         Show summary\n");
    fprintf(stderr, "  -h         Show help\n");
    fprintf(stderr, "\nExamples:\n");
    fprintf(stderr, "  len \"hello world\"         # Count characters\n");
    fprintf(stderr, "  len -s \"hello world\"      # Show summary\n");
    fprintf(stderr, "  len -f myfile.txt         # Count file characters\n");
    fprintf(stderr, "  len -sf myfile.txt        # Show file summary\n");
}

int main(int argc, char *argv[]) {
    int show_summary = 0;
    char *filename = NULL;
    char_stats stats;
    int opt;
    
    while ((opt = getopt(argc, argv, "sf:h")) != -1) {
        switch (opt) {
            case 's':
                show_summary = 1;
                break;
            case 'f':
                filename = optarg;
                break;
            case 'h':
                print_usage();
                return 0;
            case '?':
                fprintf(stderr, "Try 'len -h' for more information.\n");
                return 1;
        }
    }

    if (filename) {
        int len = len_from_file(filename, show_summary ? &stats : NULL);
        if (len >= 0) {
            if (show_summary) {
                print_summary(&stats);
            } else {
                printf("%d\n", len);
            }
            return 0;
        }
        return 1;
    }

    if (optind < argc) {
        int len = len_from_args(argc, argv, optind, show_summary ? &stats : NULL);
        if (show_summary) {
            print_summary(&stats);
        } else {
            printf("%d\n", len);
        }
        return 0;
    }

    if (!isatty(STDIN_FILENO)) {
        int len = len_from_stdin(show_summary ? &stats : NULL);
        if (show_summary) {
            print_summary(&stats);
        } else {
            printf("%d\n", len);
        }
        return 0;
    }

    print_usage();
    return 1;
}

