#include "stdio.h"
#include "stdbool.h"
#include "RLEList.h"
#include "AsciiArtTool.h"
#include "RLEList.c"
#define buffer_size 256

void minimize_and_add_to_RLEList(RLEList list, char* str)
{
    while (str)
    {
        RLEListAppend(list, *str++);
    }
    RLEListAppend(list, '\n');
}

RLEList asciiArtRead(FILE* in_stream)
{
    RLEList list = RLEListCreate();

    if(!list){
        return list;
    }

    char buffer[buffer_size + 1] = "";
    while (fgets(buffer, buffer_size, in_stream))
    {
        minimize_and_add_to_RLEList(list, buffer);
    }
    return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    if(!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEList helper = list;
    char *line = (char*)malloc(buffer_size);
    while (list)
    {
        while (helper->character != '\n')
        {
            fputc(helper->character, out_stream);
            helper++;
        }
    fputc('\n', out_stream);
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    char *encoded;
    encoded = RLEListExportToString(list, NULL);

    fputs(encoded, out_stream);
    return RLE_LIST_SUCCESS;
}
