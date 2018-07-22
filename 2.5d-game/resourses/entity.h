
//===================================================================================
//!
//!		This library realise entity class & other help classes
//!			(this class need to nasledovanie)
//!
//===================================================================================


//!
//! This class realize one coordnode
//!
class coords_c
{
	public:

	int x;
	int y;
	int z;
};

//!
//! This class realise list of coords
//!
class way_c
{
	public:

	int cur_coord;
	int way_len;
	coords_c *coords;

	  //
	 // Constructor & deconstructor
	//
	way_c(int lengh)
	{
		cur_coord = 0;
		way_len = lengh;

		coords = new coords_c [lengh];
	}

	~way_c()
	{
		cur_coord = -1;
		delete [] coords;
	}
};

//!
//! This class realize entity for nasledovane
//!
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
	bool is_way_ready;

	// need inventory class

	sf::Texture texture;
	sf::Texture corpse_texture;
	sf::Sprite sprite;
	sf::Sprite corpse_sprite;

	  //
	 //	Constructor
	//
	//	if max_starve = -1 it is off
	/*entity_c(const char *texture_adress, const char *corpse_texture_adress)
	{
		texture.loadFromFile(texture_adress);
		sprite.setTexture(texture);
		corpse_texture.loadFromFile(corpse_texture_adress);
		corpse_sprite.setTexture(corpse_texture);
	}*/

	  //
	 // Virtual functions
	//

	//*// This function must draw entity          //*//
	virtual void draw() = 0;
	//*// This function move entity io aim coords //*//
	virtual void move() = 0;
	//*//  //*//

};








