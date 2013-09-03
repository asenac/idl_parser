#ifndef IDL_GRAMMAR_HPP
#define IDL_GRAMMAR_HPP

#include "parser.hpp"
#include "idl_tokens.hpp"

namespace idl 
{
namespace grammar 
{

using namespace ::parser;
using namespace tokens;

enum primitive_types
{
    PT_UNSIGNED_SHORT,
    PT_UNSIGNED_LONG_LONG,
    PT_UNSIGNED_LONG,
    PT_LONG_DOUBLE,
    PT_LONG_LONG,
    PT_LONG,
    PT_OCTET,
    PT_CHAR,
    PT_SHORT,
    PT_FLOAT,
    PT_DOUBLE,
    PT_STRING,
    PT_WSTRING,
    PT_VOID,
    PT_NULL
};

template < typename Name, primitive_types type >
struct primitive_type : 
    semantic_rule < primitive_type < Name, type >, Name >
{
    template <typename S, typename match_pair>
    static inline void process_match (S& state, match_pair const& mp)
    {
        state.semantic_state().set_primitive_type(type);
    }
};

typedef or_<
       primitive_type < unsigned_short_t, PT_UNSIGNED_SHORT >,
       primitive_type < unsigned_long_long_t, PT_UNSIGNED_LONG_LONG >,
       primitive_type < unsigned_long_t, PT_UNSIGNED_LONG >,
       primitive_type < long_double_t, PT_LONG_DOUBLE >,
       primitive_type < long_long_t, PT_LONG_LONG >,
       primitive_type < long_t, PT_LONG >,
       primitive_type < octet_t, PT_OCTET >,
       or_ <
           primitive_type < void_t, PT_VOID >,
           primitive_type < char_t, PT_CHAR >,
           primitive_type < short_t, PT_SHORT >,
           primitive_type < float_t, PT_FLOAT >,
           primitive_type < double_t, PT_DOUBLE >,
           primitive_type < string_t, PT_STRING >,
           primitive_type < wstring_t, PT_WSTRING >
       >
    > primitive_types_rule;

enum flags
{
    FLAG_ONEWAY,
    FLAG_READONLY,
    FLAG_ABSTRACT,
    FLAG_IN,
    FLAG_OUT,
    FLAG_INOUT
};

template < typename Name, flags flag >
struct flag_ : semantic_rule < flag_ < Name, flag >, Name >
{
    template <typename S, typename match_pair>
    static inline void process_match (S& state, match_pair const& mp)
    {
        state.semantic_state().set_flag(flag);
    }
};

template < typename Name, flags flag >
struct optflag_ : opt_< seq_< flag_ < Name, flag >, space_ > >
{
};

template < typename rule >
struct data_ : 
    semantic_rule < data_ < rule >, rule >
{
    template <typename S, typename match_pair>
    static inline void process_match (S& state, match_pair const& mp)
    {
        state.semantic_state().set_data(state, mp);
    }
};

enum semantic_context_type
{
    CONTEXT_TRANSLATION_UNIT,
    CONTEXT_MODULE,
    CONTEXT_INTERFACE,
    CONTEXT_STRUCT,
    CONTEXT_STRUCT_FIELD,
    CONTEXT_ALIAS,
    CONTEXT_ARRAY,
    CONTEXT_ATTRIBUTE,
    CONTEXT_OPERATION,
    CONTEXT_PARAMETER,
    CONTEXT_ENUM,
    CONTEXT_SEQUENCE,
    CONTEXT_CONST,

    // Expressions
    CONTEXT_UNARY_EXPRESSION,
    CONTEXT_BINARY_EXPRESSION,
    CONTEXT_VALUE_EXPRESSION,
    CONTEXT_CONSTANT_REF
};

template < typename C0, semantic_context_type type >
struct semantic_context
{
    typedef semantic_rule < semantic_context, C0 > rule_t;

