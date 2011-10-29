// summary.h : 64 bit integers
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
    
#ifndef int64__summary__h
#define int64__summary__h

namespace int64{
    namespace internal{

template <typename LONG>
SEXP summary__min( const int64::LongVector<LONG>& data){
    LONG x = data.get(0) ;
    LONG tmp = x ;
    int n = data.size() ;
    for( int i=1; i<n; i++){
        tmp = data.get(i) ;
        if( tmp < x ) x = tmp ;
    }
    return int64::internal::new_long<LONG>( x ) ;
}

template <typename LONG>
SEXP summary__max( const int64::LongVector<LONG>& data){
    LONG x = data.get(0) ;
    LONG tmp = x ;
    int n = data.size() ;
    for( int i=1; i<n; i++){
        tmp = data.get(i) ;
        if( tmp > x ) x = tmp ;
    }
    return int64::internal::new_long<LONG>( x ) ;
}

template <typename LONG>
SEXP summary__range( const int64::LongVector<LONG>& data){
    LONG min = data.get(0) ;
    LONG max = data.get(0) ;
    LONG tmp = min ;
    int n = data.size() ;
    for( int i=1; i<n; i++){
        tmp = data.get(i) ;
        if( tmp < min ) min = tmp ;
        if( tmp > max ) max = tmp ;
    }
    return int64::internal::new_long_2<LONG>( min, max) ;
}

template <typename LONG>
SEXP summary__prod( const int64::LongVector<LONG>& data){
    LONG res = data.get(0) ;
    int n = data.size() ;
    
    for( int i=1; i<n; i++){
        res *= data.get(i) ;
    }
    return int64::internal::new_long<LONG>( res ) ;
}

template <typename LONG>
SEXP summary__sum( const int64::LongVector<LONG>& data){
    LONG res = data.get(0) ;
    int n = data.size() ;
    
    for( int i=1; i<n; i++){
        res += data.get(i) ;
    }
    return int64::internal::new_long<LONG>( res ) ;
}

template <typename LONG>
SEXP summary__any( const int64::LongVector<LONG>& data){
    int n = data.size() ;
    int res = 0 ;
    for( int i=0; i<n; i++){
        if( data.get(i) ) {
            res = 1 ;
            break ;
        }
    }
    SEXP x = PROTECT( Rf_allocVector( LGLSXP, 1 ) ) ;
    INTEGER(x)[0] = res ;
    UNPROTECT(1) ; // x
    return x ;
}

template <typename LONG>
SEXP summary__all( const int64::LongVector<LONG>& data){
    int n = data.size() ;
    int res = 1 ;
    for( int i=0; i<n; i++){
        if( ! data.get(i) ) {
            res = 0 ;
            break ;
        }
    }
    SEXP x = PROTECT( Rf_allocVector( LGLSXP, 1 ) ) ;
    INTEGER(x)[0] = res ;
    UNPROTECT(1) ; // x
    return x ;
}

template <typename LONG>
SEXP int64_summary(const char* op, SEXP x){
    int64::LongVector<LONG> data( R_do_slot(x, Rf_install(".Data") ) ) ;
    
    if( ! strcmp(op, "min") ){
        return int64::internal::summary__min<LONG>( data ) ;
    } else if( !strcmp(op, "max") ){
        return int64::internal::summary__max<LONG>( data ) ;
    } else if( !strcmp(op, "range" ) ){
        return int64::internal::summary__range<LONG>( data ) ;
    } else if( !strcmp(op, "prod") ){
        return int64::internal::summary__prod<LONG>( data ) ;
    } else if( !strcmp(op, "sum" ) ) {
        return int64::internal::summary__sum<LONG>( data ) ;
    } else if( !strcmp(op, "any" ) ){
        return int64::internal::summary__any<LONG>( data ) ;
    } else if( !strcmp(op, "all") ){
        return int64::internal::summary__all<LONG>( data ) ;
    }
    Rf_error( "unknown operator" ) ;
    return R_NilValue ;
        
}


    } // namespace internal
    
} // namespace int64

#endif
