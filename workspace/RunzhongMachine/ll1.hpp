//
// Created by ganler-Mac on 2019-10-20.
//

#pragma once

#include "token.hpp"

#include <unordered_map>
#include <string_view>
#include <vector>
#include <stack>

namespace rm
{

static bool is_terminator(rm::token_t v)
{
    return v <= STOP;
}

static bool is_terminator(rm::token_word w)
{
    return is_terminator(w.token_type);
}

struct parse_node
{
    parse_node(rm::token_word w) : value(w) {}
    rm::token_word value;
    std::vector<std::unique_ptr<parse_node>> sons = {};
    bool terminator() const
    {
        return is_terminator(value);
    }
    template <typename StrC>
    void node_export(std::ostream& out, const StrC& container)
    {
        static int tabs = 0;
        ++tabs;
        const auto tabit = [&](){
            for (int i = 0; i < tabs; ++i)
                out << '\t';
        };
//        std::cout << value.token_type << '\n';
        tabit();
        out << "name:\"" << rm::readable_token_cast(value.token_type) << "\",\n";  // NAME
        tabit();
        out << "str:\"";                                                           // STR
        if(terminator())
        {
            auto [t, l, beg, end] = value.fully_unpack();
            std::string_view str(container[l].data()+beg, end-beg);
            out << str;
        }
        out << " \",\n";
        tabit();
        out << "NodeType:\"" << (terminator() ? "T" : "N-T") << "\"";
        if(!sons.empty())
        {
            out << ",\n";
            tabit();
            out << "children: [\n";
            ++tabs;
            for (auto&& ptr : sons)
            {
                tabit();
                out << "{\n";
                ptr->node_export(out, container);
                tabit();
                out << "}";
                if(ptr != sons.back())
                    out << ',';
                out << '\n';
            }
            --tabs;
            tabit();
            out << ']';
        }
        out << '\n';
        --tabs;
    }
};

static std::vector<rm::token_t > conduct(rm::token_t non, rm::token_t term)
{
    constexpr auto make_token_pair = [](rm::token_t l, rm::token_t r)
    {
        return ((uint16_t)l << 8) | (r);
    };
    auto sign = make_token_pair(non, term);
    using hashmap = std::unordered_map<decltype(sign), std::vector<rm::token_t >>;
    const static hashmap conduct_map {
        // TODO
            {make_token_pair(PROGRAM, INT), {DEF, PROGRAM}},
            {make_token_pair(PROGRAM, VOID), {DEF, PROGRAM}},
            {make_token_pair(PROGRAM, STOP), {}},

            {make_token_pair(DEF, INT), {INT, IDENTIFIER, DEF_}},
            {make_token_pair(DEF, VOID), {VOID, IDENTIFIER, FUNC_DEF}},

            {make_token_pair(DEF_, L_PARENTHESES), {FUNC_DEF}},
            {make_token_pair(DEF_, BOUNDS), {BOUNDS}},

            {make_token_pair(FUNC_DEF, L_PARENTHESES), {L_PARENTHESES, FARGLIST, R_PARENTHESES, L_BRACE, BLOCK, R_BRACE}},

            {make_token_pair(BLOCK, IDENTIFIER), {ASSIGN_EXP, BLOCK}},
            {make_token_pair(BLOCK, R_BRACE), {}},
            {make_token_pair(BLOCK, INT), {INTERNAL_DEF, BLOCK}},
            {make_token_pair(BLOCK, IF), {IF_EXP, BLOCK}},
            {make_token_pair(BLOCK, WHILE), {WHILE_EXP, BLOCK}},
            {make_token_pair(BLOCK, RETURN), {RET_EXP, BLOCK}},

            {make_token_pair(FARGLIST, INT), {NONE_EMPTY_FARG}},
            {make_token_pair(FARGLIST, VOID), {EMP_FARG}},

            {make_token_pair(INTERNAL_DEF, INT), {INT, IDENTIFIER, INTERNAL_DEF_}},

            {make_token_pair(INTERNAL_DEF_, SPLIT), {SPLIT, IDENTIFIER, INTERNAL_DEF_}},
            {make_token_pair(INTERNAL_DEF_, BOUNDS), {BOUNDS}}, // ZZZ's BUG fixed

            {make_token_pair(IF_EXP, IF), {IF, L_PARENTHESES, EXP, R_PARENTHESES, L_BRACE, BLOCK, R_BRACE, ELSE_EXP}},

            {make_token_pair(ELSE_EXP, IDENTIFIER), {}},
            {make_token_pair(ELSE_EXP, IF), {}},
            {make_token_pair(ELSE_EXP, ELSE), {ELSE, L_BRACE, BLOCK, R_BRACE}},
            {make_token_pair(ELSE_EXP, WHILE), {}},
            {make_token_pair(ELSE_EXP, RETURN), {}},
            {make_token_pair(ELSE_EXP, BOUNDS), {}},

            {make_token_pair(RET_EXP, RETURN), {RETURN, RETVAL}},

            {make_token_pair(RETVAL, NUMBER), {EXP}},
            {make_token_pair(RETVAL, IDENTIFIER), {EXP}},
            {make_token_pair(RETVAL, L_PARENTHESES), {EXP}},
            {make_token_pair(RETVAL, BOUNDS), {BOUNDS}}, // ZZZ's BUG fixed

            {make_token_pair(WHILE_EXP, WHILE), {WHILE, L_PARENTHESES, EXP, R_PARENTHESES, L_BRACE, BLOCK, R_BRACE}},

            {make_token_pair(ASSIGN_EXP, IDENTIFIER), {IDENTIFIER, ASSIGNMENT, EXP}},

            {make_token_pair(EXP, NUMBER), {ADDSUB_EXP, RELATION_EXP}},
            {make_token_pair(EXP, IDENTIFIER), {ADDSUB_EXP, RELATION_EXP}},
            {make_token_pair(EXP, L_PARENTHESES), {ADDSUB_EXP, RELATION_EXP}},

            {make_token_pair(RELATION_EXP, COMPARE), {COMPARE, ADDSUB_EXP}},
            {make_token_pair(RELATION_EXP, BOUNDS), {BOUNDS}}, // ZZZ's BUG fixed

            {make_token_pair(ADDSUB_EXP, NUMBER), {TERM, ADDSUB_OP}},
            {make_token_pair(ADDSUB_EXP, IDENTIFIER), {TERM, ADDSUB_OP}},
            {make_token_pair(ADDSUB_EXP, L_PARENTHESES), {TERM, ADDSUB_OP}},

            {make_token_pair(ADDSUB_OP, COMPARE), {}},
            {make_token_pair(ADDSUB_OP, ADD_SUB), {ADD_SUB, TERM, ADDSUB_OP}},  // ZZZ's BUG fixed
            {make_token_pair(ADDSUB_OP, BOUNDS), {}},

            {make_token_pair(TERM, NUMBER), {FACTOR, MULDIV_OP}},
            {make_token_pair(TERM, IDENTIFIER), {FACTOR, MULDIV_OP}},
            {make_token_pair(TERM, L_PARENTHESES), {FACTOR, MULDIV_OP}},

            {make_token_pair(MULDIV_OP, COMPARE), {}},
            {make_token_pair(MULDIV_OP, ADD_SUB), {}}, // ZZZ's BUG fixed
            {make_token_pair(MULDIV_OP, MUL_DIV), {MUL_DIV, FACTOR, MULDIV_OP}}, // ZZZ's BUG fixed
            {make_token_pair(MULDIV_OP, BOUNDS), {}},

            {make_token_pair(FACTOR, NUMBER), {NUMBER}},
            {make_token_pair(FACTOR, IDENTIFIER), {IDENTIFIER, SUFFIX}},
            {make_token_pair(FACTOR, L_PARENTHESES), {L_PARENTHESES, EXP, R_PARENTHESES}},

            {make_token_pair(SUFFIX, COMPARE), {}},
            {make_token_pair(SUFFIX, L_PARENTHESES), {L_PARENTHESES, VARGLIST, R_PARENTHESES}},
            {make_token_pair(SUFFIX, ADD_SUB), {}},
            {make_token_pair(SUFFIX, MUL_DIV), {}},
            {make_token_pair(SUFFIX, BOUNDS), {}},

            {make_token_pair(VARGLIST, NUMBER), {EXP, OTHER_VARGS}},
            {make_token_pair(VARGLIST, IDENTIFIER), {EXP, OTHER_VARGS}},
            {make_token_pair(VARGLIST, L_PARENTHESES), {EXP, OTHER_VARGS}},
            {make_token_pair(VARGLIST, VOID), {VOID}},

            {make_token_pair(OTHER_VARGS, R_PARENTHESES), {}},
            {make_token_pair(OTHER_VARGS, SPLIT), {SPLIT, EXP, OTHER_VARGS}},

            {make_token_pair(NONE_EMPTY_FARG, INT), {INT, IDENTIFIER, OTHER_FARGS}},
            {make_token_pair(OTHER_FARGS, R_PARENTHESES), {}},
            {make_token_pair(OTHER_FARGS, SPLIT), {SPLIT, EXP, OTHER_FARGS}},

            {make_token_pair(EMP_FARG, VOID), {VOID}},
    }; // FD | GD ~ 内部声明 语句块 |  语句 语句块
    const auto it = conduct_map.find(sign);
    if(it == conduct_map.cend())
    {
        std::string error_message("SYNTAX ANALYSIS FAILED ~ CANNOT CONDUCT {");
        error_message += readable_token_cast(non);
        error_message += ", ";
        error_message += readable_token_cast(term);
        error_message += "}";
        RM_ERROR(error_message);
    }

//    std::cout << '\t' << non << " via~ " << term << " -> ";
//    for(auto&& x : it->second)
//        std::cout << x << ' ';
//    std::cout << std::endl;

    return it->second;
}


template <typename Container>
std::unique_ptr<rm::parse_node> ll1_parse(Container&& remaining_inp)
{// ContainerA<ContainerB<rm::token_word > >
    if(remaining_inp.empty())
    RM_ERROR("EMPTY TOKEN STREAM, NOTHING TO ANALYZE.");

    remaining_inp.back().push_back({STOP, unknown, unknown, unknown});
    std::stack<rm::token_t > parse_stack ({token_t ::STOP, token_t ::PROGRAM});

    auto root = std::make_unique<rm::parse_node >(token_t::PROGRAM);
    std::stack< rm::parse_node*> non_term_stack;
    non_term_stack.push(root.get());

    const auto endit = remaining_inp.back().end();
    auto curit = remaining_inp.front().begin();
    auto token_line = remaining_inp.begin();
    bool finished = false;
    while(!finished)
    {
        auto is_finished = [&](){
            if(parse_stack.empty())
            {
                if(token_line == remaining_inp.end()) // endl
                    finished = true; // SUCCESS;
                else
                RM_ERROR("SYNTAX ANALYSIS FAILED!");
            }
        };
        auto incre = [&](){
            if(curit+1 == token_line->end())  // increment;
            {
                ++token_line;
                if(token_line != remaining_inp.end())
                    curit = token_line->begin();
            }
            else
                ++curit;
            is_finished();
        };
        if(!is_terminator(parse_stack.top())) // Stack 的头 ~ Non-terminator 推导
        {
//            std::cout << parse_stack.top() << '\t' <<  curit->token_type << '\n';
            auto conducted = conduct(parse_stack.top(), curit->token_type);
            parse_stack.pop();
            rm::parse_node* cur_parent = non_term_stack.top();
            non_term_stack.pop();

            std::for_each(conducted.rbegin(), conducted.rend(), [&](auto&& v){
                parse_stack.push(v);
                cur_parent->sons.emplace_back(new rm::parse_node(v));
                non_term_stack.push(cur_parent->sons.back().get());
            });
        }
        else if(parse_stack.top() == curit->token_type) // Match
        {
//            std::cout << "\tMerge: " << parse_stack.top() << '\n';
            if(curit->token_type != STOP)
            {
                *non_term_stack.top() = *curit;
                non_term_stack.pop();
            }
            parse_stack.pop();
            incre();
        }
        else
        {
            RM_ASSERT(!parse_stack.empty());
            std::cerr << "REMAINS IN THE STACK TOP: " << parse_stack.top() << '\n';
            std::cerr << (token_line+1)->front().token_type << '\n';
            RM_ASSERT(curit != token_line->cend());
            std::string error_message("SYNTAX ANALYSIS FAILED ~ CANNOT MATCH {");
            error_message += readable_token_cast(parse_stack.top());
            error_message += ", ";
            error_message += readable_token_cast(curit->token_type);
            error_message += "}";
            RM_ERROR(error_message);
        }
    }
    return root;
}

void traverse(parse_node* root)
{
    std::cout << root->value.token_type << '\n';
    for(auto&& x : root->sons)
        traverse(x.get());
}

}