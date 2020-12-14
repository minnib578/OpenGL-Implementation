#include "camera.h"


void Camera::F_B(GLfloat steps = 0.1f) {
	eye = eye + at * steps;
}

void Camera::R_L(GLfloat steps = 0.1f) {
	eye = eye + cross(at, up) * steps;
}

void Camera::U_D(GLfloat steps =0.1f) {
	eye = eye + up * steps;
}

void Camera::Y_axis(GLfloat angle = 0.1f) {
	at = rotate(vector3f(0, 1, 0), at, angle);
	up = rotate(vector3f(0, 1, 0), up, angle);
}

void Camera::X_axis(GLfloat angle = 0.1f) {
	vector3f t = cross(at, up);
	at = rotate(t, at, angle);
	up = rotate(t, up, angle);
}
