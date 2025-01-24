#ifndef CHUNK_H
#define CHUNK_H

#include <stdint.h>
#include <vector>
#include <constants/blocks.h>
#include <godot_cpp/classes/fast_noise_lite.hpp>

namespace godot {

class Chunk {

private:
    static const uint8_t SIDE_SIZE = 2;
    FastNoiseLite *noise;

public:
    std::vector<std::vector<std::vector<uint32_t>>> blocks;
    void render();
    Chunk(FastNoiseLite *noise);
    ~Chunk();
};

};

#endif