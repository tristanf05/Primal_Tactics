#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

#include "game_objects.h"

//SFML files
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
//SFML namespace
using namespace sf;


class map_Manager {

private:
    board* game_board = nullptr;

public:
    map_Manager() {
        game_board = new board(400, 50, 50, Color::Transparent);
    }

    ~map_Manager() {
        delete game_board;
    }

    void draw_all(RenderWindow& window) {
        if (game_board)
            game_board->draw(window);
    }

    void update_all(float delta) {
        // If you add animations or logic to Hex, you can call it here
    }


    
    
    

    

    //Run update function for all objects in the current level
    void update_all_objects(Time delta, bool left_input, bool right_input, bool up_input, bool down_input) {
       
        
    }

    //Detects collisions between objects every frame
    void detect_collisions(Time delta) {
       
    }

    //Reset the positions of all objects in the level
    void reset_level() {
        
    }

    //Delete all of the levels. Called when the game is ended
    void delete_maps() {
        
    }

    //Getters & Setters
    
    vector<Hex*> get_all_hexes() {
        return game_board->get_all_hexes();
    }
    
    //Setters
    void set_Map_1() {
        game_board->set_hex_terrain(3, 4, Hex::water);
        game_board->set_hex_terrain(4, 4, Hex::water);
        game_board->set_hex_terrain(5, 4, Hex::water);
    }
    void set_Map_2() {
       
    }
    void set_Map_3() {
        
    }

    
    //Getters
    board* get_board() {
        return game_board;
    }
    
};