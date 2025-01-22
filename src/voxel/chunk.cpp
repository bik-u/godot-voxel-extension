#include <voxel/chunk.h>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;
using namespace std;


void Chunk::render() {
    

}

Chunk::Chunk() {
    // Fill chunks with air
    blocks = vector<vector<vector<uint32_t>>> (
        SIDE_SIZE, vector<vector<uint32_t>>(
            SIDE_SIZE, vector<uint32_t> (
                SIDE_SIZE, BLOCKS::AIR
            )
        )
    );

    UtilityFunctions::print("new chunk!");

};


Chunk::~Chunk() {
};