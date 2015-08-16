/*
**      txt2pdbdoc -- Text to Doc converter for Palm Pilots
**      utf8.h
**
**      Copyright (C) 2015  Paul J. Lucas
**
**      This program is free software; you can redistribute it and/or modify
**      it under the terms of the GNU General Public License as published by
**      the Free Software Foundation; either version 2 of the Licence, or
**      (at your option) any later version.
**
**      This program is distributed in the hope that it will be useful,
**      but WITHOUT ANY WARRANTY; without even the implied warranty of
**      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**      GNU General Public License for more details.
**
**      You should have received a copy of the GNU General Public License
**      along with this program; if not, write to the Free Software
**      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef txt2pdbdoc_utf8_H
#define txt2pdbdoc_utf8_H

// local
#include "util.h"                       /* for bool */

// standard
#include <stddef.h>                     /* for size_t */
#include <stdint.h>                     /* for uint8_t, ... */

#ifndef TXT2PDBDOC_UTF8_INLINE
# define TXT2PDBDOC_UTF8_INLINE _GL_INLINE
#endif /* TXT2PDBDOC_UTF8_INLINE */

///////////////////////////////////////////////////////////////////////////////

/**
 * The maximum number of bytes needed by a Unicode code-point encoded in UTF-8.
 */
#define UTF8_LEN_MAX  6

///////////////////////////////////////////////////////////////////////////////

/**
 * Checks whether the given Unicode code-point is valid.
 *
 * @param codepoint The Unicode code-point to check.
 * @return Returns \c true only if \a codepoint is valid.
 */
TXT2PDBDOC_UTF8_INLINE bool codepoint_is_valid( uint64_t codepoint ) {
  return                            codepoint <= 0x00D7FF
      ||  (codepoint >= 0x00E000 && codepoint <= 0x00FFFD)
      ||  (codepoint >= 0x010000 && codepoint <= 0x10FFFF);
}

/**
 * Decodes a UTF-8 octet sequence into a Unicode codepoint.
 *
 * @param utf8 The UTF-8 octet sequence to decode.
 * @return Returns said codepoint or 0 if the \a utf8 is invalid.
 */
uint32_t utf8_decode( char const *utf8, size_t *len );

/**
 * Encodes a Unicode codepoint into UTF-8.
 *
 * @param codepoint The Unicode code-point to encode.
 * @param utf8_buf A pointer to the start of a buffer to receive the UTF-8
 * bytes; must be at least \c UTF8_LEN_MAX long.  No NULL byte is appended.
 * @return Returns the number of bytes comprising the codepoint encoded as
 * UTF-8.
 */
size_t utf8_encode( uint32_t codepoint, char *utf8_buf );

/**
 * Checks whether the given byte is the first byte of a UTF-8 byte sequence
 * comprising an encoded character.  Note that this is not equivalent to
 * !utf8_is_cont(c).
 *
 * @param c The byte to check.
 * @return Returns \c true only if the byte is the first byte of a UTF-8 byte
 * sequence comprising an encoded character.
 */
TXT2PDBDOC_UTF8_INLINE bool utf8_is_start( char c ) {
  uint8_t const u = c;
  return u < 0x80u || (u >= 0xC2u && u < 0xFEu);
}

/**
 * Checks whether the given byte is not the first byte of a UTF-8 byte sequence
 * comprising an encoded character.  Note that this is not equivalent to
 * !utf8_is_start(c).
 *
 * @param c The byte to check.
 * @return Returns \c true only if the byte is not the first byte of a UTF-8
 * byte sequence comprising an encoded character.
 */
TXT2PDBDOC_UTF8_INLINE bool utf8_is_cont( char c ) {
  uint8_t const u = c;
  return u >= 0x80u && u < 0xC0u;
}

/**
 * Gets the length of a UTF-8 character.
 *
 * @param start The start byte of a UTF-8 byte sequence.
 * @return Returns the number of bytes needed for the UTF-8 character in the
 * range [1,6] or 0 if \a start is not a valid start byte.
 */
TXT2PDBDOC_UTF8_INLINE size_t utf8_len( char start ) {
  extern uint8_t const utf8_len_table[];
  return utf8_len_table[ (uint8_t)start ];
}

///////////////////////////////////////////////////////////////////////////////

#endif /* txt2pdbdoc_utf8_H */
/* vim:set et sw=2 ts=2: */
