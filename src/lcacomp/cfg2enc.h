/* 
 *  Copyright (c) 2011 Shirou Maruyama
 * 
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 * 
 *   1. Redistributions of source code must retain the above Copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above Copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   3. Neither the name of the authors nor the names of its contributors
 *      may be used to endorse or promote products derived from this
 *      software without specific prior written permission.
 */

#ifndef ENCODECFGINCLUDED
#define ENCODECFGINCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"bits.h"
#include"lcacommon.h"

typedef struct EncodeDictionary
{
  uint txtlen;
  uint numRules;
  CODE start;
  RULE *rule;
  CODE *tcode;
  CODE newcode;
} EDICT;

#ifdef __cplusplus
extern "C" {
#endif
EDICT *ReadCFG(FILE *input);
void EncodeCFG(EDICT *dict, FILE *output);
void DestructEDict(EDICT *dict);
#ifdef __cplusplus
}
#endif

#endif
