
//=======================================================================
//!
//!		This library initialize all objects & textures
//!
//=======================================================================

int init_screen(void);

int init_all(void)
{
	int error = 0;

	if(error == 0)
		error = init_screen();

	return error;
}

int init_screen(void)
{
	float screen_high = 900;
	float screen_lengh = 1500;
	float backgr_high = screen_high / 733;
	float backgr_lengh = screen_lengh / 1100;

	sf::RenderWindow window(sf::VideoMode(screen_lengh, screen_high), "My super-puper game");
	window.setFramerateLimit(25);

	Main_window = &window;

	return 0;
}
