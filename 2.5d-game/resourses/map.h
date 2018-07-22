
//===================================================================
//!
//!		This library realise map & map functions
//!		map[z,y,x]
//!
//===================================================================

const int Out_of_map = -13;

bool around_is_block(int ***map_pointer, int xx, int yy, int zz, int num);

class c_map
{
	public:

	int ***map_pointer;
	long int max_x;
	long int max_y;
	long int max_z;
	long int cur_x;
	long int cur_y;
	long int cur_z;
	int cur_draw_x;
	int cur_draw_y;
	int max_textures;
	bool is_camera_free;

	int type_of_view;
	int type_of_view_max;

	sf::Sprite ***sprite_pointer;
	sf::Texture *cur_textures;

	sf::Sprite pointer_sprite;
	sf::Texture pointer_texture;

	  //
	 // Constructor & deconstructor
	//

	c_map(int xx, int yy, int zz, const char *texture_adress)
	{
		max_x = xx;
		max_y = yy;
		max_z = zz;
		cur_x = max_x / 2;
		cur_y = max_y / 2;
		cur_z = max_z / 2;

		pointer_texture.loadFromFile(texture_adress);
		pointer_sprite.setTexture(pointer_texture);

		int gen_x = 0;
		int gen_y = 0;
		int gen_z = 0;

		is_camera_free = true;

		type_of_view_max = 1; // TYPE OF VIEW HERE
		type_of_view = 1;

		map_pointer = new int** [max_z];
		sprite_pointer = new sf::Sprite** [max_z];

		while(gen_z != max_z)
		{
			map_pointer[gen_z] = new int* [max_y];
			sprite_pointer[gen_z] = new sf::Sprite* [max_y];

			gen_y = 0;

			while(gen_y != max_y)
			{
				map_pointer[gen_z][gen_y] = new int [max_x];
				sprite_pointer[gen_z][gen_y] = new sf::Sprite [max_x];
								
				gen_x = 0;
				
				while(gen_x != max_x)
				{
					map_pointer[gen_z][gen_y][gen_x++] = -1;
				}
				gen_y++;
			}

			gen_z++;
		}

	}

	~c_map()
	{
		delete [] map_pointer;
		delete [] cur_textures;
	}

	  //
	 //  FUNCTIONS
	//

	  //
	 // This function return block on current coords 
	//
	int get_block(int xx, int yy, int zz)
	{
		if(xx < 0 || xx >= max_x || yy < 0 || yy >= max_y || zz < 0 || zz >= max_z)
			return Out_of_map;

		return map_pointer[zz][yy][xx];
	}

	  //
	 // This function change type of view
 	//
	void change_type(void)
	{
		if(type_of_view != type_of_view_max)
			type_of_view++;
		else
			type_of_view = 0;
	}

	  //
	 // Move layer up
	//
	void up()
	{
		if(cur_z != max_z - 1)
			cur_z++;
	}

	  //
	 // Move layer down
	//
	void down()
	{
		if(cur_z != 1)
			cur_z--;
	}

	  //
	 // Move in one dimension
	//
	void move(char dim)
	{
		if(dim == 'W' && cur_x != 0)
			cur_x--;
		else if(dim == 'S' && cur_x != max_x - 1)
			cur_x++;
		else if(dim == 'A' && cur_y != max_y - 1)
			cur_y++;
		else if(dim == 'D' && cur_y != 0)
			cur_y--;
	}

	  //
	 // TEST FUNCTION
	//
	void block_interaction(char sym)
	{
		if(sym == 'S')
		{
			map_pointer[cur_z - 1][cur_y][cur_x] = 0;
			sprite_pointer[cur_z - 1][cur_y][cur_x].setTexture(cur_textures[0]);
		}
		else if(sym == 'B')
		{
			map_pointer[cur_z - 1][cur_y][cur_x] = -1;
		}	
	}

	  //
	 //	Swap camera type
	//
	void swap_camera_type(void)
	{
		if(is_camera_free == true)
			is_camera_free = false;
		else
			is_camera_free = true;
	}

	  //
	 // Check is it air or floor?
	//
	bool is_num_or_air(int zz, int yy, int xx, int num)
	{
		if(zz < 0 || zz >= max_z || xx < 0 || xx >= max_x || yy < 0 || yy >= max_y)
			return false;
		if(map_pointer[zz][yy][xx] == num || map_pointer[zz][yy][xx] < 0)
			return true;

		return false;
	}


