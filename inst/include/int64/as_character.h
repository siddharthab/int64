// as_character.h : 64 bit integers
//
// Copyright (C) 2011 Romain Francois
// Copyright (C) 2011 Google
//
// This file is part of int64.
//
// int64 is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// int64 is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License  
// along with int64.  If not, see <http://www.gnu.org/licenses/>.    
    
#ifndef int64__as_character__h
#define int64__as_character__h
   
#include <iostream>
#include <sstream>

namespace int64{
    namespace internal{

template <typename LONG>
SEXP int64_as_character( SEXP x){
    int64::LongVector<LONG> data( R_do_slot(x, Rf_install(".Data") ) ) ;
    int n = data.size() ; 
    SEXP res = PROTECT( Rf_allocVector( STRSXP, n) ) ;
    std::ostringstream stream ;
    for( int i=0; i<n; i++){ 
        stream << data.get(i) ;
        SET_STRING_ELT( res, i, Rf_mkChar(stream.str().c_str()) ) ;
        stream.str("") ;
    }
    UNPROTECT(1) ; // res
    return res ;
}
        
    } // namespace internal
} // namespace int64

#endif
