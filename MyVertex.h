#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>

using namespace std;

extern sf::RenderWindow window;

class MyVertex{

public:
    MyVertex(){
        isSelected_=false;

    }

    MyVertex( int number ,sf::Vector2f position,
              sf::Color color=sf::Color::Red, float size=20 ):radius_(size),number_(number){

        char num = number + '0';
        isSelected_=false;
         vertex_.setFillColor(color);
         vertex_.setRadius(size);

         vertex_.setPosition(position.x-size/2,position.y-size/2);
         vertex_.setOrigin( size/2,size/2 );
         vertex_.setOutlineThickness(5);
         vertex_.setOutlineColor(sf::Color(250, 150, 100));

         if(!font_.loadFromFile("Arial.ttf")){
             std::cout<<"błąd ładowania czcionki!"<<endl;
          }
          vertexNumber_.setFont(font_);
          vertexNumber_.setString(num);
          vertexNumber_.setCharacterSize(20); // in pixels, not points!
          vertexNumber_.setFillColor(sf::Color::White);
          vertexNumber_.setStyle(sf::Text::Bold);
          vertexNumber_.setPosition( vertex_.getPosition().x+3,vertex_.getPosition().y );
    }
    sf::Vector2f getPosition(){

        return vertex_.getPosition();
    }
    void drawMyVertex(){

        window.draw(vertex_);
        window.draw(vertexNumber_);

    }
    bool Select(){
        cout<<"zaznaczam"<<endl;
        isSelected_=true;
        vertex_.setOutlineColor(sf::Color(192, 234, 70));
        drawMyVertex();
        return 1;
    }
    bool unSelect(){
        cout<<"odznaczam"<<endl;
        isSelected_=false;
        vertex_.setOutlineColor(sf::Color(250, 150, 100));
        drawMyVertex();
        return 1;
    }
    bool isSelected(){
        return isSelected_;
    }
    float distance(sf::Vector2f pos){

        return sqrt( pow( pos.y-this->getPosition().y ,2 )
        + pow( pos.x - this->getPosition().x ,2));

    }
    float getRadius(){
        return radius_;
    }
    string getNumberString(){
        return vertexNumber_.getString();
    }
    int getNumberInt(){
        return number_;
    }
private:
    sf::CircleShape vertex_;
    sf::Text vertexNumber_;
    sf::Font font_;
    int number_;
    bool isSelected_;
    float radius_;

};




