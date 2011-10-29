// routines.h: int64 64 bit integers
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

#ifndef int64_LongVector_h
#define int64_LongVector_h

#include <stdio.h>
#include <iostream>

namespace int64{
    
    template <class LONG>
    class LongVector {
    private :
        SEXP data ;
        
    public:
        LongVector(SEXP x) : data(x) {
            R_PreserveObject(data) ;   
        }
        
        operator SEXP(){ return data; }
        
        LongVector(int n) : data(R_NilValue) {
            SEXP x = PROTECT( Rf_allocVector( VECSXP, n ) ) ;
            for( int i=0; i<n; i++){
                SET_VECTOR_ELT( x, i, int64::internal::int2(0,0) ) ;    
            }
            UNPROTECT(1) ; // x
            data = x ;
            R_PreserveObject(data) ;
        }
        
        ~LongVector(){
            R_ReleaseObject(data) ;   
        }
        
        inline LONG get(int i) const {
            int* p = INTEGER(VECTOR_ELT(data,i)) ;
            return int64::internal::get_long<LONG>( p[0], p[1] ) ;
        }
        
        inline void set(int i, LONG x){
            int* p = INTEGER(VECTOR_ELT(data,i)) ;
            p[0] = int64::internal::get_high_bits(x) ;
            p[1] = int64::internal::get_low_bits(x) ;
        }
        
        inline int size() const { return Rf_length(data); }
        
    } ;

    
}


#endif
