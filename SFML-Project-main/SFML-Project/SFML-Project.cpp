#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>
#include <sstream>



//Our files
#include "game_objects.h"
#include "level_manager.h"

//SFML files
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <SFML/Audio.hpp> 
#include <SFML/System/Clock.hpp> 

//SFML namespace
using namespace sf;

using namespace std;

//file out function
void saveData(string player_name,int levelHere, int timeOn) {
    /*
    string path = "playerStats.txt";
    ofstream writer;
    writer.open(path);
    if(writer.is_open())
    {
       
        writer << player_name << "," << levelHere << "," << timeOn;
                    
    }
    else
    {
        cout << "error reading from file" << endl;
    }
    */
}

void delete_save() {
    /*
    string path = "playerStats.txt";
    string name , line;
    int level, seconds;
    string level_string, seconds_string;
    ifstream reader; // Open file in truncate mode
    reader.open(path);
    
    if (reader.is_open()) {
        while (getline(reader, line)) {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, level_string, ',');
            stringstream level_stream(level_string);
            level_stream >> level;
            getline(ss, seconds_string, ',');
            stringstream seconds_stream(seconds_string);
            seconds_stream >> seconds;
            reader.close();
        }
    }
    else {
        cout << "Could not find player in file." << endl;
    }
    ofstream writer;
    writer.open(path);
    /*
    if (writer.is_open()) {
        writer << name << ',' << 1  << ',' << seconds;
    }
    */
}



int main() {
    //Variables
    string player_name;
    int user_selection;
    //Player input variables
    bool is_left_pressed = false;
    bool is_right_pressed = false;
    bool is_jump_pressed = false;
    bool is_down_pressed = false;
    //file variables
    string userOn;
    int levelOn;
    

    //sky background
    Texture background_texture;
    background_texture.loadFromFile("background.PNG");

    // Create a sprite and set the texture
    Sprite background_sprite;
    background_sprite.setTexture(background_texture);




    // get data from file



    string path = "playerStats.txt";
    ifstream reader;
    reader.open(path);
    



        //SOUND

    vector<string> audioFiles = {
       "jump.wav",   //jump                          0    keycodes for calling sound
       "pop.wav",  //complete level                  1
       "explode.wav", //death                        2
       "click.wav",  //click                         3
       "notify.wav", //notification ping             4
       "background.wav"//background music            5
    };
    vector<SoundBuffer> soundBuffers(audioFiles.size()); //storing sound buffers
    vector<Sound> sounds(audioFiles.size());

    //creating loop to set each sound to each buffer
    for (int i = 0; i < audioFiles.size(); ++i) {
        if (!soundBuffers[i].loadFromFile(audioFiles[i])) {
            cout << "Error loading sound file: " << audioFiles[i] << endl;
            return -1;
        }
        sounds[i].setBuffer(soundBuffers[i]);
    }

    sounds[5].setPitch(0.75f); //speed modifier and pitch
    sounds[5].setLoop(true); //loops forever
    sounds[5].setVolume(90.0f); //100 is default and max
    sounds[5].play();







    //Level manager
    map_Manager map = map_Manager();
    map.set_Map_1();



    //Inital message
    cout << "Welcome to Primal Tactics!" << endl;
    //New game or continue
    cout << "1. Start New Game" << endl;//<< "2. Continue From Existing Save File" << endl;
    //Get user selection
    cin >> user_selection;
    switch (user_selection) {
    case 1:
        //New game
        cout << endl << "Enter Your Name:" << endl;
        cin >> player_name;





        break;
        
    default:

        cout << endl << "Invalid input!" << endl;
        return -1;
        break;
    }
    //Some of the following code is based on the offical SFML documentation (https://www.sfml-dev.org/documentation/2.6.2/)
    //Create window with SFML
    RenderWindow window(VideoMode(1400, 1000), "Primal Tactics", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60); //Set the framerate limit to 60fps
    //SFML input detection
    Event input_event;
    //Clock that records the time between each frame
    Clock delta_clock;
    //Time between each frame
    //IMPORTANT: Make sure to mutliply any movement by delta so that it is frame independant!
    Time delta;

    //Main game loop -- exits when the window is closed
    while (window.isOpen()) {
        //reset player forced jump if not on jump pad, otherwise force a jump

        //game_object* firstObject = levels.get_current_level()->at(0);



        //Detect user inputs
        while (window.pollEvent(input_event)) {

            //Check if inputs pressed down
            if (input_event.type == Event::KeyPressed) {


            }
            //Check if inputs are released 
            else if (input_event.type == Event::KeyReleased) {



            }

            //Close the window if the close window button is pressed or the escape button is pressed
            if (input_event.type == Event::Closed || (input_event.type == Event::KeyPressed && input_event.key.code == Keyboard::Escape)) {

                //Close the window
                sounds[2].play();

                window.close();
            }
        }



        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

        //Main game logic

        //Run the update function for every object in the current level
        map.update_all_objects(delta, is_left_pressed, is_right_pressed, is_jump_pressed, is_down_pressed);

        

        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-



        //Render
        //Clear the previous frame and color the background with light blue
        window.clear();
        window.draw(background_sprite);
        //Draw every object in the level
        for (auto hex : map.get_all_hexes()) {
            window.draw(hex->get_shape());  // You probably only need to draw the shape
        }
        map.draw_all(window);
        //Display the new frame
        window.display();

        //Returns the time elapsed from the last restart (time between each frame)
        delta = delta_clock.restart();
    }

    //Delete the map arrays
    map.delete_maps();

    return 1;
}



    









  