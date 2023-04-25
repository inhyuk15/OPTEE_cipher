/*
 * Copyright (c) 2016, Linaro Limited
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

#include <err.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* OP-TEE TEE client API (built by optee_client) */
#include <tee_client_api.h>

/* To the the UUID (found the the TA's h-file(s)) */
#include <TEEencrypt_ta.h>

struct ta_attrs {
	TEEC_Context ctx;
	TEEC_Session sess;
};

void rsa_gen_keys(TEEC_Session* sess) {
	/*TEEC_Result res;
	res = TEEC_InvokeCommand(sess, TA_RSA_CMD_GENKEYS, NULL, NULL);
	if(res != TEEC_SUCCESS) {
		errx(1, "\n error: TEEC InvokeCommand failed");
	}
	*/
}


int main(int argc, char* argv[])
{
	TEEC_Result res;
	TEEC_Context ctx;
	TEEC_Session sess;
	TEEC_Operation op;
	TEEC_UUID uuid = TA_TEEencrypt_UUID;
	uint32_t err_origin;
	char plaintext[100] = {0, };
	char ciphertext[100] = {0, };
	int randomkey = 0;
	int len = 100;

	/* Initialize a context connecting us to the TEE */
	res = TEEC_InitializeContext(NULL, &ctx);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_InitializeContext failed with code 0x%x", res);
	res = TEEC_OpenSession(&ctx, &sess, &uuid,
			       TEEC_LOGIN_PUBLIC, NULL, NULL, &err_origin);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_Opensession failed with code 0x%x origin 0x%x",
			res, err_origin);


	memset(&op, 0, sizeof(op));

	// command and option
	if(argc < 4) {
	  printf("Error: insufficient arguments\n");
	  printf("Usage: TEEencrypt -e [filename] [cypertype]\n");
	  return 1;
	}

	// encryption
	if(strcmp(argv[1], "-e") == 0) {
	// parameter setting
		op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_OUTPUT,
TEEC_VALUE_OUTPUT,
					 TEEC_NONE, TEEC_NONE);
	op.params[0].tmpref.buffer = plaintext;
	op.params[0].tmpref.size = len;


		// file read
		FILE *file = fopen(argv[2], "r");
		if(file == NULL) {
		  printf("Error: failed to open input file '%s'\n", argv[2]);
		  return 1;
		}
		if(fgets(plaintext, 100, file) == NULL) {
		  printf("Error: failed to open input file '%s'\n", argv[2]);
		  return 1;
		}
		printf("success to open file and contents: %s\n", plaintext);
		fclose(file);



		// encryption
		memcpy(op.params[0].tmpref.buffer, plaintext, len);

		printf("Invoking TA to encryption %s\n", op.params[0].tmpref.buffer);
		if(strcmp(argv[3], "caesar") == 0) {
			res = TEEC_InvokeCommand(&sess, TA_TEEencrypt_CMD_ENC_VALUE, &op,
					 &err_origin);
		}
		else if(strcmp(argv[3],"rsa") == 0) {
			//rsa_gen_keys(&sess);
			//res = TEEC_InvokeCommand(&sess, TA_TEEencrypt_CMD_RSA_ENC_VALUE, &op,
			//		 &err_origin);
			return 1;
		}
		else {
			printf("option not available");
			return 1;
		}
		if(res != TEEC_SUCCESS) {
			errx(1, "TEEC_InvokeCommand failed with code 0x%x origin 0x%x",
				res, err_origin);
		}

		memcpy(ciphertext, op.params[0].tmpref.buffer, len);
		printf("Ciphertext : %s\n", ciphertext);
		randomkey = op.params[1].value.a;
		printf("randomKey: %u\n", randomkey);
		
		FILE *encryptedFile = fopen("encrypted.txt", "w");
		FILE *keyFile = fopen("key.txt", "w");
		if(encryptedFile == NULL) {
		  printf("Error: failed to write encrypted.txt");
		  fclose(encryptedFile);
		}
		if(keyFile == NULL) {
		  printf("Error: failed to write key.txt");
		  fclose(keyFile);
		}
		fprintf(encryptedFile, "%s", ciphertext);
		fprintf(keyFile, "%u", randomkey);
	}
	// decryption
	else if(strcmp(argv[1],"-d") == 0) {
		// parameter setting
		op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_OUTPUT,
TEEC_VALUE_INOUT,
					 TEEC_NONE, TEEC_NONE);
	op.params[0].tmpref.buffer = plaintext;
	op.params[0].tmpref.size = len;


		// file read
		FILE *file = fopen(argv[2], "r");
		if(file == NULL) {
		  printf("Error: failed to open input file '%s'\n", argv[2]);
		  return 1;
		}
		if(fgets(ciphertext, 100, file) == NULL) {
		  printf("Error: failed to open input file '%s'\n", argv[2]);
		  return 1;
		}
		printf("success to open file and contents: %s\n", ciphertext);
		fclose(file);
	
		FILE *keyFile = fopen(argv[3], "r");
		if(keyFile == NULL) {
		  printf("Error: failed to open key file '%s'\n", argv[2]);
		  fclose(keyFile);
		  return 1;
		}
		char keyline[100];
		if(fgets(keyline, 100, keyFile) == NULL) {
		  printf("Error: failed to open key file '%s'\n", argv[2]);
		  fclose(keyFile);
		  return 1;
		}
		sscanf(keyline, "%d", &randomkey);
		printf("success to open key file and contents: %d\n", randomkey);
		fclose(keyFile);
	
		// decryption
		memcpy(op.params[0].tmpref.buffer, ciphertext, len);
		op.params[1].value.a = randomkey;
		printf("Invoking TA to decryption %s and key is %u\n", op.params[0].tmpref.buffer, randomkey);

		if(strcmp(argv[4], "caesar") == 0) {
			res = TEEC_InvokeCommand(&sess, TA_TEEencrypt_CMD_DEC_VALUE, &op,
					 &err_origin);
		}
		else if(strcmp(argv[4], "rsa") == 0) {
			//res = TEEC_InvokeCommand(&sess, TA_TEEencrypt_CMD_RSA_DEC_VALUE, &op,
			//		 &err_origin);
			return 1;
		}
		else {
			printf("option not available");
			return 1;
		}
		if(res != TEEC_SUCCESS) {
			errx(1, "TEEC_InvokeCommand failed with code 0x%x origin 0x%x",
				res, err_origin);
		}

		memcpy(plaintext, op.params[0].tmpref.buffer, len);
		printf("Plaintext : %s\n", plaintext);
		
	}

	TEEC_CloseSession(&sess);

	TEEC_FinalizeContext(&ctx);

	return 0;
}
