/********************************************************************** 

    Golgotha Forever - A portable, free 3D strategy and FPS game.
    Copyright (C) 1999 Golgotha Forever Developers

    Sources contained in this distribution were derived from
    Crack Dot Com's public release of Golgotha which can be
    found here:  http://www.crack.com

    All changes and new works are licensed under the GPL:

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    For the full license, see COPYING.

***********************************************************************/
 

/*! \file 
    \brief Include file for the lisp subsystem

     This file declares various functions that can be used to evaluate 
     lisp expressions in lisp enviroments. Ranging from mostly oriented
     towards debugging to production use, these functions forms the basis
     of the lisp interprenter.
*/

#ifndef LI_LISP_HH
#define LI_LISP_HH

#include "lisp/li_types.hh"
#include "lisp/li_optr.hh"

class i4_status_class;

/** Will print the value of o to the stream i4_debug.
    o is not evaluated. Primarily used for debugging.
    @param o A lisp object. If valid it will be printed, 
             otherwise an error message will be printed.
    @see li_read_eval, li_print
*/
void lip(li_object *o);

// this is the function added into the system, arguments are evaluated

// /////////////////////////////////////////////////////////////////////////////
//
// li_print, li_get_expression & li_eval
/** Evaluates and print a li_object.
    Will evaluate a object or list of objects, print each of them using lip(),
    and finally return the value of the last expression evaluated.
    @param o A lisp object or list of lisp objects. 
    @param env An optional environment to evaluate in.
    @return The value of the evaluation of o.
    @see li_read_eval, lip
*/
li_object *li_print(li_object *o, li_environment *env=0);

/** Retrieves a lisp expression from the character string s.    
    @param s A character string, containing one or more valid lisp expressions.
    @param env A lisp environment. (Not sure what its role is).
    @return A lisp expression or an error if no valid expression could 
            be obtained.
*/
li_object *li_get_expression(char *&s, li_environment *env);

/** Evals a lisp expression or list of lisp expressions.
    @param expression A lisp expression or list of expressions to be evaluated.
    @param env Optional environment to evaluate expression in.
    @return The value of the expression or the value of the first expression in 
            the list.(?)
*/
li_object *li_eval(li_object *expression, li_environment *env=0);

////////////////////////////////////////////////////////////////////////////////
//
// li_call

/** Calls a lisp function by name.
    If an environment is supplied, the function is evaluated in that 
    environment.
    @param fun_name   Refers to the name of the function to be evaluated.
    @param params     List of arguments to the function. May be 0 if the 
                      function does not take any arguments
    @param env    Optional Lisp environment.
    @return If succesfull li_call will return the value returned by the 
            function in a li_object. Otherwise 0 is returned.
    @see    i4/lisp.hh. The other li_call call.
*/
li_object *li_call(char *fun_name, li_object *params=0, li_environment *env=0);

/** Calls a lisp function by symbol.
    If an environment is supplied, the function is evaluated in that 
    environment.
    @param fun_name   Refers to the name of the function to be evaluated.
    @param params     List of arguments to the function. May be 0 if the 
                      function does not take any arguments
    @param env    Optional Lisp environment.
    @return If succesfull li_call will return the value returned by the 
            function in a li_object. Otherwise 0 is returned.
    @see    i4/lisp.hh. The other li_call call.
*/
li_object *li_call(li_symbol *fun_name, li_object *params=0, 
                   li_environment *env=0);

/** Used to add C++ functions to the lisp system.
    This function can be used to make userwritten C++ functions to the 
    lisp system, thereby making them accesible to the lisp interprenter.
    @param sym A lisp symbol with name of the function as seen from the 
               lisp system.(?)
    @param fun The actual C++ function to make accesible to the lisp system.
    @param env Optional environment to publish the function in. If not present
               (or 0) the function will be accesible globally.
    @see The other li_add_function's. li_automatic_add_function.
*/
void li_add_function(li_symbol *sym, li_function_type fun, 
                     li_environment *env=0); 

/** Used to add C++ functions to the lisp system.
    This function can be used to make userwritten C++ functions to the 
    lisp system, thereby making them accesible to the lisp interprenter.
    @param sym_name A string with the name of the function as seen from the 
               lisp system.
    @param fun The actual C++ function to make accesible to the lisp system.
    @param env Optional environment to publish the function in. If not present
               (or 0) the function will be accesible globally.
    @see The other li_add_function's. li_automatic_add_function.
*/
void li_add_function(char *sym_name, li_function_type fun, 
                     li_environment *env=0);

