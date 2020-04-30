#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
//#include "MyVertex.h"

extern sf::RenderWindow window;

class MyEdge{
public:
    MyEdge( MyVertex& begin, MyVertex& end, int cost=1 ):
    beginVertex_(begin),endVertex_(end),cost_(cost)
    {

    }
    void ActiveEdge(){
        sf::Vertex line[2];
        line[0].position = sf::Vector2f(beginVertex_.getPosition());
        line[0].color  = sf::Color::Green;
        line[1].position = sf::Vector2f(endVertex_.getPosition());
        line[1].color = sf::Color::Green;

        window.draw(line, 2, sf::Lines);
        beginVertex_.Select();
        usleep(100000);
        endVertex_.Select();
        //beginVertex_.drawMyVertex();
        //endVertex_.drawMyVertex();
        usleep(100000);
        window.display();
        usleep(300000);

        line[0].color  = sf::Color::White;
        line[1].color  = sf::Color::White;
        window.draw(line, 2, sf::Lines);
        beginVertex_.unSelect();
        endVertex_.unSelect();
        sleep(1);
        window.display();
        sleep(1);

    }
    void DrawEdge(sf::Color color=sf::Color::White){
        sf::Vertex line[2];
        line[0].position = sf::Vector2f(beginVertex_.getPosition());
        line[0].color  = color;
        line[1].position = sf::Vector2f(endVertex_.getPosition());
        line[1].color = color;

        window.draw(line, 2, sf::Lines);
        beginVertex_.drawMyVertex();
        endVertex_.drawMyVertex();
        window.display();
        usleep(30000);
    }
    int getCost(){
        return cost_;
    }
    void setCost(int cost)
    {
        cost_=cost;
    }
    MyVertex getBeginVertex(){
        return beginVertex_;
    }
    MyVertex getEndVertex(){
        return endVertex_;
    }
private:
    int cost_;
    MyVertex beginVertex_;
    MyVertex endVertex_;

};






