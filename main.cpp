#include "Starter.h"

int main(int argc, char **argv) {
    std::unique_ptr<Starter> starter = std::make_unique<Starter>(argc, argv);
    return 0;
}