	  //
	 // Draw map
	//
	// 0 - not all visible
	// 1 - all on layer is vizible
	void drawing() // TESTED & WORKED Need x = y!
	{
		long int xx = 0;
		long int yy = 0;
		long int zz = 0;
		long int move_x = 15;		// TESTED DONT TOUCH
		long int move_y = 7;		// TESTED DONT TOUCH
		long int move_z = 16;		// TESTED DONT TOUCH
		long int draw_x = 750 + (move_x * (max_x / 2 - cur_x)) - (move_x * (max_y / 2 - cur_y));
		long int draw_y = max_z * move_z / 2.5 + (move_y * (max_x / 2 - cur_x)) + (move_y * (max_y / 2 - cur_y)) - move_z * (max_z / 2 - cur_z);

		while(zz < cur_z)
		{
			yy = 0;

			while(yy != max_y)
			{
				xx = 0;

				while(xx != max_x)
				{
					if(map_pointer[zz][yy][xx] != -1)
					{
						if(draw_x >= -move_z && draw_y >= -move_z * 2 && draw_x <= Screen_lengh && draw_y <= Screen_high)
						{
							sprite_pointer[zz][yy][xx].setColor(sf::Color(255, 255, 255));

							if((cur_z - zz) * 10 > 255)
								sprite_pointer[zz][yy][xx].setColor(sf::Color(0, 0, 0));
							else if(zz != cur_z - 1)
								sprite_pointer[zz][yy][xx].setColor(sf::Color(255 + ((zz - cur_z) * 10), 255 + ((zz - cur_z) * 10), 255 + ((zz - cur_z) * 10))); // need rework (more dark for cur_z - 2 level)
							else
								sprite_pointer[zz][yy][xx].setColor(sf::Color(255, 255, 255));

							if(xx != 0 && yy != 0 && zz != 0 && xx != max_x - 1 && yy != max_y - 1 && zz != cur_z && zz != cur_z - 1)
							{
								if(around_is_block(map_pointer, xx, yy, zz, air) == true)
									{
										sprite_pointer[zz][yy][xx].setPosition(draw_x, draw_y);
										Main_window->draw(sprite_pointer[zz][yy][xx]);
									}
							}
							else if(xx != 0 && yy != 0 && zz != 0 && xx != max_x - 1 && yy != max_y - 1 && zz == cur_z - 1)
							{
								if(type_of_view == 0 && around_is_block(map_pointer, xx, yy, zz, air) == true)
									{
										sprite_pointer[zz][yy][xx].setPosition(draw_x, draw_y);
										Main_window->draw(sprite_pointer[zz][yy][xx]);
									}
								else if(type_of_view == 1)
									{
										sprite_pointer[zz][yy][xx].setPosition(draw_x, draw_y);
										Main_window->draw(sprite_pointer[zz][yy][xx]);
									}
							}
							else if(xx == 0 || yy == 0 || zz == 0 || xx == max_x - 1 || yy == max_y - 1 || zz == cur_z)
							{
								sprite_pointer[zz][yy][xx].setPosition(draw_x, draw_y);
								Main_window->draw(sprite_pointer[zz][yy][xx]);
							}
						}
						/*if(type_of_view == 1)
						{
							sprite_pointer[zz][yy][xx].setPosition(draw_x, draw_y);
							Main_window->draw(sprite_pointer[zz][yy][xx]);
						}*/
					}

					if(is_camera_free == true && xx == cur_x && yy == cur_y && zz == cur_z - 1)
					{
						pointer_sprite.setPosition(draw_x, draw_y);
						Main_window->draw(pointer_sprite);
					}
					else if(is_camera_free == false && xx == cur_x && yy == cur_y && zz == cur_z - 1)
					{
						cur_draw_x = draw_x;
						cur_draw_y = draw_y;
					}

					draw_x = draw_x + move_x;
					draw_y = draw_y + move_y;
					xx++;
				}

				draw_x = draw_x - (xx + 1) * move_x;
				draw_y = draw_y - (xx - 1) * move_y;
				yy++;	
			}
			
			draw_x = draw_x + xx * move_x;
			draw_y = draw_y - yy * move_y;
			draw_y = draw_y - move_z;
			zz++;
		}
	}

