#pragma once
#include <iostream>
#include <string>
using namespace std;

//SFML files
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
//SFML namespace
using namespace sf;






//class hex;
class game_Object {


public:

    Vector2f inital_position; //The inital position of the object. Used to reset the objects position
    
    RectangleShape shape; //The object's shape
    Texture texture; //The object's texture
    Sprite sprite;
    //Called every frame (delta is the time between frame in seconds)
    virtual void update(float delta) { update_sprite(); }

    //Called every time a collision is detected by the level manager
    virtual int on_collision(string type_of_other_object, Vector2f other_position, Vector2f other_size) { return 0; }

    //Resets the position of the object
    void reset_position() {
        shape.setPosition(inital_position);
    }



    //Updates the sprite
    virtual void update_sprite() {
        //Update the sprites position to be the same as the shape's position
        set_sprite_position(Vector2f(get_x_position(), get_y_position()));
    }

    //Getters
    Vector2f get_inital_position() { return inital_position; };
    float get_x_position() { return shape.getPosition().x; };
    float get_y_position() { return shape.getPosition().y; };
    float get_width() { return shape.getSize().x; };
    float get_height() { return shape.getSize().y; };
    virtual void draw(sf::RenderWindow& window) = 0;
    RectangleShape get_shape() { return shape; };
    Color get_color() { return shape.getFillColor(); };
    Sprite get_sprite() { return sprite; }
    //Setters
    void set_inital_position(float x_position, float y_position) { inital_position.x = x_position; inital_position.y = y_position; };
    void set_position(float x_position, float y_position) { shape.setPosition(Vector2f(x_position, y_position)); };
    void set_size(float width, float height) { shape.setSize(Vector2f(width, height)); };
    
    void set_color(Color color) { shape.setFillColor(color); };
    void set_sprite_position(Vector2f position) { sprite.setPosition(position); };

    game_Object(float width, float height, Color color) {
        
        set_size(width, height);
        set_color(color);
       
    }
};

class tile;

class Hex : public game_Object {
public:
    enum terrain_Type { plain, forest, water, mountain };
private:


    ConvexShape hex_shape;
    int x, y; // axial coordinates

    tile* tile_ptr = nullptr;
    terrain_Type terrain = plain;

    


public:
    void set_Terrain(terrain_Type terrain) {
        this->terrain = terrain;
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(hex_shape);
    }
    

    const vector<pair<int, int>> axial_directions = {
    {+1, 0}, {+1, -1}, {0, -1},
    {-1, 0}, {-1, +1}, {0, +1}
    };
    //pair<int,int>cords = axial_directions[1];
    terrain_Type get_Terrain() {
        return terrain;
    }
    
    Hex(int x, int y, float size, Color color) : game_Object(0, 0, color) {
        this->x = x;
        this->y = y;

        hex_shape.setPointCount(6);
        float angle_deg, angle_rad;

        for (int i = 0; i < 6; ++i) {
            angle_deg = 60 * i; // flat-top
            angle_rad = 3.14159265f / 180.f * angle_deg;
            float px = size * cos(angle_rad);
            float py = size * sin(angle_rad);
            hex_shape.setPoint(i, sf::Vector2f(px, py));
        }

        hex_shape.setPosition(x, y);
        hex_shape.setFillColor(color);
        hex_shape.setOutlineThickness(5.f);
        hex_shape.setOutlineColor(Color::Black);

        
    }

    ConvexShape& get_shape() {
        return hex_shape;
    }

};
class tile : public game_Object {
public: 
    enum tile_Type { elephant, rhino, tiger, chimp, leopard, dog, cobra, eagle, human };
private:
    string name;
    int x, y;
    tile_Type animal;
    void set_Tile_Type(tile_Type animal) {
        this->animal = animal;
    }
    Hex* hex_ptr = nullptr;
    //top, top right, bottom right, bottom, bottom left, top left
    int spikes[6] = { 0, 0, 0, 0, 0, 0 };
public:

    void set_Tile_Cords(int x, int y) {
        set_inital_position(x, y);
        set_position(x, y);
        sprite.setPosition(x, y);
    }

    void move_Tile() {

    }

    tile(tile_Type animal, string name, enum animal, float width, float height, Color color): game_Object(width, height, color) {
        this->name = name;
        this->animal = animal;
        if (animal == human) {
            //texture.loadFromFile("platform.PNG");
            texture.setRepeated(false);
            sprite.setTexture(texture);
            sprite.setScale(3.125, 3.125);
            
            
        }
    }



   




public:
    tile_Type get_Tile_Type() {
        return animal;
    }

    int rotate_spikes(string left_right) {

        if (left_right == "left") {
            int temp = spikes[0];
            for (int i = 0; i < 5; i++) {
                spikes[i] = spikes[i + 1];
            }
            spikes[5] = temp;
        }
        else if (left_right == "right") {
            int temp = spikes[5];
            for (int i = 5; i > 0; i--) {
                spikes[i] = spikes[i - 1];
            }
            spikes[0] = temp;
        }

        return 0;

    }
    
};



class board : public game_Object {
private:
    map<pair<int, int>, Hex*> grid;
    int x, y;



public:


    board(int x, int y, float size, Color color) : game_Object(0, 0, color) {
        
        this->x = x;
        this->y = y;
        for (int j = 1; j < 12; j++) {
            for (int k = 1; k < 10; k++) {
                if (j % 2 == 0){
                    grid[{j, k}] = new Hex((j * 80) + x, ((k * 90) + y) - (size-5), size, Color::White);
                }
                else {
                    grid[{j, k}] = new Hex((j * 80) + x, ((k * 90) + y), size, Color::White);
                }
                
            }
        }
    }
    void draw(RenderWindow& window) {
        for (auto& [cords, hex] : grid) {
            window.draw(hex->get_shape());
        }
    }
    Hex* get_hex_ptr(int x, int y) {
        std::pair<int, int> cords = { x, y };
        auto it = grid.find(cords);
        if (it != grid.end()) {
            return it->second;
        }
    }
    void set_hex_terrain(int x, int y, Hex::terrain_Type terrain) {
        Hex* hex = get_hex_ptr(x, y);
        if (hex) {
            hex->set_Terrain(terrain); // Make sure this is public
            if (terrain == Hex::mountain) {
                
                hex->get_shape().setFillColor(Color{ 128, 128, 128 });
            }
            else if (terrain == Hex::water) {
                hex->get_shape().setFillColor(Color{ 0, 255, 255 });
            }
            else if (terrain == Hex::forest) {
                hex->get_shape().setFillColor(Color{144, 238, 144});
            }
            else if (terrain == Hex::plain) {
                hex->get_shape().setFillColor(Color::White);
            }

            
        }
    }
    vector<Hex*> get_all_hexes() {
        vector<Hex*> hexes;
        for (auto& [coords, hex] : grid) {
            hexes.push_back(hex);
        }
        return hexes;
    }
};

class players_Tiles : public game_Object {
public:

private:

};