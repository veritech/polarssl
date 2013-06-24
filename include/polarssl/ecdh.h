/**
 * \file ecdh.h
 *
 * \brief Elliptic curve Diffie-Hellman
 *
 *  Copyright (C) 2006-2013, Brainspark B.V.
 *
 *  This file is part of PolarSSL (http://www.polarssl.org)
 *  Lead Maintainer: Paul Bakker <polarssl_maintainer at polarssl.org>
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef POLARSSL_ECDH_H
#define POLARSSL_ECDH_H

#include "polarssl/ecp.h"

/**
 * \brief           ECDH context structure
 */
typedef struct
{
    ecp_group grp;      /*!<  ellipitic curve used      */
    mpi d;              /*!<  our secret value          */
    ecp_point Q;        /*!<  our public value          */
    ecp_point Qp;       /*!<  peer's public value       */
    mpi z;              /*!<  shared secret             */
    int point_format;   /*!<  format for point export   */
}
ecdh_context;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief           Generate a public key
 *
 * \param grp       ECP group
 * \param d         Destination MPI (secret exponent)
 * \param Q         Destination point (public key)
 * \param f_rng     RNG function
 * \param p_rng     RNG parameter
 *
 * \return          0 if successful,
 *                  or a POLARSSL_ERR_ECP_XXX or POLARSSL_MPI_XXX error code
 */
int ecdh_gen_public( const ecp_group *grp, mpi *d, ecp_point *Q,
                     int (*f_rng)(void *, unsigned char *, size_t),
                     void *p_rng );

/**
 * \brief           Compute shared secret
 *
 * \param grp       ECP group
 * \param z         Destination MPI (shared secret)
 * \param Q         Public key from other party
 * \param d         Our secret exponent
 *
 * \return          0 if successful,
 *                  or a POLARSSL_ERR_ECP_XXX or POLARSSL_MPI_XXX error code
 */
int ecdh_compute_shared( const ecp_group *grp, mpi *z,
                         const ecp_point *Q, const mpi *d );

/**
 * \brief           Initialize context
 *
 * \param ctx       Context to initialize
 */
void ecdh_init( ecdh_context *ctx );

/**
 * \brief           Free context
 *
 * \param ctx       Context to free
 */
void ecdh_free( ecdh_context *ctx );

/**
 * \brief           Setup and write the ServerKeyExhange parameters
 *
 * \param ctx       ECDH context
 * \param buf       destination buffer
 * \param olen      number of chars written
 * \param f_rng     RNG function
 * \param p_rng     RNG parameter
 *
 * \note            This function assumes that ctx->grp has already been
 *                  properly set (for example using ecp_use_known_dp).
 *
 * \return          0 if successful, or an POLARSSL_ERR_ECP_XXX error code
 */
int ecdh_make_params( ecdh_context *ctx, size_t *olen,
                      unsigned char *buf, size_t blen,
                      int (*f_rng)(void *, unsigned char *, size_t),
                      void *p_rng );

/**
 * \brief           Parse the ServerKeyExhange parameters
 *
 * \param ctx       ECDH context
 * \param buf       $(start of input buffer)
 * \param end       one past end of buffer
 *
 * \return          0 if successful, or an POLARSSL_ERR_ECP_XXX error code
 */
int ecdh_read_params( ecdh_context *ctx,
                      const unsigned char **buf, const unsigned char *end );

/**
 * \brief           Setup and export the client's public value
 *
 * \param ctx       ECDH context
 * \param olen      number of bytes actually written
 * \param buf       destination buffer
 * \param blen      size of destination buffer
 *
 * \return          0 if successful, or an POLARSSL_ERR_ECP_XXX error code
 */
int ecdh_make_public( ecdh_context *ctx, size_t *olen,
                      unsigned char *buf, size_t blen,
                      int (*f_rng)(void *, unsigned char *, size_t),
                      void *p_rng );

/**
 * \brief           Parse and import the client's public value
 *
 * \param ctx       ECDH context
 * \param buf       start of input buffer
 * \param blen      length of input buffer
 *
 * \return          0 if successful, or an POLARSSL_ERR_ECP_XXX error code
 */
int ecdh_read_public( ecdh_context *ctx,
                      const unsigned char *buf, size_t blen );

/**
 * \brief           Derive and export the shared secret
 *
 * \param ctx       ECDH context
 * \param olen      number of bytes written
 * \param buf       destination buffer
 * \param blen      buffer length
 *
 * \return          0 if successful, or an POLARSSL_ERR_ECP_XXX error code
 */
int ecdh_calc_secret( ecdh_context *ctx, size_t *olen,
                      unsigned char *buf, size_t blen );

/**
 * \brief          Checkup routine
 *
 * \return         0 if successful, or 1 if the test failed
 */
int ecdh_self_test( int verbose );

#ifdef __cplusplus
}
#endif

#endif