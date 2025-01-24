#include <voxel/chunk.h>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/surface_tool.hpp>

using namespace godot;
using namespace std;


void Chunk::render() {
    //TODO: binary greedy meshing
    using grid = uint8_t[SIDE_SIZE][SIDE_SIZE];

    // Make grids for face culling
    auto x_cols = new grid();
    auto y_cols = new grid();
    auto z_cols = new grid(); 

    auto p_x_cols = new grid();
    auto n_x_cols = new grid();
    auto p_y_cols = new grid();
    auto n_y_cols = new grid();
    auto p_z_cols = new grid();
    auto n_z_cols = new grid();

    for (int x = 0; x < SIDE_SIZE; x++) {
        for (int y = 0; y < SIDE_SIZE; y++) {
            for (int z = 0; z < SIDE_SIZE; z++) {
                uint32_t block = blocks[x][y][z];
                if (block) {

                    x_cols[z][y] |=  1 << x;
                    y_cols[x][z] |=  1 << y;
                    z_cols[x][y] |=  1 << z;

                };
                // Check if solid
            };
        };
    };

    // Cull Face
    for (int x = 0; x < SIDE_SIZE;  x++) {
        for (int y = 0; y < SIDE_SIZE; y++) {
            p_x_cols[x][y] = x_cols[x][y] & (x_cols[x][y] << 1);
            n_x_cols[x][y] = x_cols[x][y] & (x_cols[x][y] >> 1);
            p_y_cols[x][y] = y_cols[x][y] & (y_cols[x][y] << 1);
            n_y_cols[x][y] = y_cols[x][y] & (y_cols[x][y] >> 1);
            p_z_cols[x][y] = z_cols[x][y] & (z_cols[x][y] << 1); 
            n_z_cols[x][y] = z_cols[x][y] & (z_cols[x][y] >> 1);

        }        
    }

    delete x_cols;
    delete y_cols;
    delete z_cols;
    delete p_x_cols;
    delete n_x_cols;
    delete p_y_cols;
    delete n_y_cols; 
    delete p_z_cols; 
    delete n_z_cols; 

};

uint32_t get_block_from_pos(Vector3i pos, FastNoiseLite *noise)  {
    float val = noise->get_noise_3dv(pos);
    if (val > 0.2) {
        UtilityFunctions::print("solid");
        return BLOCKS::DIRT;
    } else {
        return BLOCKS::AIR;
    };
};

Chunk::Chunk(FastNoiseLite *noise) {
    // Fill chunks
    noise = noise;
    blocks = vector<vector<vector<uint32_t>>> {};

    for (int x = 0; x < SIDE_SIZE; x++) {
        blocks.push_back(vector<vector<uint32_t>> {{}});
        for (int y = 0; y < SIDE_SIZE; y++) {
            blocks[x].push_back(vector<uint32_t> {});
            for (int z = 0; z < SIDE_SIZE; z++) {
                Vector3i block_pos = Vector3i(x, y, z);
                blocks[x][y].push_back(get_block_from_pos(block_pos, noise));
            };
        };
    };


};


Chunk::~Chunk() {
};