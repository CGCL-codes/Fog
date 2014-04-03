#ifndef __PAGERANK_HPP__
#define __PAGERANK_HPP__

#define DAMPING_FACTOR	0.85

//this structure will define the "attribute" of one vertex, the only member will be the rank 
// value of the vertex
struct pagerank_vert_attr{
	float rank;
};

class pagerank_program{
	public:
		static u32_t iteration_times;	//how many iterations will there be?

		//initialize each vertex of the graph
		static void init( u32_t vid, pagerank_vert_attr* this_vert )
		{
			this_vert->rank = 1.0;
		}

		//This member function is defined to process one of the out edges of vertex "vid".
		//Explain the parameters:
		// vid: the id of the vertex to be scattered.
		// this_vert: point to the attribute of vertex to be scattered.
		// num_outedge: the number of out edges of the vertex to be scattered.
		// this_edge: the edge to be scattered this time. 
		//Notes: 
		// 1) this member fuction will be used to scatter ONE edge of a vertex.
		// 2) the return value will be a pointer to the generated update.
		//	However, it is possible that no update will be generated at all! 
		//	In that case, this member function should return NULL.
		// 3) This function should be "re-enterable", therefore, no global variables
		//	should be visited, or visited very carefully.
		static update<pagerank_vert_attr>* scatter_one_edge( u32_t vid, 
					pagerank_vert_attr* this_vert, 
					u32_t num_outedge, 
					edge* this_edge )
		{
			update<pagerank_vert_attr> * ret;
			float scatter_weight = DAMPING_FACTOR *(this_vert->rank/num_outedge) + (1- DAMPING_FACTOR);
			ret = new update<pagerank_vert_attr>;
			ret->dest_vert = this_edge->dest_vert;
			ret->vert_attr.rank = scatter_weight;
			return ret;
		}

		// Gather one update. Explain the parameters:
		// vid: the vertex id of destination vertex;
		// va: the attribute of destination vertex;
		// u: the update from the "update" buffer.
		static void gather_one_update( u32_t vid, pagerank_vert_attr * dest_vert_attr, update<pagerank_vert_attr> * u )
		{
			assert( vid == u->dest_vert );
			dest_vert_attr->rank += u->vert_attr.rank;
		}
};

u32_t pagerank_program::iteration_times = 0;

#endif
