#define MATE_IMPLEMENTATION
#include "mate.h"

i32 main()
{
    if (getenv("CCACHE_DIR") == NULL)
    {
        mkdir("build/.ccache", 0755);
        setenv("CCACHE_DIR", "build/.ccache", 0);
    }

    if (getenv("CCACHE_TEMPDIR") == NULL)
    {
        mkdir("build/.ccache/tmp", 0755);
        setenv("CCACHE_TEMPDIR", "build/.ccache/tmp", 0);
    }

    StartBuild();
    {
        Executable executable = CreateExecutable((ExecutableOptions){
            .output = "featherdb",
            .flags = "-Wall -g -std=c17 -D_GNU_SOURCE",
        });

        AddIncludePaths(executable, "./deps/c_std", "./deps/c_std/time");

        char *cStdSources[] = {
            "./deps/c_std/algorithm/algorithm.c",
            "./deps/c_std/array/array.c",
            "./deps/c_std/bigfloat/bigfloat.c",
            "./deps/c_std/bigint/bigint.c",
            "./deps/c_std/bitset/bitset.c",
            "./deps/c_std/cli/cli.c",
            "./deps/c_std/concurrent/concurrent.c",
            "./deps/c_std/concurrent/thread_pool.c",
            "./deps/c_std/config/config.c",
            "./deps/c_std/csv/csv.c",
            "./deps/c_std/date/date.c",
            "./deps/c_std/deque/deque.c",
            "./deps/c_std/encoding/encoding.c",
            "./deps/c_std/evalexpr/evalexpr.c",
            "./deps/c_std/file_io/file_reader.c",
            "./deps/c_std/file_io/file_writer.c",
            "./deps/c_std/fmt/fmt.c",
            "./deps/c_std/forward_list/forward_list.c",
            "./deps/c_std/hashmap/hashmap.c",
            "./deps/c_std/json/json.c",
            "./deps/c_std/list/list.c",
            "./deps/c_std/log/log.c",
            "./deps/c_std/map/map.c",
            "./deps/c_std/matrix/matrix.c",
            "./deps/c_std/network/http.c",
            "./deps/c_std/network/tcp.c",
            "./deps/c_std/network/udp.c",
            "./deps/c_std/priority_queue/priority_queue.c",
            "./deps/c_std/queue/queue.c",
            "./deps/c_std/random/random.c",
            "./deps/c_std/secrets/secrets.c",
            "./deps/c_std/sort/sort.c",
            "./deps/c_std/span/span.c",
            "./deps/c_std/stack/stack.c",
            "./deps/c_std/statistics/statistics.c",
            "./deps/c_std/string/std_string.c",
            "./deps/c_std/sysinfo/sysinfo.c",
            "./deps/c_std/time/std_time.c",
            "./deps/c_std/tuple/tuple.c",
            "./deps/c_std/vector/vector.c",
            "./deps/c_std/xml/xml.c",
        };

        AddFiles(executable, cStdSources);
        AddFile(executable, "./src/*.c");

        LinkSystemLibraries(executable, "m", "pthread", "ssl", "crypto", "gmp", "mpfr");

        InstallExecutable(executable);
        CreateCompileCommands(executable);

        RunCommand(executable.outputPath);
    }
    EndBuild();
}
