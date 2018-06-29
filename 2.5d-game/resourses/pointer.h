
//===============================================================
//!
//!		This library realize pointer & actions vs it
//!
//===============================================================
class c_pointer
{
	public:

	int coord_x;
	int coord_y;
	int coord_z;
	
	sf::Texture texture;
	sf::Sprite sprite;

	  //
     // Constructor & deconstructor
    //

	c_pointer(int xx, int yy, int zz, char *texture_adress)
	{
		coord_x = xx;
		coord_y = yy;
		coord_z = zz;

		texture.loadFromFile(texture_adress);
		sprite.setTexture(texture);
	}

	  //
	 // Return coords functions
	//

	int get_x(void);
	{
		return coord_x;
	}

	int get_y(void);
	{
		return coord_y;
	}

	int get_z(void);
	{
		return coord_z;
	}

	  //
	 // This command realize movement
    //
};














