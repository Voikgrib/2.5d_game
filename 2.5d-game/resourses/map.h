
//===================================================================
//!
//!		This library realise map & map functions
//!		map[z,y,x]
//!
//===================================================================

class c_map
{
	public:

	int ***map_pointer;
	int max_x;
	int max_y;
	int max_z;
	int cur_x;
	int cur_y;
	int cur_z;

	sf::Sprite ****sprite_pointer;
	sf::Texture *textures;
	
	  //
	 // Constructor & deconstructor
	//

	c_map(int xx, int yy, int zz)
	{
		max_x = xx;
		max_y = yy;
		max_z = zz;
		cur_x = max_x / 2;
		cur_y = max_y / 2;
		cur_z = max_z / 2;

		int gen_x = 0;
		int gen_y = 0;
		int gen_z = 0;

		map_pointer = new int** [max_z];
		sprite_pointer = new sf::Sprite*** [max_z];

		while(gen_z != max_z)
		{
			map_pointer[gen_z] = new int* [max_y];
			sprite_pointer[gen_z] = new sf::Sprite** [max_y];

			gen_y = 0;

			while(gen_y != max_y)
			{
				map_pointer[gen_z][gen_y] = new int [max_x];
				sprite_pointer[gen_z][gen_y] = new sf::Sprite* [max_x];
								
				gen_x = 0;
				
				while(gen_x != max_x)
				{
					map_pointer[gen_z][gen_y][gen_x++] = 0;
				}
				gen_y++;
			}

			gen_z++;
		}

		textures = new sf::Texture [2]; // TEST
		textures[0].loadFromFile("resourses/textures/enviroment/map/dirt_block.png");
		textures[1].loadFromFile("resourses/textures/enviroment/map/grass_floor.png");
	}

	~c_map()
	{
		delete [] map_pointer;
		delete [] textures;
	}

	  //
	 //  FUNCTIONS
	//

	void up()
	{
		if(cur_z != max_z)
			cur_z++;
	}

	void down()
	{
		if(cur_z != 0)
			cur_z--;
	}

	void drawing() // TESTED
	{
		sf::Sprite sprite_0[500]; // TEST
		//sf::Sprite sprite_1;
		int i = 0;

		for(i = 0; i != 500; i++)
			sprite_0[i].setTexture(textures[0]);

		i = 0;
			

		//sprite_1.setTexture(textures[1]);
	
		int xx = 0;
		int yy = 0;
		int zz = 0;
		float draw_x = 400;
		float draw_y = 400;
		float move_x = 15;		// TESTED DONT TOUCH
		float move_y = 7;		// TESTED DONT TOUCH
		float move_z = 16;		// TESTED DONT TOUCH

		while(zz < cur_z) // swap to cur_z
		{
			yy = 0;

			while(yy != max_y)
			{
				xx = 0;

				while(xx != max_x)
				{
					sprite_0[i].setPosition(draw_x, draw_y);
					Main_window->draw(sprite_0[i]);

					i++;
					draw_x = draw_x + move_x;
					draw_y = draw_y + move_y;
					xx++;
				}

				draw_x = draw_x - (xx + 1) * move_x;
				draw_y = draw_y - (xx - 1) * move_y;
				yy++;	
			}
			
			draw_x = draw_x + xx * move_x;
			draw_y = draw_y - xx * move_y;
			draw_y = draw_y - move_z;
			zz++;
		}
	}
};












