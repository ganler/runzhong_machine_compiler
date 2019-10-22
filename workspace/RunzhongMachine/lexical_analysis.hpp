//
// Created by ganler-Mac on 2019-10-10.
//

#pragma once

#include "utility.hpp"
#include "token.hpp"

#include <string_view>
#include <stdexcept>
#include <iostream>
#include <future>
#include <vector>
#include <thread>
#include <stack>
#include <cmath>
#include <array>

namespace rm
{

namespace trap_methods
{

/* @Trap method => Identifier or keyword */
template <typename C>
inline void id_or_kword_handler(std::string_view str, std::size_t &where, C &line_appender)
{
    /* while if void return int else */
    /* 因为首字母不相同，所以其实直接整词判断和dfa是等价的（而且可以用更长的寄存器进行&） */
    std::size_t word_begin = where;
    std::size_t word_end   = word_begin + 1;
    while(word_end != str.size() && (std::isalpha(str[word_end]) || std::isdigit(str[word_end])))
        ++word_end;
    std::string_view this_word = std::string_view(str.begin() + word_begin, word_end - word_begin);
    line_appender.emplace_back(IDENTIFIER, rm::unknown, word_begin, word_end);
    if(this_word == "while") // TODO: 优化 ~ 编译器哈希 （2ce的建议）
        line_appender.back().token_type = WHILE;
    else if(this_word == "if")
        line_appender.back().token_type = IF;
    else if(this_word == "void")
        line_appender.back().token_type = VOID;
    else if(this_word == "return")
        line_appender.back().token_type = RETURN;
    else if(this_word == "int")
        line_appender.back().token_type = INT;
    else if(this_word == "else")
        line_appender.back().token_type = ELSE;
    where = word_end;
}

/* @Trap method => Single Character */
template <typename C>
inline void singlec_handler(std::string_view str, std::size_t &where, C &line_appender)
{   /* $l~r:type */
    constexpr std::array<token_t, 6> token40_45 = {
            L_PARENTHESES, R_PARENTHESES, MUL_DIV, ADD_SUB, SPLIT, ADD_SUB
    };
    line_appender.emplace_back(token40_45[str[where]-'('], rm::unknown, where, where+1);
    if(str[where] == ';')
        line_appender.back().token_type = BOUNDS;
    else if(str[where] >= 46)
        line_appender.back().token_type = ((str[where] == '{') ? L_BRACE : R_BRACE);
    ++where;
}

/* @Trap method => '/' & '//' */
template <typename C>
inline void sbar_handler(std::string_view str, std::size_t &where, C &line_appender)
{
    if(where+1 != str.size() && str[where+1] == '/') // not end yet.
    { // "/**/" 类型的注释会在第一遍pass的时候去掉
        where = str.size(); // Just go.
        return;
    }
    // => matching '/'
    line_appender.emplace_back(MUL_DIV, rm::unknown, where, where+1);
    ++where;
}

/* @Trap method => '=' & '==' */
template <typename C>
inline void equal_handler(std::string_view str, std::size_t &where, C &line_appender)
{  // As '=' is assignment type.
    if(where+1 != str.size() && str[where+1] == '=')
    { // ==
        line_appender.emplace_back(COMPARE, rm::unknown, where, where+2);
        where += 2;
        return;
    }
    line_appender.emplace_back(ASSIGNMENT, rm::unknown, where, where+1);
    ++where;
}

/* @Trap method => number */
template <typename C>
inline void number_handler(std::string_view str, std::size_t &where, C &line_appender)
{
    std::size_t begin = where;
    while(where != str.size() && isdigit(str[++where]));
    line_appender.emplace_back(NUMBER, rm::unknown, begin, where);
}

template <typename C>
inline void operator_handler(std::string_view str, std::size_t &where, C &line_appender)
{
    std::size_t begin = where;
    where += ((where != str.size() && str[where+1] == '=') ? 2 : 1);
    line_appender.emplace_back(COMPARE, rm::unknown, begin, where);
}

enum trap_t
{
    DIRECT = 0,    // implemented
    ID_OR_KWORD,   // implemented
    SLANTING_BAR,  // implemented
    EQUAL,         // implemented
    OP,            // implemented
    NUM,           // implemented
    ERROR,         // implemented
    PASS           // implemented
};

inline std::array<trap_t, 128> trap_table;

const auto init_trap_methods = []()
{
    trap_table.fill(ERROR); // Things will be constexpr in C++20 ~ Wulaaaa!
    /*     DIRECT   */
    for (int i = 40; i < 46; ++i)
        trap_table[i] = DIRECT;
    trap_table[';'] = trap_table['{'] = trap_table['}'] = DIRECT;
    /* ID_OR_KWORD  */
    for(int i = 'a'; i <= 'z'; ++i)
        trap_table[i] = trap_table[i+'A'-'a'] = ID_OR_KWORD;
    /* SLANTING_BAR */ trap_table['/'] = SLANTING_BAR;
    /* EQUAL        */ trap_table['='] = EQUAL;
    /* OP           */ trap_table['>'] = trap_table['<'] = trap_table['!'] = OP;
    /* NUMBER       */
    for (int i = 0; i < 10; ++i)
        trap_table[i+'0'] = NUM;
    /* PASS         */ trap_table['\r'] = trap_table[' '] = trap_table['\t'] = PASS;
    return nullptr;
}();

}

// LEXCIAL ANALYZE
template <typename C>
static inline C lexcial_analyze_each_line(std::string_view str, std::size_t line_id)
{
    static_assert(
            std::is_same_v<typename std::remove_reference_t<C>::value_type, rm::token_word>,
            "[COMPILE ERROR] RM::LEXCIAL_ANALYZE can only return a container(STL) like `ContainerA<ContainerB<rm::token_word>>`");
    C ret;
    std::size_t index = 0;
    while(index < str.length())
    {
        /* $l~r:type */
        const trap_methods::trap_t trap_gate = trap_methods::trap_table[str[index]];
        switch(trap_gate)
        {
            case trap_methods::trap_t::ERROR:// ERROR HANDLER.
            RM_ERROR(
                    "[LEXICAL ERROR] \n\t=> @UNKNOWN CHARACTER: [ascii value : " +
                    std::to_string(str[index]) +
                    "]\n\t\t ~ NO. " +
                    std::to_string(index+1) +
                    " character in line " +
                    std::to_string(line_id) +
                    ":\t" +
                    str.data());
            case trap_methods::trap_t::PASS:
                ++index;
                break;
            default:
                constexpr std::array<void(*)(std::string_view, std::size_t&, C&), 6> dispatcher{
                        trap_methods::singlec_handler,
                        trap_methods::id_or_kword_handler,
                        trap_methods::sbar_handler,
                        trap_methods::equal_handler,
                        trap_methods::operator_handler,
                        trap_methods::number_handler
                };
                dispatcher[static_cast<int>(trap_gate)](str, index, ret); // GO!
        }
    }
    for(rm::token_word& x : ret)
        x.location.line = line_id;
    return ret;
}

template <typename C, typename S>
static std::remove_reference_t<C>
lexical_analyze_impl(
        const std::vector<bool> &check_table,
        const S &compile_src,      /* 源文件，每个str代表一行    */
        std::size_t begin,         /* 本function处理的起始位置   */
        std::size_t end,           /* 本function处理的终止位置+1 */
        std::size_t recur_num)
{
    using Container     = std::remove_reference_t<C>;
    using ContainerLine = typename Container::value_type;
    constexpr std::size_t max_work_sz = 64;
    const static std::size_t max_recur_num = std::log2(2 * std::thread::hardware_concurrency() + 2);
    std::size_t work_size = end - begin;
    if(work_size < max_work_sz || recur_num > max_recur_num)
    {
        Container ret;
        ret.reserve(work_size);
        for(int i = begin; i < end; ++i)
            if(check_table[i])
                if(auto result = lexcial_analyze_each_line<ContainerLine>(compile_src[i], i); !result.empty())
                    ret.push_back(std::move(result));
        return ret;
    }
    auto foo = std::async(lexical_analyze_impl <Container, S>, check_table, compile_src, begin, begin+work_size/2, recur_num+1);
    auto get2 = lexical_analyze_impl<Container, S>(check_table, compile_src, begin + work_size / 2, end, recur_num + 1);
    auto get1 = foo.get();
    get1.reserve(get1.size()+get2.size());
    for(auto&& x : get2)
        get1.push_back(std::move(x));
    return get1;
}

template <typename C>
void clean_all_star_comments(C&& src, std::vector<bool>& check_table)
{// 标记跨行"/**/" 以及消除不跨行的"/**/"
    std::stack<std::pair<int, int>> stk;
    for(std::size_t i=0; i<src.size(); ++i)
    {
        std::string& line = src[i];
        if(line.empty())
        {
            check_table[i] = false;
            continue;
        }
        for(std::size_t j=1; j<line.length(); ++j)
            if(line[j]=='*' && line[j-1]=='/')
                stk.emplace(i, j-1);
            else if(!stk.empty() && line[j]=='/' && line[j-1]=='*')
            {
                auto last = stk.top();
                stk.pop();
                for(int w = last.first+1; w<i; ++w)
                    check_table[w] = false;
                if(last.first == i)
                {
                    line.erase(line.begin()+last.second, line.begin()+j+1);
                    if(!line.empty())
                        j = last.second - 1;
                }
                else
                {
                    if(last.second == 0)
                        check_table[last.first] = false;
                    if(j + 1 == line.length())
                        check_table[i] = false;
                    src[last.first].erase(src[last.first].begin()+last.second, src[last.first].end());
                    line.erase(line.begin(), line.begin()+j+1);
                    j = 1;
                }
            }
    }
}

template <typename RetContainer = std::vector<std::vector<rm::token_word>>, typename C>
RetContainer // containerA<containerB<rm::token_word>>
lexical_analyze(C &&compile_src)
{
    static_assert(
            std::is_same_v<typename std::remove_reference_t<C>::value_type, std::string>,
            "[COMPILE ERROR] RM::LEXCIAL_ANALYZE can only adapt a container(STL) that contains `std::string`");
    std::vector<bool> lines2be_compiled(compile_src.size(), true);
    clean_all_star_comments(compile_src, lines2be_compiled);
    return lexical_analyze_impl<RetContainer>(lines2be_compiled, compile_src, 0, compile_src.size(), 1);
}

}