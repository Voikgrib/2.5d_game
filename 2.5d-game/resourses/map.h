
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
	int max_textures;

	sf::Sprite ***sprite_pointer;
	sf::Texture *cur_textures;
	
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
	 // Move layer up
	//
	void up()
	{
		if(cur_z != max_z)
			cur_z++;
	}

	  //
	 // Move layer down
	//
	void down()
	{
		if(cur_z != 0)
			cur_z--;
	}

	  //
	 // Draw map
	//
	void drawing() // TESTED & WORKED
	{
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
					if(map_pointer[zz][yy][xx] != -1)
					{
						sprite_pointer[zz][yy][xx].setPosition(draw_x, draw_y);
						Main_window->draw(sprite_pointer[zz][yy][xx]);
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
			draw_y = draw_y - xx * move_y;
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

		fscanf(map_info, "%[0-9]", string);
		max_textures = atoi(string);

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

			printf("%s\n\n", string);

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
	//
	void generate(int preset)
	{
		int xx = 0;
		int yy = 0;
		int zz = 0;

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
							map_pointer[zz][yy][xx] = 1;
						else
							map_pointer[zz][yy][xx] = 0;

						xx++;
					}
					yy++;
				}
				zz++;
			}
		}
		else
			printf("{!} Invalid preset num!\n");
	}
};












