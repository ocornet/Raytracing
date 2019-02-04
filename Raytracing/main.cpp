#include <iostream>
#include <fstream>
#include "ray.h"

using namespace std;

vec3 color(const ray& r) {
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

bool hit_sphere(const vec3& centre, float radius, const ray& r) {

	vec3 oc = r.origin() - centre;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(r.direction(), oc);
	float c = dot(oc, oc) - radius * radius;
	return (b*b - 4 * a*c) > 0;
}

vec3 colorSphere(const ray&r) {
	if (hit_sphere(vec3(0, 0, -1), 0.5, r)) {  // Si le rayon touche le ballon
		return vec3(1, 0, 0);  // Tout rough
	}
	vec3 unit_direction = unit_vector(r.direction());  // S'il ne le touche pas
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);  // Couleur normale
}



int main(int, char*) {
	ofstream file;
	file.open("output.ppm");
	int nx = 200;
	int ny = 100;
	file << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);



	//(i,j) = (0,0) en  bas à gauche
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 col = colorSphere(r);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			file << ir << " " << ig << " " << ib << endl;

		}
	}

	file.close();
	int end;
	cin >> end;
	return 0;
}