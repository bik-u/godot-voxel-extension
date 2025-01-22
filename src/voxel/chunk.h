#ifndef CHUNK_H
#define CHUNK_H

#include <stdint.h>
#include <vector>
#include <constants/blocks.h>

namespace godot {

class Chunk {

private:
    static const int8_t SIDE_SIZE = 16;

public:
    std::vector<std::vector<std::vector<uint32_t>>> blocks;
    void render();
    Chunk();
    ~Chunk();
};

}

#endif