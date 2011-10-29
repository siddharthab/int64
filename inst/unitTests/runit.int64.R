# Copyright (C) 2011	Romain Francois
# Copyright (C) 2011	Google
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

test.int64 <- function(){
    ints <- c(-122L, 0L, 1L, 122L)
    x <- as.int64(ints)
    
    checkEquals(
        as.integer(as.character(x)), 
        ints
    )
    checkEquals( as.character(x+1L), as.character(ints+1L) )
    checkEquals( as.character(x-1L), as.character(ints-1L) )
    checkEquals( as.character(x*x), as.character(ints*ints) )
    checkEquals( as.character(x/2L), as.character(as.integer(ints/2L)) )
    
    checkEquals( x > 0L, ints > 0L )
    checkEquals( x < 0L, ints < 0L )
    checkEquals( x == 0L, ints == 0L )
    checkEquals( x != 0L, ints != 0L )
    checkEquals( x <= 0L, ints <= 0L )
    checkEquals( x >= 0L, ints >= 0L )
    
    checkEquals( range(x), as.int64(c(-122L, 122L)) ) 
    checkEquals( min(x), as.int64(-122L) )
    checkEquals( max(x), as.int64(122L) )
    checkEquals( prod(x), as.int64(as.integer(prod(ints))) )
    checkEquals( sum(x), as.int64(as.integer(sum(ints))) )
    checkEquals( any(x), any(ints) )
    checkEquals( all(x), all(ints) )
    
    chars <- c( "-9223372036854775808", "9223372036854775807" )
    x <- as.int64( chars )
    checkEquals( as.character(x), chars )
    
}

test.uint64 <- function(){
    ints <- c(0L, 1L, 123L)
    x <- as.uint64(ints)
    
    checkEquals(
        as.integer(as.character(x)), 
        ints
    )
    
    chars <- c( "123456789123456789", "18446744073709551615" )
    x <- as.uint64( chars )
    checkEquals( as.character(x), chars )
    
}

