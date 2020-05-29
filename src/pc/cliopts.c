#include "cliopts.h"
#include "configfile.h"
#include "cheats.h"
#include "pc_main.h"

#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#ifdef __MINGW32__
#define FOR_WINDOWS 1
#else
#define FOR_WINDOWS 0
#endif

struct PCCLIOptions gCLIOpts;

static void print_help(void) {
    printf("Super Mario 64 PC Port\n");
    printf("%-20s\tSkips the Peach and Castle intro when starting a new game.\n", "--skip-intro");
    printf("%-20s\tStarts the game in full screen mode.\n", "--fullscreen");
    printf("%-20s\tStarts the game in windowed mode.\n", "--windowed");
    printf("%-20s\tSaves the configuration file as CONFIGNAME.\n", "--configfile CONFIGNAME");
}

bool parse_cli_opts(int argc, char* argv[]) {
    // Initialize options with false values.
    memset(&gCLIOpts, 0, sizeof(gCLIOpts));

    if (strlen(argv[0]) > sizeof(gCLIOpts.BaseDirectory))
    {
        fprintf(stderr, "Directory name too long: %s\n", argv[0]);
        return FALSE;
    }

#if FOR_WINDOWS
    char *pch = strrchr(argv[0], '\\');
#else
    char *pch = strrchr(argv[0], '/');
#endif

    size_t last_index = pch-argv[0]+1;

    if (last_index < 1 || last_index > sizeof(gCLIOpts.BaseDirectory) || last_index > sizeof(gCLIOpts.ConfigFile))
    {
        fprintf(stderr, "Could not parse directory name. Got index: %d\n", last_index);
        return FALSE;
    }

    strncpy(gCLIOpts.BaseDirectory, argv[0], last_index);
    gCLIOpts.BaseDirectory[last_index] = '\0';

    if (strlen(gCLIOpts.BaseDirectory)+strlen(CONFIGFILE_DEFAULT) > sizeof(gCLIOpts.ConfigFile))
    {
        fprintf(stderr, "Config file path too long: %s%s\n", gCLIOpts.BaseDirectory, CONFIGFILE_DEFAULT);
        return FALSE;
    }

    strncpy(gCLIOpts.ConfigFile, gCLIOpts.BaseDirectory, sizeof(gCLIOpts.ConfigFile));
    strncpy(gCLIOpts.ConfigFile+strlen(gCLIOpts.ConfigFile), CONFIGFILE_DEFAULT, sizeof(gCLIOpts.ConfigFile));

    //printf("Base directory: %s\n", gCLIOpts.BaseDirectory);

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--skip-intro") == 0) // Skip Peach Intro
            gCLIOpts.SkipIntro = 1;

        else if (strcmp(argv[i], "--fullscreen") == 0) // Open game in fullscreen
            gCLIOpts.FullScreen = 1;

        else if (strcmp(argv[i], "--windowed") == 0) // Open game in windowed mode
            gCLIOpts.FullScreen = 2;

        else if (strcmp(argv[i], "--cheats") == 0) // Enable cheats menu
            Cheats.EnableCheats = true;

        // Print help
        else if (strcmp(argv[i], "--help") == 0) {
            print_help();
            game_exit();
        }

        else if (strcmp(argv[i], "--configfile") == 0) {
            if (i+1 < argc) {
                const unsigned int arglen = strlen(argv[i+1]);
                if (arglen >= sizeof(gCLIOpts.ConfigFile)) {
                    fprintf(stderr, "Configuration file supplied has a name too long.\n");
                    return FALSE;
                } else {
                    strncpy(gCLIOpts.ConfigFile, argv[i+1], arglen);
                    gCLIOpts.ConfigFile[arglen] = '\0';
                }
            }
        }
    }
}
