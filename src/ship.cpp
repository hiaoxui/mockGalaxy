#include "ship.h"
#include "space.h"
#include "stdio.h"
using namespace glm;

const double c = 0.1;
const double G = 0.00001;

void ship::init()
{
	r = beta = dvec3(0, 0, 0);
	front = dvec3(0, 0, -1);
	up = dvec3(0, 1, 0);
	right = cross(front, up);
	needUpdate = true;
	gamma = 1;
	t = 0;
	relative = false;
    //printf("%f %f %f %f %f %f %f %f %f\n",front.x,front.y,front.z,up.x,up.y,up.z,right.x,right.y,right.z);
}

dmat3 ship::getMatrix()
{
	if (!needUpdate)return shipMatrix;
	needUpdate = false;
    //printf("%f %f %f %f %f %f %f %f %f\n",front.x,front.y,front.z,up.x,up.y,up.z,right.x,right.y,right.z);
	return shipMatrix=dmat3(right,up,-front);
}

void ship::forward(float delta)
{
    if(delta>0.1){forward(delta-0.1);delta=0.1;}
	if (gamma > 100000)if (dot(front, beta)*delta > 0)return;
	dvec3 b = (double)delta*front;
	if (gamma < 1.0000001)beta = b;
	else beta = (beta + b / gamma + (1 - 1 / gamma)*dot(b, beta) / dot(beta, beta)*beta) / (1 + dot(b, beta));
	gamma = 1 / sqrt(1 - dot(beta, beta));
    printf("%lf %lf\n", gamma, 1-length(beta));
}

void ship::leftward(float delta)
{
	if (gamma > 100)if (dot(right, beta)*delta < 0)return;
	dvec3 b = -(double)delta*right;
	if (gamma < 1.0000001)beta = b;
	else beta = (beta + b / gamma + (1 - 1 / gamma)*dot(b, beta) / dot(beta, beta)*beta) / (1 + dot(b, beta));
	gamma = 1 / sqrt(1 - dot(beta, beta));
	printf("%f\n", gamma);
}

void ship::turn_left(float theta)
{
	front = normalize(front*(double)cos(theta) - right*(double)sin(theta));
	right = cross(front, up);
	needUpdate = true;
}

void ship::turn_up(float theta)
{
	front = normalize(front*(double)cos(theta) + up*(double)sin(theta));
	up = cross(right, front);
	needUpdate = true;
}

void ship::nextFrame(double dtao)
{
	static dvec3 p(0, 0, 0), f(0, 0, 0), temp_f(0, 0, 0), temp_beta(0, 0, 0);
	static double temp_gamma=1;

	double dt = dtao*gamma;
	t += dt;
	temp_gamma = gamma; temp_f = f; temp_beta = beta;
	f = dvec3(0, 0, 0);
	p = c*beta*gamma + temp_f*dt;
	gamma = sqrt(1 + dot(p, p) / c / c);
	r += (c*beta + p / gamma)*(dt / 2);
	double m = 100000;
	for (int i = 1; i < evm_pt->size(); i++)
	{
		dvec3 r_r = dvec3(r.x - (*evm_pt)[i].x, r.y - (*evm_pt)[i].y, r.z - (*evm_pt)[i].z);
		if (length(r_r) < (*evm_pt)[i].radius)continue;
		if (length(r_r) < m)m = length(r_r);
		f -= G*temp_gamma*r_r / pow(length(r_r), 3)*(double)(*evm_pt)[i].mass;
	}
	p = c*beta*temp_gamma + (f + temp_f)*(dt / 2);
	gamma = sqrt(1 + dot(p, p) / c / c);
	//temp_gamma += dot((f + temp_f) / 2.0, p / gamma / c) / c * dt;
	//beta = length(p) < 0.0001 ? p / gamma / c : sqrt(1 - 1 / temp_gamma / temp_gamma)*normalize(p);
	beta = p / gamma / c;
	//printf("%f %f\n", dot(normalize(beta), normalize(f)),length(beta));
	if(fabs(rand())*10<RAND_MAX)printf("%lf %lf %lf %lf %lf\n", m,G*(*evm_pt)[0].mass,gamma,length(beta),dt);

	const vector<planet> planets = evm_pt->getPlanets();
	for (planet p : planets)
	{
		vec3 r_p;
		p.getPosition(t, r_p.x, r_p.y, r_p.z);
		dvec3 r_r = r - (dvec3)r_p;
		if (length(r_r) < p.radius)r = r - r_r + normalize(r_r)*(double)p.radius;
	}
}

void ship::makeOrbit()
{
	dvec3 r_near = dvec3(100000, 0, 0);
	double m = 0;
	for (int i = 1; i < evm_pt->size(); i++)
	{
		dvec3 r_r = dvec3(r.x - (*evm_pt)[i].x, r.y - (*evm_pt)[i].y, r.z - (*evm_pt)[i].z);
		if (length(r_r) < length(r_near))
		{
			r_near = r_r;
			m = (*evm_pt)[i].mass;
		}
	}
	beta -= dot(beta, r_near) / dot(r_near, r_near) * r_near;
	beta *= sqrt(G*m / length(r_near)) / c / length(beta);
	gamma = 1 / sqrt(1 - dot(beta, beta));
	printf("%f %f %f\n", length(r_near),m,length(beta));
}
