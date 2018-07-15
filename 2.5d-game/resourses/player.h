
//====================================================================
//!
//!		This library realise player class 
//!
//====================================================================

class player_c : public entity_c
{
	
	  //
	 // Virtual functions
	//

	virtual void move(void) override
	{
		// need wall checker
	}

	virtual void draw(void) override
	{
		if(hp >= 0)
			Main_window->draw(sprite);
		else
			Main_window->draw(corpse_sprite);
	}
}


