//
// Created by JokerTOoL on 20/04/2022.
//

#ifndef ACSII_ART_TOOL
#define ACSII_ART_TOOL

#include "stdio.h"
#include "stdbool.h"
#include "RLEList.h"

RLEList asciiArtRead(FILE* in_stream);

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif