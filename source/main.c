#include <spmp.h>

int main(void) {
    SPMP_GFXDefaultInit();
    SPMP_SerialPrint("BREAK!\n");
    BREAK(0);
    return 0;
}
