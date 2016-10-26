//#pragma OPENCL EXTENSION cl_khr_global_int32_base_atomics : enable


typedef struct{
	float4 target;
	float speed;
	float dummy1;
	float dummy2;
    float dummy3;
} Particle;

__kernel void updateParticle(__global Particle* particles,
                             __global float4* posBuffer){
	int id = get_global_id(0);  //index which is processed by OpenCL
	__global Particle *p = &particles[id];
    __global float4 *pos = &posBuffer[id];
    
    float4 delta = p->target - *pos;
    *pos += delta * p->speed;
}

__kernel void drawingParticle(__global Particle* drawing,
                             __global float4* drawingPosBuffer){
    int id = get_global_id(0);  //index which is processed by OpenCL
    __global Particle *p = &drawing[id];
    __global float4 *pos = &drawingPosBuffer[id];
    
    float4 delta = p->target - *pos;
    *pos += delta * p->speed;
    
}