/** Lookup and return a an already existing lisp object.
    Will perform a binary search through the symboltable, and return the object
    with called 'name'. If it is not found 0 is returned.
    @param name Name of the symbol to look up.
    @return 0 if symbol is not found, otherwise the symbol is returned.
    @see The li_get_symbol calls.
*/
li_symbol *li_find_symbol(const char *name); 

/** Lookup and return a lisp object.
    Will perform a binary search through the symboltable, and return the object
    with called 'name'. If it is not found a new object is created.
    @param name Name of the symbol to look up.
    @return A symbol with the name is returned.
    @see The other li_get_symbol call, li_find_symbol.
*/
li_symbol *li_get_symbol(const char *name);  

// if cache_to is 0, then the symbol is found and stored there, otherwise cache_to is returned
/** */
/** Lookup and return a cached lisp object.
    If cache_to is not 0, this will be returned. Otherwise a lookup in the 
    global symboltable will be performed, using li_get_symbol().
    @param name Name of the symbol to look up.
    @param cache_to A lisp symbol or 0.
    @return A symbol with the name is returned.
    @see The other li_get_symbol call, li_find_symbol.
*/
li_symbol *li_get_symbol(char *name, li_symbol *&cache_to);

// /////////////////////////////////////////////////////////////////////////////
//
// li_get_value & li_set_value

/** Get the value of a symbol.
    If an environment is supplied, the value will be from the symbol in that
    environment. Otherwise the symbols global value is used.
    
    @param sym   Refers to the symbol to get.
    @param env   Optional Lisp environment.

    @return If succesfull li_call will return the symbols value. Unknown symbols
            may give runtime errors.
    @see    li_set_value. The other li_get_value call.
*/
inline li_object *li_get_value(li_symbol *sym, li_environment *env=0)
{ 
  if (env)
    return env->value(sym);
  else return sym->value();
}

/** Get the value of a symbol, using the symbols name.
    If an environment is supplied, the value will be from the symbol in that
    environment. Otherwise the symbols global value is used.
    @param sym   Refers to the symbols name.
    @param env   Optional Lisp environment.
    @return If succesfull li_call will return the symbols value. Unknown symbols
            may give runtime errors.
    @see    li_set_value. The other li_get_value call.
*/
inline li_object *li_get_value(char *sym, li_environment *env=0) 
{ return li_get_value(li_get_symbol(sym),env); }

/** Set the value of a symbol.
    If an enviroment is supplied, the symbol in the enviroment will have its
    value updated. Otherwise, the symbols global value will be updated,
    @param sym Refers to the symbol which will have its value set.
    @param env Optional Lisp enviroment.
*/
inline void li_set_value(li_symbol *sym, li_object *value, li_environment *env=0)
{ 
  if (env)
    env->set_value(sym, value);
  else sym->set_value(value);  
}

/** Set the value of a symbol.
    If an enviroment is supplied, the symbol in the enviroment will have its
    value updated. Otherwise, the symbols global value will be updated,
    @param sym Name of the symbol which will have its value set.
    @param env Optional Lisp enviroment.
*/
inline void li_set_value(char *sym, li_object *value, li_environment *env=0) 
{ li_set_value(li_get_symbol(sym),value,env); }
  

// gets a function for a symbol.  Checks to see if it has a local value in the environment
// first

/** Not documented.
*/
li_object *li_get_fun(li_symbol *sym, li_environment *env);

/** Not documented
*/
li_object *li_get_fun(char *sym, li_environment *env);
  
// return 0 if type doesn't exsist

/** Not documented
*/
li_object *li_new(char *type_name, li_object *params=0, li_environment *env=0);  
/** Not documented
*/
li_object *li_new(int type, li_object *params=0, li_environment *env=0);  

/** Get the first element in a list.

    CAR comes from old LISP machines which stands for 
    Contents of the Address Register. Though lisp machines aren't used anymore,
    the term has stuck around.
    
    @param      o List
    @param      env Lisp environment.
    @return     The first element in the list.
    @see        i4/lisp.hh. li_cdr.
*/
inline li_object *li_car(li_object *o, li_environment *env) { return li_list::get(o,env)->data(); }

