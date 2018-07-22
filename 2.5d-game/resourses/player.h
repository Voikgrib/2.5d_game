
//====================================================================
//!
//!		This library realise player class & other helpful functions
//!
//====================================================================

class player_c : public entity_c
{
	public:
	
	// NEED INVENTORY
	// NEED STATS

	  //
	 //	Constructor
	//
	player_c(const char *texture_adress, const char *corpse_texture_adress)
	{
		texture.loadFromFile(texture_adress);
		sprite.setTexture(texture);
		corpse_texture.loadFromFile(corpse_texture_adress);
		corpse_sprite.setTexture(corpse_texture);
	}

	  //
	 // Functions
	//
	void coord_set(int zz, int yy, int xx)
	{
		cur_x = xx;
		cur_y = yy;
		cur_z = zz;

		aim_x = cur_x;
		aim_y = cur_y;
		aim_z = cur_z;
	}

	void aim_set(int move_side)
	{
		printf("is press = %c \n", move_side);

		//if(hp > 0)
		//{
			if(move_side == 'W' && (Main_map_pointer->is_num_or_air(cur_z - 1, cur_y, cur_x - 1, 1) == true))
			{
				aim_x--;
				Main_map_pointer->move('W');				
			}
			else if(move_side == 'S' && (Main_map_pointer->is_num_or_air(cur_z - 1, cur_y, cur_x + 1, 1) == true))
			{
				aim_x++;
				Main_map_pointer->move('S');
			}
			else if(move_side == 'A' && (Main_map_pointer->is_num_or_air(cur_z - 1, cur_y + 1, cur_x, 1) == true))
			{
				aim_y++;
				Main_map_pointer->move('A');
			}
			else if(move_side == 'D' && (Main_map_pointer->is_num_or_air(cur_z - 1, cur_y - 1, cur_x, 1) == true))
			{
				aim_y--;
				Main_map_pointer->move('D');
			}
			else if(move_side == 'J' && (Main_map_pointer->is_num_or_air(cur_z, cur_y, cur_x, -1) == true))
			{
				aim_z++;
				Main_map_pointer->up();
			}
		//}
	}
	  //
	 // Virtual functions
	//

	virtual void move(void) override
	{
		if(Main_map_pointer->is_num_or_air(cur_z - 1, cur_y, cur_x, -1) == true)
		{
			aim_z--;
			Main_map_pointer->down();
		}

		cur_x = aim_x;
		cur_y = aim_y;
		cur_z = aim_z;
	}

	virtual void draw(void) override
	{
		sprite.setPosition(Main_map_pointer->cur_draw_x, Main_map_pointer->cur_draw_y);
		corpse_sprite.setPosition(Main_map_pointer->cur_draw_x, Main_map_pointer->cur_draw_y);	

		Main_map_pointer->cur_x = cur_x;
		Main_map_pointer->cur_y = cur_y;
		Main_map_pointer->cur_z = cur_z;

		if(hp >= 0)
			Main_window->draw(sprite);
		else
			Main_window->draw(corpse_sprite);
	}
};




