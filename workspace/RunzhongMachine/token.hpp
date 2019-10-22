//
// Created by ganler-Mac on 2019-10-17.
//

#pragma once

#include <utility>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <array>

#define RM_ERROR(MESSAGE)\
{\
    std::cerr                                               \
        << ">>> COMPILE ERROR -> in line "                  \
        << __LINE__ << ": @" << MESSAGE                     \
        << "\n\t-> at " << __PRETTY_FUNCTION__ << std::endl;\
    std::exit(-1);                                          \
}

#define RM_ASSERT(X)\
{\
    if(!(X))\
        RM_ERROR("RM_ASSERT FAILED: "#X);\
}

namespace rm
{

constexpr std::size_t unknown = std::numeric_limits<std::size_t >::max();

struct word
{
    std::size_t line;
    std::size_t begin;
    std::size_t end;
    word(std::size_t a, std::size_t b, std::size_t c) : line(a), begin(b), end(c) {}
    decltype(auto) unpack() const
    {
        return std::make_tuple(line, begin, end);
    }
};

enum token_t : uint8_t
{
    NUMBER        = 'a',
    COMPARE       = 'b',
    IDENTIFIER    = 'c',
    ASSIGNMENT    = 'd',
    ADD_SUB       = 'e',
    BOUNDS        = 'f',
    L_PARENTHESES = 'g',
    R_PARENTHESES = 'h',
    L_BRACE       = 'i',
    R_BRACE       = 'j',
    SPLIT         = 'k',
    WHILE         = 'l',
    IF            = 'm',
    VOID          = 'n',
    RETURN        = 'o',
    INT           = 'p',
    ELSE          = 'q',
    MUL_DIV       = 'r',
    STOP  , // #
    PROGRAM  ,
    DEF     ,
    DEF_,
    FUNC_DEF  ,
    BLOCK   ,
    FARGLIST   ,
    INTERNAL_DEF,
    INTERNAL_DEF_,
    IF_EXP,
    ELSE_EXP,
    RET_EXP,
    RETVAL,
    WHILE_EXP,
    ASSIGN_EXP,
    EXP,
    RELATION_EXP,
    ADDSUB_EXP,
    ADDSUB_OP,
    TERM,
    MULDIV_OP,
    FACTOR,
    SUFFIX,
    VARGLIST,
    OTHER_VARGS,
    NONE_EMPTY_FARG,
    OTHER_FARGS,
    EMP_FARG,
    UNKNOWN
};

std::string_view readable_token_cast(token_t t)
{
    constexpr std::array<std::string_view, (UNKNOWN-NUMBER)+1> print_table{
            "数字", "比较运算", "标识符", "赋值符", "加减运算符",
            ";", "(", ")", "{", "}", ",", "while", "if", "void", "return", "int", "else", "乘除运算符",
            "#",
            "程序", "声明", "声明1", "函数声明", "语句块", "形参列表", "内部声明",
            "内部声明1", "if语句", "else语句", "return语句", "返回值", "while语句",
            "赋值语句", "表达式", "关系式", "加减表达式", "加减操作", "项", "乘除操作", "因子",
            "后缀", "实参列表", "其余实参", "非空形参", "其他形参", "空形参", "UNKNOW"
    };
    return print_table[t-'a'];
}

char token_color_style(token_t t)
{
    constexpr std::array<char, (UNKNOWN-NUMBER)+1> print_table{
            '0', '1', '2', '3', '4', '5', '6', '6', '7', '7', '8', '9', '9', '9', '9', '9', '9',
            '4',
            '#',
            'S', 'e', 'T', 't', 'F', '?'
    };
    return print_table[t-'a'];
}

std::ostream& operator<<(std::ostream& out, token_t t)
{
    return out << readable_token_cast(t);
}

struct token_word
{
    rm::token_t    token_type;
    rm::word       location;
    template <typename ... Args>
        token_word(token_t x, Args&& ... args)
        : token_type(x), location(std::forward<Args>(args)...) {}
    token_word() : token_type(UNKNOWN), location(unknown, unknown, unknown) {}
    token_word(token_t t) : token_type(t), location(unknown, unknown, unknown) {}
    decltype(auto) unpack() const
    {
        return std::make_tuple(token_type, location);
    }
    decltype(auto) fully_unpack() const
    {
        auto [x, y, z] = location.unpack();
        return std::make_tuple(token_type, x, y, z);
    }
};

}