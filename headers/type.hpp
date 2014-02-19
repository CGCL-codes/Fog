#ifndef __TYPES_H__
#define __TYPES_H__

typedef unsigned int u32_t;
typedef unsigned long long u64_t;

struct edge{
    unsigned int dst_vert;                                         
    float edge_weight;
}__attribute__ ((aligned(8)));                                     

struct vertex_index{
    unsigned long long  offset;                                    
}__attribute__ ((aligned(8)));   

template<typename T>
struct update{
	unsigned int dst_vert;
	T vert_attribute;
}__attribute__ ((__packed__));

#endif