	  //
	 // This function upload textures for map
	//
	void upload_textures() // TESTED & WORKED
	{
		int xx = 0;
		int yy = 0;
		int zz = 0;
		FILE* map_info = fopen("resourses/textures/enviroment/map/map_info.txt","r");
		int i = 0;
		int string_size = 100;
		char string[100] = {};
		char cur_symbol = 0;
		int cur_texture = 0;
		max_textures = 0;

		cur_symbol = getc(map_info);

		while(cur_symbol != EOF)
		{
			if(cur_symbol == '\n')
				max_textures++;

			cur_symbol = getc(map_info);
		} 
		fclose(map_info);
		//fscanf(map_info, "%[0-9]", string);
		//max_textures = atoi(string);


		map_info = fopen("resourses/textures/enviroment/map/map_info.txt","r");
		cur_textures = new sf::Texture [max_textures];

		while(cur_texture != max_textures)
		{
			i = 0;
			while(i != string_size)
				string[i++] = '\0';

			cur_symbol = getc(map_info);
			while(cur_symbol == ' ' || cur_symbol == '\t' || cur_symbol == '\n')
				cur_symbol = getc(map_info);

			ungetc(cur_symbol, map_info);

			fscanf(map_info, "%[^\n]", string);

			printf("%s\n", string);

			cur_textures[cur_texture].loadFromFile(string);
			cur_texture++;
		}

		while(zz != max_z)
		{
			yy = 0;

			while(yy != max_y)
			{
				xx = 0;

				while(xx != max_x)
				{
					cur_texture = map_pointer[zz][yy][xx];

					if(cur_texture != -1)
						sprite_pointer[zz][yy][xx].setTexture(cur_textures[cur_texture]);

					xx++;
				}
				yy++;
			}
			zz++;
		}

		fclose(map_info);
	}

	  //
	 // This gunction generate map using preset num
	//
	//	1 = flat map
	//  2 = hills
	//
	void generate(int preset)
	{
		long int xx = 0;
		long int yy = 0;
		long int zz = 0;
		long int rand_x = 0;
		long int rand_y = 0;
		long int rand_z = 0;
		long int rand_a = 0;
		long int rand_b = 0;
		long int rand_c = 0;	
		int i = 0;
		int max_i = 0;
		int cur_ore = 0;

		srand(time(0));

		if(preset == 1)
		{
			while(zz <= (max_z / 2))
			{
				yy = 0;
				while(yy != max_y)
				{
					xx = 0;
					while(xx != max_x)
					{
						if(zz == (max_z / 2))
							map_pointer[zz][yy][xx] = grass_floor;
						else if(zz < (max_z / 2) && zz > (max_z / 2) - 7)
							map_pointer[zz][yy][xx] = dirt_block;
						else if(zz <= (max_z / 2) - 7)
							map_pointer[zz][yy][xx] = stone_block;

						xx++;
					}
					yy++;
				}
				zz++;
			}
		}
		else if(preset = 2) // MABY WORKED
		{
			max_i = max_x * max_y / 300;
			while(i != max_i)
			{
				rand_x = rand() % max_x;
				rand_y = rand() % max_y;
				rand_z = (max_z / 3) + (rand() % (max_z / 3));

				rand_a = rand() % 5 + 1;
				rand_b = rand() % 5 + 1;
				rand_c = rand() % 5 + 1;
				
				zz = rand_z + 2;
				yy = 0;
				xx = 0;

				while(zz != 0)
				{
					yy = 0;
					while(yy != max_y)
					{
						xx = 0;
						while(xx != max_x)
						{
							if(((rand_x - xx) / rand_b) * ((rand_x - xx) / rand_b) + ((rand_y - yy) / rand_a) * ((rand_y - yy) / rand_a) < (rand_z - zz))	
								map_pointer[zz][yy][xx] = stone_block;
							if(((rand_x - xx) / rand_b) * ((rand_x - xx) / rand_b) + ((rand_y - yy) / rand_a) * ((rand_y - yy) / rand_a) == (rand_z - zz))
								map_pointer[zz][yy][xx] = dirt_block;								
							if(((rand_x - xx) / rand_b) * ((rand_x - xx) / rand_b) + ((rand_y - yy) / rand_a) * ((rand_y - yy) / rand_a) == (rand_z - zz) + 1 && map_pointer[zz + 1][yy][xx] == air)
								map_pointer[zz][yy][xx] = grass_floor;

							xx++;
						}
						yy++;
					}
					zz--;
				}

				//map_pointer[rand_z][rand_y][rand_x] = stone_block;

				i++;
			}

			xx = 0;
			yy = 0;
			zz = 0;

			while(zz <= max_z)
			{
				yy = 0;
				while(yy != max_y)
				{
					xx = 0;
					while(xx != max_x)
					{
						if(zz == 0)
							map_pointer[zz][yy][xx] = unbreaking_core;
						else if(zz < (max_z / 3) && zz > (max_z / 3) - 7 && map_pointer[zz][yy][xx] != 2)
							map_pointer[zz][yy][xx] = dirt_block;
						else if(zz <= (max_z / 3) - 7)
							map_pointer[zz][yy][xx] = stone_block;
						else if(zz != 0 && zz != max_z - 1 && map_pointer[zz - 1][yy][xx] == 0 && map_pointer[zz + 1][yy][xx] == air)
						{
							//map_pointer[zz][yy][xx] = 1;

							rand_c = rand() % 10 + (max_z / 30) - (zz / 15);
							
							if(yy != max_y - 1 && map_pointer[zz][yy + 1][xx] == grass_floor_with_tree)
								rand_c++;
							if(yy != 0 && map_pointer[zz][yy - 1][xx] == grass_floor_with_tree)
								rand_c++;
							if(xx != max_x - 1 && map_pointer[zz][yy][xx + 1] == grass_floor_with_tree)
								rand_c++;
							if(xx != 0 && map_pointer[zz][yy][xx - 1] == grass_floor_with_tree)
								rand_c++;

							if(rand_c >= 7)
								map_pointer[zz][yy][xx] = grass_floor_with_tree;
							else
								map_pointer[zz][yy][xx] = grass_floor;

						}
						xx++;
					}
					yy++;
				}
				zz++;
			}

			// ore generation here (+- worked)
			
			i = 0;
			max_i = max_x * max_y * max_z / 5000;

			while(i != max_i)
			{
				rand_x = rand() % max_x;
				rand_y = rand() % max_y;
				rand_z = rand() % (max_z - 1) + 1;
				rand_a = rand() % 100;
	
				if(map_pointer[rand_z][rand_y][rand_x] == stone_block)
				{
					if(rand_a + rand_z >= 70)
						map_pointer[rand_z][rand_y][rand_x] = coal_ore;
					if(rand_a + rand_z < 70 && rand_a + rand_z >= 50)
						map_pointer[rand_z][rand_y][rand_x] = copper_ore;
					if(rand_a + rand_z < 50)
						map_pointer[rand_z][rand_y][rand_x] = iron_ore;
				}

				cur_ore = map_pointer[rand_z][rand_y][rand_x];
				rand_a = rand() % 10;
				rand_b = rand() % 10;
				rand_c = rand() % 3;

				xx = rand_x - rand_a;
				yy = rand_y - rand_b;
				zz = rand_z - rand_c;

	
				while(zz != rand_z + rand_c)
				{
					yy = rand_y - rand_b;
					while(yy != rand_y + rand_b)
					{
						xx = rand_x - rand_a;
						while(xx != rand_x + rand_a)
						{
							if(xx >= 0 && xx <= max_x - 1 && yy >= 0 && yy <= max_y - 1 && zz > 0 && zz <= max_z - 1)
							{
								if((rand_x - xx) * (rand_x - xx) + (rand_y - yy) * (rand_y - yy) <= (rand_a * rand_b) && (map_pointer[zz][yy][xx] == stone_block))
									map_pointer[zz][yy][xx] = cur_ore;
							}
							xx++;
						}
						yy++;
					}
					zz++;
				}
				i++;
			}

			// Cave generation here

			// i am lazy			

		}
		else
			printf("{!} Invalid preset num!\n");
	}
};


