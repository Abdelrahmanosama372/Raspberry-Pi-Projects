#include "publisher.hpp"
#include <iostream>

int main(int argc, const char** argv) {

    Publisher pub("ledstate");
    pub.input_publish();
    return 0;
}
