
//=========================================================================
//!
//! This library realise hud & so on
//!
//=========================================================================

class hud_c
{
	public:

	char active_slot;
	sf::Texture main_texture;
	sf::Sprite hud_sprite;	
	sf::Sprite pointer_sprite;
	float hud_x;
	float hud_y;
	float pointer_x;
	float pointer_y;
	int cur_func;
	int max_func;
	int ret_num;
	int sprite_zoom;
	char plus_key;
	char minus_key;
	char active_key;

	sf::Sprite *icons_sprite;
	sf::Texture *icons_textures;

	hud_c(const char *main_adress)
	{
		main_texture.loadFromFile(main_adress);
	}

	  //
	 // First function of init
	//
	void first_init(int fx, int fy, int fl, int fh, int sx, int sy, int sl, int sh)
	{
		hud_sprite.setTexture(main_texture);
		hud_sprite.setTextureRect(sf::IntRect(fx, fy, fl, fh));
		pointer_sprite.setTexture(main_texture);
		pointer_sprite.setTextureRect(sf::IntRect(sx, sy, sl, sh));
	}

	  //
	 // Second function of init
	//
	void last_init(float hx, float hy, float px, float py, int zoom)
	{
		hud_x = hx;
		hud_y = hy;
		pointer_x = px;
		pointer_y = py;
		sprite_zoom = zoom;
		hud_sprite.setScale(zoom, zoom);
		pointer_sprite.setScale(zoom, zoom);
		hud_sprite.setPosition(hud_x, hud_y);
		pointer_sprite.setPosition(pointer_x, pointer_y);
	}

	  //
	 // Third init function
	//
	void third_init(char p, char m, char a, int mf)
	{
		cur_func = 0;
		max_func = mf;
		plus_key = p;
		minus_key = m;
		active_key = a;
	}

	  //
	 // Custom init function
	//
	void custom_init(void init_function(hud_c* ))
	{
		init_function(this);
	}

	  //
	 // This functon realize hud 
	//
	void call(char input_sym, class hud_c* cur_hud, int (*cur_menu_func)(int, hud_c*, bool))
	{
		if(input_sym == plus_key && cur_func != max_func - 1)
		{
			cur_func++;
			ret_num = cur_menu_func(cur_func, cur_hud, false);
		}
		else if(input_sym == minus_key && cur_func != 0)
		{
			cur_func--;
			ret_num = cur_menu_func(cur_func, cur_hud, false);
		}
		else if(input_sym == active_key)
			ret_num = cur_menu_func(cur_func, cur_hud, true);
	}

	  //
	 // This function draw hud
	//
	void draw(void)
	{
		int i = 0;
		Main_window->draw(hud_sprite);
		while(i != max_func)
			Main_window->draw(icons_sprite[i++]);
		Main_window->draw(pointer_sprite);
	}
};












