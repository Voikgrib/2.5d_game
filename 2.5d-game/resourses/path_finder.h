
//================================================================================
//!
//! This library realize pathfinder functions
//!
//================================================================================

bool f_compare(const node_c *x, const node_c *y);
way_c *reconstruct_path(node_c &start, node_c &goal);

//-----------------------------------------------------------
//!
//! This class need for path_find
//!
//-----------------------------------------------------------
class node_c
{
	public:
	// coords
	int x;
	int y;
	int z;

	node_c *parent;
	node_c *child;
	
	float g; // Стоимость пути от начальной вершины. У start g(x) = 0
	float h; // Эвристическая оценка расстояние до цели. h(x)
	float f; // f(x) = g(x) + h(x)

	  //
	 // Constructors
	//
	node_c()
	{
		x = 0;
		y = 0;
		z = 0;
		g = 0;
		h = 0;
		f = 0;
		parent = NULL;
		child = NULL;
	}

	node_c(int px, int py, int pz)
	{
		x = px;
		y = py;
		z = pz;
		g = 0;
		h = 0;
		f = 0;
		parent = NULL;
		child = NULL;
	}

	  //
	 // Functions
	//
	bool is_same_state(node_c &rhs)
	{
		if(x == rhs.x && y == rhs.y && z == rhs.z)
			return true;
		else
			return false;
	}

	void goal_distance_calc(node_c &node_goal)
	{
		h = abs(x - node_goal.x) + abs(y - node_goal.y) + abs(z - node_goal.z);	
		f = g + h;	
	}

	bool is_goal(node_c &node_goal)
	{
		if(x == node_goal.x && y == node_goal.y && z == node_goal.z)
			return true;
	}
};


//-----------------------------------------------------------
//!
//! This class realize list of nodes
//!
//-----------------------------------------------------------
class list_of_nodes_c
{
	public:
	
	class list_part_c
	{
		public:

		list_part_c *next;
		node_c *current;
		list_part_c *previos;
	};

	list_part_c *first_node;
	list_part_c *cur_node;
	
	  //
	 // Constructor
	//
	list_of_nodes_c(node_c *start_node)
	{
		first_node->previos = NULL;
		first_node->current = start_node;
		first_node->next = NULL;

		cur_node->previos = NULL;
		cur_node->current = start_node;
		cur_node->next = NULL;
	}

	  //
	 // Functions
	//
	void adder(node_c *new_node)
	{
		cur_node->next = new list_part_c [1];
		cur_node->next->previos = cur_node;
		cur_node = cur_node->next;
		cur_node->current = new_node;
		first_node->next = NULL;
	}

	void remower(void)
	{
		cur_node = cur_node->previos;
		delete cur_node->next;
		cur_node->next = NULL;
	}
};

//!
//! This function find path & return way class
//!
way_c *path_finder(int xx, int yy, int zz, int aim_x, int aim_y, int aim_z)
{
	node_c start_node(xx, yy, zz);
	node_c goal_node(aim_x, aim_y, aim_z);
	node_c *cur_node = NULL;
	
	start_node.goal_distance_calc(goal_node);

	while()
	{
		if(cur_node->is_same_state(goal_node))
			return reconstruct_path(start, goal); // NOT INPLIMENTED

		// NEED A LOT OF TIME & BRAINS
	}
}


//!
//! This function compare f of two nodes
//!
bool f_compare(const node_c *x, const node_c *y)
{
	return x->f > y->f;
}

//!
//! This function reconstruct path, using nodes
//!
way_c *reconstruct_path(node_c &start, node_c &goal);
{
	// 
}