/** Drop the first element in a list.

    Returns the list, exclusive the first element.

    CDR = Contents of the Destination Register.  or better know by "C" 
    people as ->next
    
    @param      o List.
    @param      env Lisp environment.
    @return     All but the first element of the list.
    @see        i4/lisp.hh. li_car.
*/
inline li_object *li_cdr(li_object *o, li_environment *env) { return li_list::get(o,env)->next(); }

/** Evaluate argument to a i4_bool.
    This function returns a i4_bool type, or raises an error.
    @param o Object to evaluate to i4_T or i4_F.
    @param env environment to lookup object in.
    @return If o is a bool lisp object, its value is returned as a i4_bool. 
            If is is defined as T i4_T is returned.
            If it is not defined, or defined as nil, i4_F is returned.
            If it is defined, but not as a valid lisp object, an error is 
            returned. 
    @see li_get_float, li_get_int, li_get_string.
*/
i4_bool    li_get_bool(li_object *o, li_environment *env);   // return i4_T if o is 'T,  i4_F if it is 'F or nil

/** Evaluate argument to a float
    This function returns a float value, or an error.
    @param o Object to evaluate to a float.
    @param env environment to lookup object in.
    @return If o is a LI_INT it will be converted to a LI_FLOAT.
            If o is not a LI_INT or LI_FLOAT an error will occur(?).
            The value of the object will be returned if no error.
    @see li_get_bool, li_get_int, li_get_string.
*/
float      li_get_float(li_object *o, li_environment *env);  // will convert int to float

/** Evaluate argument to a int.
    This function returns a int value, or an error.
    @param o Object to evaluate to a int.
    @param env environment to lookup object in.
    @return If o is a LI_FLOAT it will be converted to a LI_INT.
            If o is not a LI_INT or LI_FLOAT an error will occur(?)
            The value of the object will be returned if no error.
    @see li_get_bool, li_get_float, li_get_string.
*/
int        li_get_int(li_object *o, li_environment *env);    // will convert float to int

/** Evaluate argument to a string.
    This function returns a string value, or an error.
    @param o Object to evaluate to a string.
    @param env environment to lookup object in.
    @return If o is not a string an error will occur(?)
            The value of the object will be returned if no error.
    @see li_get_bool, li_get_int, li_get_float.
*/
char      *li_get_string(li_object *o, li_environment *env); 

/** Is object a number?

    Determines if a given object is a number, ie. either a LI_INT or a LI_FLOAT 
    
    @param      o Lisp Object
    @return     i4_T if o is either of type LI_INT or LI_FLOAT, i4_F otherwise.
    @see        i4/lisp.hh.
*/
i4_bool    li_is_number(li_object *o, li_environment *env);  // returns true if item is LI_INT or LI_FLOAT

// these function return the 1st, 2nd...  item in a list first=li_cdr(o), second=li_cdr(li_cdr(o))
/** Get the first element in a list.

    Does what li_car(o) does.
    
    @param      o List
    @param      env Lisp environment.
    @return     The first element in the list.
    @see        i4/lisp.hh. li_car, li_second, li_third, li_fourth, 
                li_fifth, li_nth
*/
li_object  *li_first(li_object *o, li_environment *env);
/** Get the second element in a list.

    Does what li_car(li_cdr(o)) does, although a bit more effecient.
    
    @param      o List
    @param      env Lisp environment.
    @return     The second element in the list.
    @see        i4/lisp.hh. li_car, li_first, li_third, li_fourth, 
                li_fifth, li_nth
*/
li_object  *li_second(li_object *o, li_environment *env);
/** Get the third element in a list.

    Calls li_car(li_cdr(li_cdr(o))).
    
    @param      o List
    @param      env Lisp environment.
    @return     The third element in the list.
    @see        i4/lisp.hh. li_car, li_first, li_second, li_fourth, 
                li_fifth, li_nth
*/
li_object  *li_third(li_object *o, li_environment *env);
/** Get the fourth element in a list.

    Calls li_car(li_cdr(li_cdr(li_cdr(o)))).
    
    @param      o List
    @param      env Lisp environment.
    @return     The fourth element in the list.
    @see        i4/lisp.hh. li_car, li_first, li_second, li_third, 
                li_fifth, li_nth
*/
li_object  *li_fourth(li_object *o, li_environment *env);
/** Get the fifth element in a list.

    Calls li_car(li_cdr(li_cdr(li_cdr(li_cdr(o))))).
    
    @param      o List
    @param      env Lisp environment.
    @return     The fifth element in the list.
    @see        i4/lisp.hh. li_car, li_first, li_second, li_third, li_fourth, 
                li_nth
*/
li_object  *li_fifth(li_object *o, li_environment *env);
/** Get the nth element in a list.

    li_nth(o, 0, env) is the same as li_car(o, env).

    @param      o List
    @param      x The number of the element to return, starting at 0.
    @param      env Lisp environment.
    @return     The (x+1)th element in the list.
    @see        i4/lisp.hh. li_car, li_first, li_second, li_third, li_fourth, 
                li_nth
*/
li_object  *li_nth(li_object *o, int x, li_environment *env);

