//
// Created by Johannes Moritz on 09.07.25.
//

#ifndef SCOPE_PIPELINE_HPP
#define SCOPE_PIPELINE_HPP
#include <string>
#include <vector>

namespace scop {
    class Scope_Pipeline {
    public:
        Scope_Pipeline(const std::string &vert_file_path, const std::string &frag_file_path);

    private:
        static std::vector<char> read_file(const std::string &file_path);

        void create_graphics_pipeline(const std::string &vert_file_path, const std::string &frag_file_path);
    };
} // scope

#endif //SCOPE_PIPELINE_HPP
