#ifndef VOXELTERRAIN_H
#define VOXELTERAIN_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/fast_noise_lite.hpp>
#include <voxel/chunk.h>
#include <unordered_map>

using namespace std;

namespace godot {

class VoxelTerrain : public Node3D {
	GDCLASS(VoxelTerrain, Node3D)

private:
	const uint8_t RENDER_SIDE = 1;
	const uint8_t RENDER_SIDE_Y = 1;
	double time_passed;
	vector<vector<vector<Chunk *>>> chunks;
	uint64_t seed;
	FastNoiseLite *fast_noise;

	void delete_chunks();
	void initialize_chunks();

protected:
	static void _bind_methods();

public:
	VoxelTerrain();
	~VoxelTerrain();

	void _process(double delta) override;
	void _ready() override;

	void set_seed(const uint64_t seed);
	uint64_t get_seed() const;
};

}

#endif