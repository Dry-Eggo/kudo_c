#pragma once

#include <enum.h>
#include <token.h>
#include <types.h>

typedef struct expr_ expr_t;
typedef struct stmt_ stmt_t;

typedef struct expr_literal {
    span_t span;
    literal_kind_t kind;
    union {
	    const char* str_value; /* used for both identifers and any value that requires string storage */
	    long int_value;
	    bool bool_value;
	    char char_value;
	    float float_value;
    } lit;
} literal_t;

typedef struct stmt_vardecl {
    span_t span;
    var_decl_kind_t kind;    
    bool is_uninit;
    bool is_const;

    union {
        const char* identifer;
        expr_t*     pattern;
    };

    type_t* type;
    expr_t* rhs;
} vardecl_t;

typedef struct item_funcdef {
    bool is_extern;
    bool is_decl;
    
    span_t name_span;
    const char* name;
    const char* linkage_name;
    
    juve_vec_t*   params; // vector of param_t*
    expr_t*     body;
    type_t*     return_type;
} funcdef_t;

typedef struct expr_block {
    cjvec_t* statements;
} block_t;

struct expr_ {
    expr_kind_t kind;
    span_t span;
    union {
	    struct expr_literal literal;
	    struct expr_block   block;
    } data;
};

struct stmt_ {
    stmt_kind_t kind;
    span_t span;
    union {
	    struct stmt_vardecl vardecl;
	    struct expr_ expr;
    } data;
};

typedef struct {
    item_kind_t kind;
    span_t span;
    union {
	    struct item_funcdef fndef;
    } data;
} item_t;

expr_t* expr_make_block(cjvec_t* stmts);
expr_t* expr_make_literal_int(long value, span_t span);
expr_t* expr_make_identifier(const char* name, span_t span);
stmt_t* stmt_make_vardecl(vardecl_t vardecl, span_t);

item_t* item_make_fndef(funcdef_t fn, span_t span);
