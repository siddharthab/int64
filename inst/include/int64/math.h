// math.h : 64 bit integers
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
    
#ifndef int64__math__h
#define int64__math__h

namespace int64{
    namespace internal{
      
template <typename LONG>
SEXP abs( SEXP x ){
    int64::LongVector<LONG> data(x) ;
    int n = data.size() ;
    LONG tmp ;
    int64::LongVector<LONG> res(n) ;
    for( int i=0; i<n; i++){
        tmp = data.get(i) ;
        res.set( i, tmp > 0 ? tmp : -tmp ) ;            
    }
    return res ;    
}
template <>
SEXP abs<uint64_t>( SEXP x ){ return x ; }
     
template <typename LONG>
SEXP sign( SEXP x){
    int64::LongVector<LONG> data(x) ;
    int n = data.size() ;
    SEXP res = PROTECT(Rf_allocVector(REALSXP,n)) ;
    double* p_res = REAL(res) ;
    for( int i=0; i<n; i++){
        p_res[i] = ( data.get(i) > 0 ) ? 0.0 : 1.0 ;
    }
    UNPROTECT(1) ;
    return res ;    
}

template <typename LONG>
SEXP cummax( SEXP x){
    int64::LongVector<LONG> data(x) ;
    int n = data.size() ;
    int64::LongVector<LONG> res(x) ;
    LONG max = data.get(0) ;
    res.set( 0, max) ;
    LONG tmp = 0 ;
    
    for( int i=1; i<n; i++){
        tmp = data.get(i) ;
        if( tmp > max ) max=tmp ;
        res.set( i, max ) ;
    }
    return res ;
}

template <typename LONG>
SEXP cummin( SEXP x){
    int64::LongVector<LONG> data(x) ;
    int n = data.size() ;
    int64::LongVector<LONG> res(x) ;
    LONG max = data.get(0) ;
    res.set( 0, max) ;
    LONG tmp = 0 ;
    
    for( int i=1; i<n; i++){
        tmp = data.get(i) ;
        if( tmp < max ) max=tmp ;
        res.set( i, max ) ;
    }
    return res ;
}

template <typename LONG>
SEXP cumprod( SEXP x){
    int64::LongVector<LONG> data(x) ;
    int n = data.size() ;
    int64::LongVector<LONG> res(x) ;
    LONG prod = data.get(0) ;
    res.set( 0, prod) ;
    
    for( int i=1; i<n; i++){
        prod *= data.get(i) ;
        res.set( i, prod ) ;
    }
    return res ;
}

template <typename LONG>
SEXP cumsum( SEXP x){
    int64::LongVector<LONG> data(x) ;
    int n = data.size() ;
    int64::LongVector<LONG> res(x) ;
    LONG prod = data.get(0) ;
    res.set( 0, prod) ;
    
    for( int i=1; i<n; i++){
        prod += data.get(i) ;
        res.set( i, prod ) ;
    }
    return res ;
}


template <typename LONG>
SEXP math( const char* op, SEXP x ){
    
    if( !strcmp( op, "abs" ) ){
        return abs<LONG>(x) ;
    } else if( !strcmp(op, "sign") ) {
        return sign<LONG>(x) ;
    } else if( !strcmp( op, "trunc" ) ){
        return x ;
    } else if( !strcmp( op, "floor" ) ){
        return x ;   
    } else if( !strcmp( op, "cummax" ) ){
        return cummax<LONG>( x ) ;
    } else if( !strcmp( op, "cummin" ) ){
        return cummin<LONG>( x ) ;
    } else if( !strcmp( op, "cumprod" ) ){
        return cumprod<LONG>( x ) ;
    } else if( !strcmp( op, "cumsum" ) ){
        return cumsum<LONG>( x ) ;   
    }
    
    Rf_error( "generic not implemented" );
    return R_NilValue ;
}

    } // namespace internal
    
} // namespace int64

#endif