    template <typename S>
    static inline bool match (S& state)
    {
        state.semantic_state().new_context(type);

        bool res = rule_t::match(state);
        res ? 
            state.semantic_state().commit() : 
            state.semantic_state().rollback();

        return res;
    }

    template <typename S, typename match_pair>
    static inline void process_match (S& state, match_pair const& mp)
    {
        state.semantic_state().set_context_data(state, mp);
    }
};

struct identifier_ :
    semantic_rule < 
        identifier_,
        identifier_rule
    >
{
    template <typename S, typename match_pair>
    static inline void process_match (S& state, match_pair const& mp)
    {
        const std::string s (state.to_string(mp.first, mp.second));
        state.semantic_state().push_identifier(s);
    }
};

struct literal_ :
    semantic_rule < 
        literal_,
        identifier_rule
    >
{
    template <typename S, typename match_pair>
    static inline void process_match (S& state, match_pair const& mp)
    {
        const std::string s (state.to_string(mp.first, mp.second));
        state.semantic_state().push_literal(s);
    }
};

typedef
    data_< 
        fqn_rule
    >
    type_fqn_;

typedef 
    or_ < primitive_types_rule, type_fqn_ >
    type_rule;

// attribute

typedef
    seq_ < 
            optflag_<  readonly_t, FLAG_READONLY >,
            attribute_t,
            space_,
            type_rule,
            space_,
            identifier_
        > 
    attribute_rule;
typedef
    semantic_context < 
        attribute_rule,
        CONTEXT_ATTRIBUTE
    >
    attribute_;

// operation

typedef 
    or_ < 
            flag_ < inout_t, FLAG_INOUT >,   
            flag_ < in_t, FLAG_IN >, 
            flag_ < out_t, FLAG_OUT > 
        >
    direction_rule;
typedef 
    seq_ < 
            direction_rule, 
            space_,
            type_rule , 
            space_, 
            identifier_
         > 
    parameter_rule;
typedef semantic_context< parameter_rule, CONTEXT_PARAMETER > parameter_;

template < typename Item >
struct item_ :
    seq_ <
            spaces_,
            Item,
            spaces_
         >
{};

// useful for comma-separated lists
template < typename Item, typename Sep = comma >
struct list_ :
    or_ <
        seq_ <
                item_ < Item >,
                star_ < seq_ < Sep, item_ < Item > > >
             >, 
        spaces_ 
    >
{};

typedef list_ < parameter_ > parameter_list;

typedef
    seq_ < 
            optflag_< oneway_t, FLAG_ONEWAY >,
            type_rule,
            space_,
            identifier_,
            embrace_ < '(', parameter_list, ')' >
        > 
    operation_rule;

struct operation_ :
    semantic_context < 
        operation_rule,
        CONTEXT_OPERATION
    >
{
};

// constant
struct const_expr;
struct mult_expr;
struct add_expr;

typedef semantic_context< data_ < fqn_rule >, CONTEXT_CONSTANT_REF > 
    constant_ref_expr;

typedef semantic_context< 
                or_ <  string_rule, bool_, number_ >, 
                CONTEXT_VALUE_EXPRESSION 
            > value_expr;

typedef or_ < 
                value_expr, 
                constant_ref_expr,  
                embrace_ < '(', const_expr, ')' >
            > primary_expr;

typedef semantic_context< 
                seq_ <  
                        data_ < unary_operator >, spaces_, primary_expr 
                    >, 
                    CONTEXT_UNARY_EXPRESSION 
                > unary_expr;

template < typename Operator, typename Left, typename Right = Left >
struct binary_expr :
    semantic_context< 
        seq_ <  
            Left, 
            opt_ <
                seq_ <
                    spaces_, 
                    data_ < Operator >, 
                    spaces_, 
                    Right
                >
            >
        >, 
        CONTEXT_BINARY_EXPRESSION >
{};

struct mult_expr :  
    binary_expr < mult_operator, primary_expr, mult_expr > 
{};

struct add_expr :  
    binary_expr < add_operator, mult_expr > 
{};

struct shift_expr :  
    binary_expr < shift_operator, add_expr > 
{};

struct and_expr :  
    binary_expr < and_operator, shift_expr > 
{};

struct xor_expr :  
    binary_expr < xor_operator, and_expr > 
{};

struct or_expr :  
    binary_expr < or_operator, xor_expr > 
{};

struct const_expr : or_expr
{};

typedef seq_ < 
                const_t, 
                space_, 
                type_rule, 
                space_, 
                identifier_, 
                spaces_,
                seq_ < 
                        char_ < '=' >, 
                        spaces_, 
                        const_expr
                > 
        > 
        const_rule;

typedef semantic_context< const_rule, CONTEXT_CONST > const_;

// sequence

typedef 
    seq_< 
        sequence_t, 
        spaces_, 
        char_ < '<' >, 
        spaces_, 
        type_rule, 
        spaces_, 
        char_ < '>' > 
    > 
    sequence_rule;

typedef
    semantic_context < 
        sequence_rule,
        CONTEXT_SEQUENCE
    >
    sequence_;

// typedefs

struct typedef_type_rule : or_ < sequence_, type_rule > 
{};

typedef seq_ < typedef_t, space_, typedef_type_rule, space_, identifier_ > alias_rule;

struct alias_ :
    semantic_context < 
        alias_rule,
        CONTEXT_ALIAS
    >
{
};

typedef seq_ < 
            typedef_t, space_, type_rule, space_, identifier_, spaces_,
            plus_ < embrace_<'[', const_expr, ']' > >
        > array_rule;

struct array_ :
    semantic_context < 
        array_rule,
        CONTEXT_ARRAY
    >
{
};

// contexts

template < typename Statements, typename Sep = semicol >
struct context_: 
    seq_< 
            char_ < '{' >, 
            star_< seq_ < spaces_, Statements, spaces_, Sep >  >,
            spaces_,
            char_ < '}' > 
        >
{};

template < typename Name, 
           typename Body, 
           semantic_context_type type,
           typename Sep = semicol >
struct context_rule : 
    seq_< 
        Name, space_, 
        semantic_context < 
            seq_ <identifier_, spaces_, context_ < Body, Sep > >, 
            type 
        >
    >
{};

typedef 
    semantic_context < 
            seq_ < type_rule, space_, identifier_ >, 
            CONTEXT_STRUCT_FIELD 
        > 
    struct_field;

typedef struct_field struct_body; 
typedef context_rule< struct_t, struct_body, CONTEXT_STRUCT > struct_;

template < typename Name, 
           typename Body, 
           semantic_context_type type,
           typename Sep = comma >
struct list_context : 
    seq_< 
        Name, space_, 
        semantic_context < 
            seq_ < 
                identifier_, 
                spaces_, 
                char_ < '{' >, 
                list_ < Body, Sep >, 
                char_ < '}' > 
                >, 
            type 
        >
    >
{};

typedef 
    list_context < 
            enum_t, 
            literal_, 
            CONTEXT_ENUM
        > 
    enum_;

// Can it be an interface within an interface?
typedef or_< const_, array_, alias_, struct_, enum_ > contained_;

typedef or_< contained_, attribute_, operation_ > interface_body;
typedef 
    context_rule< 
            interface_t, 
            interface_body, 
            CONTEXT_INTERFACE 
        > 
    interface_;

struct module_;
typedef or_< module_, interface_, contained_ > module_body;
struct module_ : context_rule < module_t, module_body, CONTEXT_MODULE >
{};

typedef 
    seq_ < 
            spaces_, 
            or_ < module_, interface_, contained_ >, 
            spaces_, 
            semicol 
        > 
    statement_;

typedef 
    semantic_context < 
            seq_ < star_ < statement_ >, eof_ >, 
            CONTEXT_TRANSLATION_UNIT 
        >
    gram;

} // namespace grammar
} // namespace idl

#endif /* IDL_GRAMMAR_HPP */
