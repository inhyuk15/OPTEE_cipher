/*
 * Copyright (c) 2016-2017, Linaro Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef TA_TEE_ENCRYPT_H
#define TA_TEE_ENCRYPT_H


/*
 * This UUID is generated with uuidgen
 * the ITU-T UUID generator at http://www.itu.int/ITU-T/asn1/uuid.html
 */
/*
#define TA_TEEencrypt_UUID \
	{0xfe497a3e, 0x2434, 0x4edb, \
		{ 0x8a, 0x1e, 0xda,0xc5,0xb7,0xd6,0x96,0x7d} }
*/
#define TA_TEEencrypt_UUID \
	{ 0xf99c42b5, 0x42b5, 0x487d, \
		{ 0xb4, 0x5d, 0xf9, 0x03, 0x43, 0xd2, 0x4e, 0xea} }


/* The function IDs implemented in this TA */
#define TA_TEEencrypt_CMD_ENC_VALUE		0
#define TA_TEEencrypt_CMD_DEC_VALUE		1
#define TA_TEEencrypt_CMD_RSA_ENC_VALUE		2
#define TA_TEEencrypt_CMD_RSA_DEC_VALUE		3

#endif /*TA_TEE_ENCRYPT_H*/
