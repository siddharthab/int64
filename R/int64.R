# Copyright (C) 2011 Romain Francois
# Copyright (C) 2011 Google Inc.  All rights reserved.
#
# This file is part of int64.
#
# int64 is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# int64 is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with int64.  If not, see <http://www.gnu.org/licenses/>.

setClass( "int64", contains = "list" )
setClass( "uint64", contains = "list" )

setClass( "binary",  
    representation( data = "character", bits = "integer" )
)

setGeneric( "binary", function(object) standardGeneric("binary") )
setMethod( "binary", "integer", function(object){
   new( "binary", data = .Call( int64_format_binary, object ), bits = 32L ) 
} )
setMethod( "binary", "numeric", function(object){
   new( "binary", data = .Call( int64_format_binary, object ), bits = 64L ) 
} )
setMethod( "binary", "int64", function(object){
   new( "binary", data = .Call( int64_format_binary, object ), bits = 64L ) 
} )
setMethod( "binary", "uint64", function(object){
   new( "binary", data = .Call( int64_format_binary, object ), bits = 64L ) 
} )
setMethod( "show", "binary", function(object){
    print( noquote( object@data ) )
    invisible(object)
})

int64 <- function(length=0L){
    x <- new("int64", rep( list(integer(2L)), length ) )
    x
}
uint64 <- function(length=0L){
    x <- new("uint64", rep( list(integer(2L)), length ) )
    x
}

setMethod( "length", "int64", function(x){
    length(x@.Data)
} )
setMethod( "length", "uint64", function(x){
    length(x@.Data)
} )
setMethod( "show", "int64", function(object){
    print( noquote( as.character( object ) ) )
    invisible(object)
} )
setMethod( "show", "uint64", function(object){
    print( noquote( as.character( object ) ) )
    invisible(object)
} )

as.int64 <- function(x){
    new( "int64", .Call(int64_as_int64, x) ) 
}
as.uint64 <- function(x){
    new( "uint64", .Call(int64_as_uint64, x) ) 
}

setMethod( "[", "int64", function(x, i, j, ...){
    new( "int64", x@.Data[ i ] )
} )
setMethod( "[", "uint64", function(x, i, j, ...){
    new( "uint64", x@.Data[ i ] )
} )
setMethod( "[<-", "int64", function(x, i, j, ..., value ){
    data <- x@.Data
    data[i] <- as.int64( value )@.Data
    new( "int64", data )
} )
setMethod( "[<-", "uint64", function(x, i, j, ..., value ){
    data <- x@.Data
    data[i] <- as.uint64( value )@.Data
    new( "uint64", data )
} )



setMethod( "Arith", signature(e1 = "int64", e2 = "int64" ), 
function(e1,e2){
   numbers <- .Call( int64_arith_int64_int64, .Generic, e1, e2, FALSE )
   new( "int64", numbers ) 
} )
setMethod( "Arith", signature(e1 = "int64", e2 = "ANY" ), 
function(e1,e2){
   numbers <- .Call( int64_arith_int64_int64, .Generic, e1, as.int64(e2), FALSE )
   new( "int64", numbers )     
} )
setMethod( "Arith", signature(e1 = "ANY", e2 = "int64" ), 
function(e1,e2){
   numbers <- .Call( int64_arith_int64_int64, .Generic, as.int64(e1), e2, FALSE )
   new( "int64", numbers ) 
} )

setMethod( "Arith", signature(e1 = "uint64", e2 = "uint64" ), 
function(e1,e2){
   numbers <- .Call( int64_arith_int64_int64, .Generic, e1, e2, TRUE )
   new( "uint64", numbers ) 
} )
setMethod( "Arith", signature(e1 = "uint64", e2 = "ANY" ), 
function(e1,e2){
   numbers <- .Call( int64_arith_int64_int64, .Generic, e1, as.uint64(e2), TRUE )
   new( "uint64", numbers )     
} )
setMethod( "Arith", signature(e1 = "ANY", e2 = "uint64" ), 
function(e1,e2){
   numbers <- .Call( int64_arith_int64_int64, .Generic, as.uint64(e1), e2, TRUE )
   new( "uint64", numbers ) 
} )

setMethod( "Compare", signature(e1 = "int64", e2 = "int64" ), 
function(e1,e2){
   .Call( int64_compare_int64_int64, .Generic, e1, e2, FALSE )
} )
setMethod( "Compare", signature(e1 = "ANY", e2 = "int64" ), 
function(e1,e2){
   .Call( int64_compare_int64_int64, .Generic, as.int64(e1), e2, FALSE )
} )
setMethod( "Compare", signature(e1 = "int64", e2 = "ANY" ), 
function(e1,e2){
   .Call( int64_compare_int64_int64, .Generic, e1, as.int64(e2), FALSE )
} )

setMethod( "Compare", signature(e1 = "uint64", e2 = "uint64" ), 
function(e1,e2){
   .Call( int64_compare_int64_int64, .Generic, e1, e2, TRUE )
} )
setMethod( "Compare", signature(e1 = "ANY", e2 = "uint64" ), 
function(e1,e2){
   .Call( int64_compare_int64_int64, .Generic, as.uint64(e1), e2, TRUE )
} )
setMethod( "Compare", signature(e1 = "uint64", e2 = "ANY" ), 
function(e1,e2){
   .Call( int64_compare_int64_int64, .Generic, e1, as.uint64(e2), TRUE)
} )


setMethod( "Summary", "int64", function(x,..., na.rm = FALSE){
   .Call( int64_summary_int64, .Generic, x, FALSE)
} )
setMethod( "Summary", "uint64", function(x,..., na.rm = FALSE){
   .Call( int64_summary_int64, .Generic, x, TRUE)
} )


setMethod( "as.character", "int64", function(x,...){
  .Call( int64_as_character_int64, x, FALSE)  
})
setMethod( "as.character", "uint64", function(x,...){
  .Call( int64_as_character_int64, x, TRUE)  
})
setGeneric("as.data.frame")
setMethod( "as.data.frame", "int64", function(x,row.names = NULL, optional = FALSE, ...){
   res <- data.frame( x =  seq_len(length(x)) )
   names(res) <- deparse( substitute(x ) )
   res[[1L]] <- x
   res
})
setMethod( "as.data.frame", "uint64", function(x,row.names = NULL, optional = FALSE, ...){
   res <- data.frame( x =  seq_len(length(x)) )
   names(res) <- deparse( substitute(x ) )
   res[[1L]] <- x
   res
})
         
format.int64 <- format.uint64 <- function(x, ...){
    as.character(x)   
}
setGeneric("format")
setMethod( "format", "int64", format.int64 )
setMethod( "format", "uint64", format.uint64 )

numeric_limits <- function( type ){
    .Call( int64_limits, type )
}

setGeneric( "unique" )
setMethod( "unique", "int64", function(x, incomparables = FALSE, ...){
    new( "int64", .Data = unique( x@.Data, incomparables, ... ) )  
} )
setMethod( "unique", "uint64", function(x, incomparables = FALSE, ...){
    new( "uint64", .Data = unique( x@.Data, incomparables, ... ) )  
} )

setGeneric( "sort" )
setMethod( "sort", "int64", function(x, decreasing = FALSE, ...){
    .Call( int64_sort, x, FALSE, decreasing )
} )
setMethod( "sort", "uint64", function(x, decreasing = FALSE, ...){
    .Call( int64_sort, x, TRUE, decreasing )
} )

