#include <iostream>
#include <fstream>
#include "ray.h"

using namespace std;

vec3 color(const ray& r) {
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

float hit_sphere(const vec3& centre, float radius, const ray& r) {

	vec3 oc = r.origin() - centre;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(r.direction(), oc);
	float c = dot(oc, oc) - radius * radius;
	float discirminant = (b*b - 4 * a*c);
	if (discirminant < 0) {
		return -1.0;
	}
	else {
		return (-b - sqrt(discirminant)) / (2.0 * a);  // pas + , puisque - est le premier point qui est touché
	}

}

vec3 colorSphere(const ray&r) {

	float t = hit_sphere(vec3(0, 0, -1), 0.5, r);
	if (t > 0.0) {  // Si le rayon touche le ballon
		vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1)); 
		return 0.5* vec3( N.x() + 1, N.y() + 1, N.z() + 1 );         // Changement de couleur selon (R,G,B)
	}
	
	
	vec3 unit_direction = unit_vector(r.direction());  // S'il ne le touche pas
	t = 0.5*(unit_direction.y() + 1.0);
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