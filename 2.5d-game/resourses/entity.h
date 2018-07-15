
//====================================================================
//!
//!		This library realise entity class 
//!			(this class need to nasledovanie)
//!
//====================================================================


class entity_c
{
	public:

	int hp;
	int max_hp;
	int max_starve;
	int starve;
	int cur_x;
	int cur_y;
	int cur_z;
	int aim_x;
	int aim_y;
	int aim_z;

	// need inventory class

	sf::Texture texture;
	sf::Texture corpse_texture;
	sf::Sprite sprite;
	sf::Sprite corpse_sprite;

	  //
	 //	Constructor
	//
	//	if max_starve = -1 it is off
	entity_c(int xx, int yy, int zz, int cur_hp, int cur_starve, const char *texture_adress, const char *corpse_texture_adress)
	{
		texture.loadFromFile(texture_adress);
		sprite.setTexture(texture);
		corpse_texture.loadFromFile(corpse_texture_adress);
		corpse_sprite.setTexture(corpse_texture);

		cur_x = xx;
		cur_y = yy;
		cur_z = zz;
		max_hp = cur_hp;
		hp = cur_hp;
		max_starve = cur_starve;
		starve = cur_starve;
	}

	  //
	 // Virtual functions
	//

	//*// This function must draw entity          //*//
	virtual void draw() = 0;
	//*// This function move entity io aim coords //*//
	virtual void move() = 0;
	//*//  //*//

};










