
#include <stdio.h>

#include "lily_api_embed.h"
#include "lily_api_alloc.h"
#include "lily_api_value.h"
#include "lily_api_msgbuf.h"

#define lily_return_string_raw(s,str) lily_return_string(s,lily_new_raw_string(str))
#define lily_variant_set_string_raw(v,idx,str) lily_variant_set_string(v, idx, lily_new_raw_string(str))
#define lily_list_set_string_raw(lv,idx,str) lily_list_set_string(lv,0,lily_new_raw_string(str))
#define lily_push_string_raw(s,str) lily_push_value(s,lily_new_value_of_string_lit(str))

#include "linenoise.h"
#include <errno.h>
#include <string.h>

/**
package linenoise

A Lily binding to the linenoise command-history library.

*/

static void return_error(lily_state *s)
{
    const char *return_value;
    if (errno == EAGAIN) {
        return_value = "cancel";
    } else
    if (errno == ENOENT) {
        return_value = "eof";
    } else {
        return_value = strerror(errno);
    }
    lily_instance_val *left_val = lily_new_left();
    lily_variant_set_string_raw(left_val, 0, return_value);
    lily_return_filled_variant(s,left_val);
}

/**
define linenoise(prompt: String): Either[String,String]

Get an input line, showing the given prompt

*/
void lily_linenoise__linenoise (lily_state *s)
{
    const char* prompt = lily_arg_string_raw(s,0);
    const char* return_value = linenoise(prompt);
    
    if (return_value) {    
        lily_instance_val *right_val = lily_new_right();
        lily_variant_set_string_raw(right_val, 0, return_value);
        lily_return_filled_variant(s,right_val);
        free((char*)return_value);
    } else {
        return_error(s);
    }
}
/**
define history_set_maxlen(n: Integer)

Set the maximum size of the history buffer
(which will be saved)

*/
void lily_linenoise__history_set_maxlen(lily_state *s)
{
    int n = lily_arg_integer(s,0);
    linenoiseHistorySetMaxLen(n);
    lily_return_unit(s);
}
/**
define history_add(line: String)

Add a line to command-history

*/
void lily_linenoise__history_add (lily_state *s)
{
    const char* line = lily_arg_string_raw(s,0);
    linenoiseHistoryAdd((char*)line);
    lily_return_unit(s);
}
/**
define history_load(file: String): Boolean

Reload command history from a file

*/
void lily_linenoise__history_load (lily_state *s)
{
    const char* file = lily_arg_string_raw(s,0);
    int res = linenoiseHistoryLoad((char*)file);
    lily_return_boolean(s,res==0 ? 1 : 0);    
}
/**
define history_save(file: String): Boolean

Save current history to a file


*/
void lily_linenoise__history_save (lily_state *s)
{
    const char* file = lily_arg_string_raw(s,0);
    int res = linenoiseHistorySave((char*)file);
    lily_return_boolean(s,res==0 ? 1 : 0);

}
#include "dyna_linenoise.h"
