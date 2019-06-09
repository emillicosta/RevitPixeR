#pragma once
#include "Vec3.h"
#include <vector>
class Perlin
{
private:
	std::vector<int> x_perm;
	std::vector<int> y_perm;
	std::vector<int> z_perm;
	std::vector<vec3> random_vec;
public:

	Perlin() {
		generate_permutation(x_perm);
		generate_permutation(y_perm);
		generate_permutation(z_perm);
		perlin_generate(random_vec);
	}

	float noise(const vec3& p) const;
	void generate_permutation(std::vector<int>& v);
	void perlin_generate(std::vector<vec3>& v);
	float turb(vec3 p, int depth = 7) const;
};


inline float perlin_interp(vec3 c[2][2][2], float u, float v, float w) {
	float uu = u * u * (3 - 2 * u);
	float vv = v * v * (3 - 2 * v);
	float ww = w * w * (3 - 2 * w);
	float accum = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				vec3 weight_v = vec3(u - i, v - j, w - k);
				accum += (i * uu + (1 - i) * (1 - uu)) *
					(j * vv + (1 - j) * (1 - vv)) *
					(k * ww + (1 - k) * (1 - ww)) *
					dot(c[i][j][k], weight_v);
			}
		}
	}
	return accum;
}

float Perlin::noise(const vec3 & p) const {
	int i = floor(p.x());
	int j = floor(p.y());
	int k = floor(p.z());
	double u = p.x() - i;
	double v = p.y() - j;
	double w = p.z() - k;
	double uu = u * u * (3 - 2 * u);
	double vv = v * v * (3 - 2 * v);
	double ww = w * w * (3 - 2 * w);
	double accum = 0;
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

float Perlin::turb(vec3 p, int depth) const {
	double accum = 0;
	double weight = 1;
	for (int i = 0; i < depth; i++) {
		accum += weight * noise(p);
		weight *= 0.5;
		p *= 2;
	}
	return abs(accum);
}

void Perlin::generate_permutation(std::vector<int>& v) {
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
void Perlin::perlin_generate(std::vector<vec3>& v) {
	for (int i = 0; i < 256; i++) {
		v.push_back(
			unit_vector(
				vec3(
					-1 + 2 * (double)rand() / RAND_MAX,
					-1 + 2 * (double)rand() / RAND_MAX,
					-1 + 2 * (double)rand() / RAND_MAX
				)
			)
		);
	}
}

