
#include "fff.h"
#include <assert.h>
#include <stdio.h>
#include "sbd.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(hello_world);

void setup() {
    RESET_FAKE(hello_world);
    FFF_RESET_HISTORY();
}

void test_hello_world_is_called() {
    setup();
    
    hello_world();

    assert(hello_world_fake.call_count == 1);
    printf("test_hello_world_is_called: PASSED\n");
}

int main() {
    printf("Running Library Tests...\n");
    
    test_hello_world_is_called();
    
    printf("All tests finished successfully!\n");
    return 0;
}
