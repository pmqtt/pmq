#ifndef PMQ_SECURITY_HPP
#define PMQ_SECURITY_HPP
#include <cstdio>

namespace pmq::ring_zero {

    void clean_argv(int argc, char ***argv) {
        char **arg = *argv;
        for (std::size_t i = 0; i < argc; ++i) {
            arg[i] = nullptr;
        }
    }

    void clean_environment(char ***envp){

        for (char **env = *envp; *env != 0; env++)
        {
            *env = nullptr;
        }
    }

}

#endif //PMQ_SECURITY_HPP
