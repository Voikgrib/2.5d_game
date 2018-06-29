
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <cstdlib>
#include <cmath>

// GLOBAL CONSTANTS
sf::RenderWindow *Main_window;
sf::Clock *Main_clock;

//----------------------------------//
//!     My libs included here      !//
//----------------------------------//
#include "resourses/init.h"
#include "resourses/map.h"

// FUNCTION DECLARE
int game_start();

//|1|//  ##   ##  ####  #  ##    #
//|2|//  # # # #  #  #     # #   #
//|3|//  #  #  #  ####  #  #  #  #
//|4|//  #     #  #  #  #  #   # #
//|5|//  #     #  #  #  #  #    ##
int main()
{
	int err_code = 0;

	err_code = game_start();

	return 0;
}

//-----------------------------------------------------------
//!
//! This function realise main game cycle & so on
//!
//-----------------------------------------------------------
int game_start()
{
	//int err_code = init_all();

	//if(err_code != 0)
	//	return err_code;

	float screen_high = 900;
	float screen_lengh = 1500;
	float backgr_high = screen_high / 733;
	float backgr_lengh = screen_lengh / 1100;

	sf::RenderWindow window(sf::VideoMode(screen_lengh, screen_high), "SHAITAN PROGA");
	window.setFramerateLimit(25);
	sf::Clock clock;
	sf::Time key_press_cooldown = sf::seconds(0.05f);
	sf::Time last_press = sf::seconds(0);
	sf::Time cur_time = sf::seconds(0);

	Main_clock = &clock;
	Main_window = &window;

	c_map main_map(5, 5, 5);

	// TEST
	main_map.map_pointer[2][2][2] = 1;
	main_map.map_pointer[2][3][2] = 1;
	main_map.map_pointer[2][4][2] = 1;
	main_map.map_pointer[1][2][2] = 0;
	main_map.map_pointer[1][3][2] = 0;
	main_map.map_pointer[1][4][2] = 0;
	main_map.map_pointer[2][1][2] = 0;
	main_map.map_pointer[3][1][2] = 0;
	// TEST

	main_map.upload_textures();

    while(Main_window->isOpen())		// Main sycle
    {
		cur_time = Main_clock->getElapsedTime();

	    sf::Event event;
    
	    while (Main_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Main_window->close();
        }

		if(last_press + key_press_cooldown < cur_time) // All actions vs map
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
				main_map.up();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
				main_map.down();

			last_press = cur_time;
		}

		Main_window->clear();
		main_map.drawing();
		Main_window->display();
	}

	return 0;
}





