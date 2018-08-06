
//=======================================================================
//!
//! This library realize in game hud functions
//!
//=======================================================================

int in_game_hud_func(int cur_slot, hud_c* cur_hud, bool only_move)
{
		// NI
	cur_hud->pointer_sprite.setPosition(cur_hud->hud_x + 12 + 60 * cur_hud->cur_func, cur_hud->hud_y + 30);

	int i = 0;
	while(i != cur_hud->max_func)
	{
		cur_hud->icons_sprite[i].setPosition(cur_hud->hud_x + 17 + 60 * i, cur_hud->hud_y + 35);
		i++;
	}

	if(only_move == false)
		return 0;
	
	if(cur_slot != 10)
		Main_map_pointer->block_interaction('S', cur_slot);
	else
		Main_map_pointer->block_interaction('B', air);
}


void in_game_sprite_init(sf::Texture *texture_massive, hud_c *cur_hud)
{
	cur_hud->icons_textures = texture_massive;
	cur_hud->icons_sprite = new sf::Sprite [cur_hud->max_func];

	int i = 0;

	while(i != cur_hud->max_func)
	{
		//cur_hud->icons_textures[i].setSmooth(true);
		cur_hud->icons_sprite[i].setTexture(cur_hud->icons_textures[i]);
		cur_hud->icons_sprite[i].setScale(cur_hud->sprite_zoom - 1.4, cur_hud->sprite_zoom - 1.4);
		i++;
	}
}

sf::Texture *texture_massive_init(const char *file_adress)
{
	FILE *map_info = fopen(file_adress, "r");
	int max_textures = 0;
	int i = 0;
	int string_size = 100;
	int cur_texture = 0;
	char string[100] = {};
	char cur_symbol = getc(map_info);

	while(cur_symbol != EOF)
	{
		if(cur_symbol == '\n')
			max_textures++;

		cur_symbol = getc(map_info);
	}
	fclose(map_info);
	map_info = fopen(file_adress, "r");
	sf::Texture *cur_textures = new sf::Texture [max_textures];

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

	fclose(map_info);

	return cur_textures;
}

void init_in_game_hud(hud_c* cur_hud)
{
	sf::Texture *textures = texture_massive_init("resourses/ingame_hud/main.txt");
	in_game_sprite_init(textures, cur_hud);

	cur_hud->pointer_sprite.setPosition(cur_hud->hud_x + 12 + 60 * cur_hud->cur_func, cur_hud->hud_y + 30);

	int i = 0;
	while(i != cur_hud->max_func)
	{
		cur_hud->icons_sprite[i].setPosition(cur_hud->hud_x + 17 + 60 * i, cur_hud->hud_y + 35);
		i++;
	}
}












