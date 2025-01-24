#include <voxelterrain.h>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void VoxelTerrain::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_seed"), &VoxelTerrain::get_seed);
    ClassDB::bind_method(D_METHOD("set_seed", "new_seed"), &VoxelTerrain::set_seed);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"),
        "set_seed", "get_seed");
    
};


void VoxelTerrain::delete_chunks() {
    for (int x = 0; x < chunks.size(); x++) {
        for (int y = 0; y < chunks[x].size(); y++) {
            for (int z = 0; z < chunks[x][y].size(); z++) {
                delete chunks[x][y][z];
            };
        };
    };
};


void VoxelTerrain::initialize_chunks() {

    delete_chunks();

    for (int x = 0; x < RENDER_SIDE; x++) {
        chunks.push_back(vector<vector<Chunk *>> {{}});
        for (int y = 0; y < RENDER_SIDE_Y; y++) {
            chunks[x].push_back(vector<Chunk *> {});
            for (int z = 0; z < RENDER_SIDE; z++) {
                chunks[x][y].push_back(new Chunk(fast_noise));
                chunks[x][y][z]->render();
            };
        };
    };
};


VoxelTerrain::VoxelTerrain() {
    time_passed = 0.0;
    seed = 300;
    
    fast_noise = memnew(FastNoiseLite());
    fast_noise->set_seed(seed);
    fast_noise->set_noise_type(FastNoiseLite::NoiseType::TYPE_SIMPLEX);
    fast_noise->set_fractal_type(FastNoiseLite::FRACTAL_FBM);
    fast_noise->set_fractal_octaves(5);
    fast_noise->set_frequency(0.1);
    chunks = vector<vector<vector<Chunk *>>> {};
};

VoxelTerrain::~VoxelTerrain() {

    // Free render chunks
    delete_chunks();
    memdelete(fast_noise);

};

void VoxelTerrain::_process(double delta) {
    
};

void VoxelTerrain::_ready() {
    initialize_chunks();
};

uint64_t VoxelTerrain::get_seed() const{
    return seed;
};

void VoxelTerrain::set_seed(const uint64_t new_seed) {
    seed = new_seed;
    fast_noise->set_seed(seed);
};