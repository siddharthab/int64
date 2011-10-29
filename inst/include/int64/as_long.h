// as_long.h : 64 bit integers
//
// Copyright (C) 2011 Romain Francois
// Copyright (C) 2011 Google Inc.  All rights reserved.
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
    
#ifndef int64__as_long__h
#define int64__as_long__h
              
namespace int64{
    namespace internal{

    template <typename LONG>
    LONG read_string(const char* s) ;
    
    template <>
    int64_t read_string<int64_t>(const char* s ){
        return strtoll( s, NULL, 0 ) ; 
    }
        
    template <>
    uint64_t read_string<uint64_t>(const char* s){
        return strtoull( s, NULL, 0 ) ;
    } 
        
        
template <typename LONG>
SEXP as_long(SEXP x){
    int n = Rf_length(x) ;
    int64::LongVector<LONG> data(n) ;
    switch( TYPEOF(x) ){
    case INTSXP:
        {
            int* p_x = INTEGER(x) ;
            for( int i=0;i<n; i++){
                data.set( i, (LONG)p_x[i] ) ;
            }
            break ;
        }
    case STRSXP:
        {
            for( int i=0;i<n; i++){
                LONG tmp = read_string<LONG>(CHAR(STRING_ELT(x,i))) ;
                data.set( i, tmp ) ;
            }
            break;                               
        }     
    default:
        Rf_error( "incompatible type" ) ;
    }
    return data ;
       
}
        
    } // namespace internal
} // namespace int64

#endif