bool around_is_block(int ***map_pointer, int xx, int yy, int zz, int num)
{
	if(map_pointer[zz - 1][yy][xx] == num ||
	   map_pointer[zz - 1][yy][xx - 1] == num ||
	   map_pointer[zz - 1][yy][xx + 1] == num ||
	   map_pointer[zz - 1][yy - 1][xx] == num ||
	   map_pointer[zz - 1][yy - 1][xx + 1] == num ||
	   map_pointer[zz - 1][yy - 1][xx - 1] == num ||
	   map_pointer[zz - 1][yy + 1][xx] == num ||
	   map_pointer[zz - 1][yy + 1][xx + 1] == num ||
	   map_pointer[zz - 1][yy + 1][xx - 1] == num ||	   
	   map_pointer[zz][yy - 1][xx] == num ||
	   map_pointer[zz][yy - 1][xx - 1] == num ||
	   map_pointer[zz][yy - 1][xx + 1] == num ||
	   map_pointer[zz][yy + 1][xx] == num ||
	   map_pointer[zz][yy + 1][xx - 1] == num ||
	   map_pointer[zz][yy + 1][xx + 1] == num ||
	   map_pointer[zz][yy][xx - 1] == num ||
	   map_pointer[zz][yy][xx + 1] == num ||
	   map_pointer[zz + 1][yy][xx] == num ||
	   map_pointer[zz + 1][yy][xx - 1] == num ||
	   map_pointer[zz + 1][yy][xx + 1] == num ||
	   map_pointer[zz + 1][yy - 1][xx] == num ||
	   map_pointer[zz + 1][yy - 1][xx - 1] == num ||
	   map_pointer[zz + 1][yy - 1][xx + 1] == num ||
	   map_pointer[zz + 1][yy + 1][xx] == num ||
	   map_pointer[zz + 1][yy + 1][xx - 1] == num ||
	   map_pointer[zz + 1][yy + 1][xx + 1] == num
	  )
		return true;

	return false;
}