/** li_make_list takes a variable array of arguments (null terminated) and 
    return a list of those. 
    @param first First element in list
    @param dotdotdot Additional elements to the list. Rememeber to 0 terminate.
    @return A list of the elements. 
    \code
      // Example
      li_make_list(new li_int(4), new li_string("hello"), 0);
    \endcode
*/

li_list   *li_make_list(li_object *first, ...);

/** Length of a list.
    Calculates the lenght of a list by traversing it and counting elements.
    
    @param      o Lisp List
    @param      env Enviroment to perform operation in
    @return     The length of the list. If o is not a list, 0 is returned 
    @see        i4/lisp.hh.
*/
int        li_length(li_object *o, li_environment *env);

/** Loads one or more lisp expressions from a list of files and
    evaluates the expressions.
    
    @param name   A list of li_strings which are loaded sequentially.
    @param env    Optional Lisp environment.
    @return Either 0 or an Lisp Object representing the 
    value of the last expression.
    @see         The other li_load calls.
*/
li_object *li_load(li_object *name, li_environment *env=0);

/** Loads one or more lisp expressions from a list of files and
    evaluates the expressions.
    
    @param name   A list of li_strings which are loaded sequentially.
    @param env    Optional Lisp environment.
    @param status Optional i4 status class.
    @return       Either 0 or an Lisp Object representing the value of the last expression.
    @see          The other li_load calls.
*/
li_object *li_load(li_object *name, li_environment *env, i4_status_class *status);

/** Loads one or more lisp expressions from a file and 
    evaluates the expressions.
    
    @param filename   A filename.
    @param env        Optional Lisp environment.
    @param status     Optional i4 status class.
    @return Either 0 or an Lisp Object representing the 
    value of the last expression.
    @see    i4/lisp.hh. The other li_load calls.
*/
li_object *li_load(char *filename, li_environment *env=0, i4_status_class *status=0);

/** Loads one or more lisp expressions from a i4_file_class and evaluates the expressions.
    
    \param fp     A i4 file descriptor.
    \param env    Optional Lisp environment.
    \param status Optional i4 status class.
    \return Either 0 or an Lisp Object representing the value of the last expression.
    \see    i4/lisp.hh. The other li_load calls.
*/
li_object *li_load(i4_file_class *fp, li_environment *env=0, i4_status_class *status=0);

/** Reads an expression from i4_debug and prints the result of evaluation 
    to i4_debug.

    \param o Unused - set o 0
    \param env Optional environment. If present evaluation will take place 
               in this environment.
    \return Either 0 (end of input stream) or the value of the last expression 
            evaluated.

    \code 
       printf();
    \endcode
*/
li_object *li_read_eval(li_object *o, li_environment *env=0);

/** Add an item to the begining of a list.
    @param l List to add elements to.
    @param o Object to add.
*/
inline void li_push(li_list *&l, li_object *o) { l=new li_list(o, l); }

// global symbols

extern li_symbol *li_nil, 
  *li_true_sym, 
  *li_quote, 
  *li_backquote,
  *li_comma,
  *li_function_symbol;


class li_symbol_ref
{
  char *name;
  li_symbol *sym;
public:
  li_symbol *get() { if (!sym) sym=li_get_symbol(name); return sym; }
  i4_bool operator==(const li_symbol *&b) { return (get() == b); }

  li_symbol_ref(char *sym_name) : name(sym_name) { sym=0; }
};

#endif















