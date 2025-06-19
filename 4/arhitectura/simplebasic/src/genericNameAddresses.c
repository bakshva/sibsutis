#include "basic.h"

void genericNamesAddresses()
{
    int baseAddress = currentaddress;
    for (int i = 0; i != nameTable.namecount; i++) {
        nameTable.names[i].address = baseAddress;
        baseAddress++;
    }
}