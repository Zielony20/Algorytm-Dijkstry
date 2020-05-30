#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>

using namespace std;

extern sf::RenderWindow window;
extern const int height;
extern const int width;


class InfoText{
public:
    InfoText(){

        font_.loadFromFile("Arial.ttf");
        info_.setFont(font_);
        info_.setString(text_);
        info_.setPosition(width*1/16,height*(60)/64);
    }
    InfoText( string text  ):text_(text){
        font_.loadFromFile("Arial.ttf");
        info_.setFont(font_);
        info_.setString(text_);
        info_.setPosition(width*1/16,height*(60)/64);
    }
    void displayInfoText(string text = ""){
        if(text=="") text=text_;
        info_.setString(text);
        window.draw(info_);
    }
    string getText(){
        return text_;
    }
private:

    string text_;
    sf::Text info_;
    sf::Font font_;

};
class DistanceTable{
public:

    DistanceTable(){

    }
    void MakeTable(int Size, int dist[]){
        //Tło
        sf::Texture background_texture;
        background_texture.loadFromFile("zwoj.png");
        sf::Sprite sprite;
        sf::Sprite background_sprite(background_texture);

        sf::RenderTexture render_texture;
        render_texture.create(width*4/16, height);
        //...
        background_sprite.move(1, 0);
        render_texture.clear();
        render_texture.draw(background_sprite);
        render_texture.display();
        const sf::Texture& texture = render_texture.getTexture();
        sprite.setTexture(texture);
        sprite.setPosition(width*12/16,0);
        window.draw(sprite);


        sf::RectangleShape b[64];
        sf::Text* t = new sf::Text[Size];
        sf::Text* t2 = new sf::Text[Size];
        sf::Text vertex,distance;

        int dottedLinePosition = width * 12 / 16 - 5;
        int xDistance = width * 14 / 16 + 8;
        int yDistance = height * 10 / 64;
        int xVertex = width * 12 / 16 + 45;
        int yVertex = height * 10 / 64;
        sf::Font font;
        font.loadFromFile("Arial.ttf");

        distance.setFont(font);
        distance.setString("Distance");
        distance.setPosition(xDistance,yDistance);

        vertex.setFont(font);
        vertex.setString("Vertex");
        vertex.setPosition(xVertex,yVertex);




        //pozioma kreska
        b[0].setSize(sf::Vector2f(width/4,4));
        b[0].setFillColor(sf::Color::White);
        b[0].setPosition( width*0.75,height*1/4 );
        //pionowa kreska
        b[1].setSize(sf::Vector2f(4,height));
        b[1].setFillColor(sf::Color::White);
        b[1].setPosition( width*14/16,height*10/64 );

        window.draw(sprite);

        window.draw(vertex);
        window.draw(distance);
        //window.draw(b[0]);
        //window.draw(b[1]);
        //linia przerywana
        for(int i=2,j=0;i<64;i++,j+=2){

            b[i].setSize(sf::Vector2f(4,height/64));
            b[i].setFillColor(sf::Color::White);
            b[i].setPosition( dottedLinePosition,height/32*j );
            //window.draw(b[i]);

        }

        //window.display();
        //usleep(3000);

        for (int i = 0; i < Size; i++){


            t[i].setFont(font);
            char c = '0'+i;
            t[i].setString(c);
            t[i].setPosition(width*13/16,height*(16+4*i)/64);

            t2[i].setFont(font);
            std::string s = std::to_string(dist[i]);
            t2[i].setString(s);
            t2[i].setPosition(width*14/16+4,height*(16+4*i)/64);
            window.draw(t[i]);
            window.draw(t2[i]);

        }
        //usleep(30000);
        //window.display();
        //sleep(1);



    }
private:

};





