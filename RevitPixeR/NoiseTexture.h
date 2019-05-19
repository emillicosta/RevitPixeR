#pragma once
#include "Texture.h"
//#include "Perlin.h"
class NoiseTexture :
	public Texture
{
private:
	std::vector<int> x_perm;
	std::vector<int> y_perm;
	std::vector<int> z_perm;
	std::vector<vec3> random_vec;
	float scale;
public:
	NoiseTexture(float s_) {
		generate_permutation(x_perm);
		generate_permutation(y_perm);
		generate_permutation(z_perm);
		perlin_generate(random_vec);
		scale = s_;
	}

	virtual rgb value(float u = 0, float v = 0, const vec3& p = vec3()) const {
		return vec3(1, 1, 1)* 0.5* (1 + sin(scale * p.z() + 5 * turbulance(scale * p)));
		noise(scale * p);
	}

	float noise(const vec3& p) const;
	void generate_permutation(std::vector<int>& v);
	void perlin_generate(std::vector<vec3>& v);
	float turbulance(vec3 p, int depth = 7) const;
};


inline void NoiseTexture::generate_permutation(std::vector<int> & v) {
	for (int i = 0; i < 256; i++) {
		v.push_back(i);
	}
	for (int i = 255; i > 0; i--) {
		double random = (double)rand() / RAND_MAX;
		int target = int(random * (i + 1));
		int vi = v[i];
		v[i] = v[target];
		v[target] = vi;
	}
}

inline void NoiseTexture::perlin_generate(std::vector<vec3> & v) {
	for (int i = 0; i < 256; i++) {
		v.push_back(unit_vector(vec3(-1 + 2 * (float)rand() / RAND_MAX,
			-1 + 2 * (float)rand() / RAND_MAX,
			-1 + 2 * (float)rand() / RAND_MAX)));
	}
}

inline float NoiseTexture::turbulance(vec3 p, int depth) const {
	float accum = 0;
	float weight = 1;
	for (int i = 0; i < depth; i++) {
		accum += weight * noise(p);
		weight *= 0.5;
		p *= 2;
	}
	return abs(accum);
}

inline float NoiseTexture::noise(const vec3 & p) const {
	int i = (int) floor(p.x());
	int j = (int) floor(p.y());
	int k = (int) floor(p.z());
	float u = p.x() - i;
	float v = p.y() - j;
	float w = p.z() - k;
	float uu = u * u * (3 - 2 * u);
	float vv = v * v * (3 - 2 * v);
	float ww = w * w * (3 - 2 * w);
	float accum = 0;
	for (int di = 0; di < 2; di++) {
		for (int dj = 0; dj < 2; dj++) {
			for (int dk = 0; dk < 2; dk++) {
				accum += (di * uu + (1 - di) * (1 - uu)) *
					(dj * vv + (1 - dj) * (1 - vv)) *
					(dk * ww + (1 - dk) * (1 - ww)) *
					dot(random_vec[x_perm[(i + di) & 255] ^ y_perm[(j + dj) & 255] ^ z_perm[(k + dk) & 255]],
						vec3(u - di, v - dj, w - dk));
			}
		}
	}
	return accum;
}