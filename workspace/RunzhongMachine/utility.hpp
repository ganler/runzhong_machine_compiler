//
// Created by ganler-Mac on 2019-10-15.
//

#pragma once

#include "token.hpp"
#include "ll1.hpp"

#include <deque>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/* Just some template magic :)  */

namespace rm
{

template <typename ... Args>
bool all(Args&& ... args) noexcept
{
    return (args && ...);
}

template <typename ... Args>
bool any(Args&& ... args) noexcept
{
    return (args || ...);
}

template <typename T, typename ... Args>
bool equal_all(const T& l, Args&& ... args) noexcept
{
    return ((l == args) && ... );
}

template <typename T, typename ... Args>
bool equal_any(const T& l, Args&& ... args) noexcept
{
    return ((l == args) || ... );
}

inline std::vector<std::string> get_src(std::string_view sv)
{
    std::vector<std::string> src; // NRVO
    std::ifstream code(sv.data());
    if(!code.is_open())
        RM_ERROR("INVALID FILE PATH!");
    do{
        src.emplace_back();
    } while(std::getline(code, src.back()));
    return src;
}

template <typename C>
void make_src(C&& container, std::string_view sv)
{
    std::ofstream out(sv.data());
    for(auto && x : container)
        out << x << '\n';
}


template <typename C>
struct exporter
{
    const C&                            data_ref;
    std::unique_ptr<rm::parse_node>     parse_root = nullptr;
    explicit constexpr exporter(const C& ref)
            : data_ref(ref) {}
    void lexcial(std::string_view fname) const
    {
        // C ~ ContainerA<ContainerB<rm::token_word>>
        std::ofstream out(fname.data());
        const auto& data = data_ref;
        char str_r[] = R"(, "type":X},)";
        out << "{\n\t\"report\":[\n";
        for(std::size_t l = 0; l < data.size(); ++l)
            for(auto&& v : data[l])
            {
                auto [t, line, beg, end] = v.fully_unpack();
//                std::cout << t << ' ' << line << ' ' << beg << ' ' << end << '\n';
                // {"line":0,"pos":0,"type":2},
                auto str_l = "\t\t" + (R"({"line":)" + std::to_string(line) + R"(, "pos":)");
                str_r[9] = rm::token_color_style(t);
                for(std::size_t i=beg; i<end; ++i)
                    if(l == data.size() - 1 && i == end-1)
                    {
                        str_r[11] = '\n';
                        out << str_l << std::to_string(i) << str_r;
                    }
                    else
                        out << str_l << std::to_string(i) << str_r << '\n';
            }
        out << "\t]\n}\n";
    }
    template <typename StrC>
    void syntax(std::string_view fname, const StrC &container) const
    {
        std::ofstream out(fname.data());
        out << "export default {\n";
        parse_root->node_export(out, container);
        out << '}';
    }

};

}