#pragma once

#include <compiler.h>
#include <compiler_opt.h>
#include <c_backend.h>
#include <color.h>
#include <lexer.h>
#include <parser.h>
#include <semantics.h>

typedef enum {
    phase_lexer_k,
    phase_parser_k,
    phase_sema_k,
    phase_codegen_k
} compile_phase_t;


typedef struct {
    compile_options_t* options;
    compile_phase_t    phase;

    juve_vec_t*        source_lines;
    const char*        source;
    
    lexer_t*           lexer;
    parser_t*          parser;
    semantics_t*       sema;
    c_context_t*       c_ctx;
} driver_t;


driver_t* driver_new(const char* source, compile_options_t* opts);

void kudo_compile(compile_options_t* opts);
