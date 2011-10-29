// compare.h : 64 bit integers
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
    
#ifndef int64__compare__h
#define int64__compare__h

namespace int64{
    namespace internal{

template <typename T> inline bool equals(T x1,T x2){ return x1 == x2 ; }        
template <typename T> inline bool not_equals(T x1,T x2){ return x1 != x2 ; }        
template <typename T> inline bool lower_than(T x1,T x2){ return x1 < x2 ; }        
template <typename T> inline bool lower_than_or_equal(T x1,T x2){ return x1 <= x2 ; }        
template <typename T> inline bool greater_than(T x1,T x2){ return x1 > x2 ; }        
template <typename T> inline bool greater_than_or_equal(T x1,T x2){ return x1 >= x2 ; }        
        
template <typename LONG, bool Fun(LONG x1, LONG x2)>
SEXP compare_long_long(SEXP e1, SEXP e2){
    int64::LongVector<LONG> x1( R_do_slot( e1, Rf_install(".Data") ) ) ;
    int64::LongVector<LONG> x2( R_do_slot( e2, Rf_install(".Data") ) ) ;
    
    int n1 = x1.size(), n2 = x2.size() ;
    LONG tmp ;
    int i1=0, i2=0, i=0 ;
    int n = (n1>n2) ? n1 : n2 ;
    SEXP res = PROTECT(Rf_allocVector(LGLSXP, n)); 
    int* p_res = INTEGER(res) ;       
    
    if( n1 == n2 ){
        for( i=0; i<n1; i++){
            p_res[i] = Fun(x1.get(i), x2.get(i)) ;
        }
    } else if( n1 == 1 ){
        tmp = x1.get(i) ;
        for( i=0; i<n2; i++){
            p_res[i] = Fun(tmp,x2.get(i)) ;
        }
    } else if( n2 == 1) {
        tmp = x2.get(i) ;
        for( i=0; i<n1; i++){
            p_res[i] = Fun(x1.get(i),tmp) ;
        }
    } else {
        // recycling
        for (i=i1=i2=0; i<n; i1 = (++i1 == n1) ? 0 : i1, i2 = (++i2 == n2) ? 0 : i2, ++i){
           p_res[i] = Fun(x1.get(i1), x2.get(i2)) ;
        }
    }
    UNPROTECT(1) ; // res
    return res ;
}

template <typename LONG>
SEXP int64_compare(const char* op, SEXP e1, SEXP e2){
    if( ! strcmp(op, "==") ){
        return int64::internal::compare_long_long<LONG,  int64::internal::equals<LONG> >( e1, e2) ;
    } else if( ! strcmp( op, "!=" ) ) {
        return int64::internal::compare_long_long<LONG,  int64::internal::not_equals<LONG> >( e1, e2) ;
    } else if( ! strcmp( op, "<" ) ) {
        return int64::internal::compare_long_long<LONG,  int64::internal::lower_than<LONG> >( e1, e2) ;
    } else if( ! strcmp( op, ">" ) ) {
         return int64::internal::compare_long_long<LONG,  int64::internal::greater_than<LONG> >( e1, e2) ;
    } else if( ! strcmp( op, "<=" ) ) {
        return int64::internal::compare_long_long<LONG,  int64::internal::lower_than_or_equal<LONG> >( e1, e2) ;
    } else if( ! strcmp( op, ">=" ) ) {
        return int64::internal::compare_long_long<LONG,  int64::internal::greater_than_or_equal<LONG> >( e1, e2) ;
    } 
    Rf_error( "unknown operator" ) ;
    return R_NilValue ;
}


    } // namespace internal
    
} // namespace int64

#endif
