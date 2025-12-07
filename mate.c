#define MATE_IMPLEMENTATION
#include "mate.h"

i32 main() {
    StartBuild();
    {
        Executable executable = CreateExecutable((ExecutableOptions){
            .output = "featherdb",
            .flags = "-Wall -g"
        });

        AddFile(executable, "./src/*.c");

        InstallExecutable(executable);

        RunCommand(executable.outputPath);
    }
    EndBuild();
}