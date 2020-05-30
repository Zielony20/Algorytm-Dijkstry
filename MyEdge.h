#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <string>
//#include "MyVertex.h"

extern sf::RenderWindow window;
class CostField{

public:
    CostField(int num ,sf::Vector2f position,
              sf::Color color=sf::Color::Red,sf::Vector2f s=sf::Vector2f(40,25)):number_(num),size_(s)
    {

        rect_.setFillColor(color);
        rect_.setSize(size_);

        rect_.setPosition(position.x-size_.x/2,position.y-size_.y/2);
        //rect_.setOrigin( size.x/2,size.y/2 );

        if(!font_.loadFromFile("Arial.ttf")){
            cout<<"błąd ładowania czcionki!"<<endl;
         }
         cost_.setFont(font_);

         cost_.setString(to_string(num));
         cost_.setCharacterSize(20);
         cost_.setFillColor(sf::Color::White);
         cost_.setStyle(sf::Text::Bold);
         cost_.setPosition( rect_.getPosition().x,rect_.getPosition().y );

    }
    void drawMyCostField(sf::Color color=sf::Color::Red){
        rect_.setFillColor(color);
        window.draw(rect_);
        window.draw(cost_);
    }
    sf::RectangleShape getShape(){
        return rect_;
    }
    sf::Vector2f getSize(){
        return size_;
    }
    sf::Vector2f getPosition(){
        return rect_.getPosition();
    }
private:
    int number_;
    sf::Vector2f size_;
    sf::RectangleShape rect_;
    sf::Text cost_;
    sf::Font font_;
};


class MyEdge{
public:
    MyEdge( MyVertex& begin, MyVertex& end, int cost=1 ):
    beginVertex_(begin),endVertex_(end),cost_(cost)
    {
        center_.x = (beginVertex_.getPosition().x + endVertex_.getPosition().x)/2;
        center_.y = (beginVertex_.getPosition().y + endVertex_.getPosition().y)/2;
        costfield_ = new CostField(cost,center_);
    }
    void ActiveEdge(){
        sf::Vertex line[2];
        sf::Color activeColor = sf::Color::Green;
        line[0].position = sf::Vector2f(beginVertex_.getPosition());
        line[0].color  = activeColor;
        line[1].position = sf::Vector2f(endVertex_.getPosition());
        line[1].color = activeColor;

        window.draw(line, 2, sf::Lines);
        beginVertex_.Select();
        usleep(100000);
        endVertex_.Select();
        //beginVertex_.drawMyVertex();
        //endVertex_.drawMyVertex();
        //CostField cost(cost_,center_,activeColor);
        costfield_->drawMyCostField(activeColor);
        usleep(300000);

    }
    void UnActiveEdge(){
        sf::Vertex line[2];
        sf::Color UnActiveColor = sf::Color::White;
        sf::Color UnActiveColor2 = sf::Color::Red;
        line[0].position = sf::Vector2f(beginVertex_.getPosition());
        line[1].position = sf::Vector2f(endVertex_.getPosition());

        line[0].color  = UnActiveColor;
        line[1].color  = UnActiveColor;
        window.draw(line, 2, sf::Lines);
        beginVertex_.unSelect();
        usleep(100000);
        endVertex_.unSelect();
        //CostField cost(cost_,center_,UnActiveColor2);
        costfield_->drawMyCostField(UnActiveColor2);
        //sleep(1);
        //window.display();
        //sleep(1);
    }
    void DrawEdge(sf::Color color=sf::Color::White){
        sf::Vertex line[2];
        line[0].position = sf::Vector2f(beginVertex_.getPosition());
        line[0].color  = color;
        line[1].position = sf::Vector2f(endVertex_.getPosition());
        line[1].color = color;

        sf::Vector2f center;
        center.x = (beginVertex_.getPosition().x + endVertex_.getPosition().x)/2;
        center.y = (beginVertex_.getPosition().y + endVertex_.getPosition().y)/2;
        CostField cost(cost_,center,sf::Color::Red);

        window.draw(line, 2, sf::Lines);
        cost.drawMyCostField(sf::Color::Red);
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
    sf::Vector2f getCenterPosition(){
        return center_;
    }
    CostField* getCostField(){
        return costfield_;
    }
private:
    int cost_;
    MyVertex beginVertex_;
    MyVertex endVertex_;
    sf::Vector2f center_;
    CostField* costfield_;
};






