
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <ctime>

// GLOBAL CONSTANTS
sf::RenderWindow *Main_window;
sf::Clock *Main_clock;
const float Screen_high = 900;
const float Screen_lengh = 1500;

//----------------------------------//
//!     My libs included here      !//
//----------------------------------//
#include "resourses/map_big_enum.h"
#include "resourses/init.h"
#include "resourses/map.h"

c_map *Main_map_pointer;

#include "resourses/entity.h"
#include "resourses/player.h" 


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
	float screen_high = Screen_high;
	float screen_lengh = Screen_lengh;
	float backgr_high = screen_high / 733;
	float backgr_lengh = screen_lengh / 1100;

	sf::RenderWindow window(sf::VideoMode(screen_lengh, screen_high), "SHAITAN PROGA");
	window.setFramerateLimit(20);
	sf::Clock clock;
	sf::Time key_press_cooldown = sf::seconds(0.05f);
	sf::Time last_press = sf::seconds(0);
	sf::Time cur_time = sf::seconds(0);

	Main_clock = &clock;
	Main_window = &window;

	c_map main_map(70, 70, 110, "resourses/textures/pointer.png");
	Main_map_pointer = &main_map;

	player_c player("resourses/main_hero_resourses/textures/main_texture.png", "resourses/main_hero_resourses/textures/dead_texture.png");
	player.coord_set(60, 35, 35);
	player.hp = 10;
	player.max_hp = 10;

	main_map.generate(2);
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
			if(main_map.is_camera_free == true)
			{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					main_map.move('W');
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					main_map.move('S');
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					main_map.move('A');
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					main_map.move('D');
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					main_map.block_interaction('S');
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
					main_map.block_interaction('B');	
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
					main_map.up();
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
					main_map.down();
			}
			else
			{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					player.aim_set('W');
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					player.aim_set('S');
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					player.aim_set('A');
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					player.aim_set('D');
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					player.aim_set('J');
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
				main_map.change_type();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
				main_map.swap_camera_type();

			last_press = cur_time;
		}

		player.move();

		Main_window->clear();
		main_map.drawing();
		if(main_map.is_camera_free == false)
			player.draw();
		Main_window->display();
	}

	return 0;
}





