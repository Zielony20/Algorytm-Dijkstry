#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>
#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <vector>
#include "MyVertex.h"
#include "MyEdge.h"
using namespace std;
#define V 9
const int height=400;
const int width=1000;

sf::RenderWindow window(sf::VideoMode(width,height ),
"Algorytm Dijkstry",sf::Style::Resize|sf::Style::Default);



int minDistance(int dist[], bool sptSet[]);
int printSolution(int dist[]);
void dijkstra(int** graph, int src);
int getGraphSize();
void drawBoard( int countOfVertex );
void printGraph();
void printVertex();
void printEdge();

int main()
{

    int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };





    while (window.isOpen())
    {
        sf::Event event;
        //window.pollEvent(event)

        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::TextEntered:
        {
            if(event.text.unicode<128){
                text.setString("zmieniono");
                window.clear();
                window.draw(text);
            }

        }break;

        default:
            break;
        }

        //sleep(30);


        window.clear();
        dijkstra(graph, 0);
        drawBoard(5);

        window.display();
        sleep(3);

    }

    return 0;
}

int getGraphSize(){

    //while(){
        sf::RectangleShape button(sf::Vector2f(100.f,200.f));
        button.setFillColor(sf::Color::Yellow);
        button.setPosition( (height/10)*1,(width/10)*2);

        cout << button.getPosition().x<<":"<<button.getPosition().y<<endl;
        window.clear();
        window.draw(button);
        window.display();
        sleep(1);
        return 9;
    //}
}

int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

int printSolution(int dist[]){
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);




}

void dijkstra(int** graph, int src)
{
    int dist[V];


    bool sptSet[V];


    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {

        int u = minDistance(dist, sptSet);

        sptSet[u] = true;

        for (int v = 0; v < V; v++){

            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v]){

                dist[v] = dist[u] + graph[u][v];
            }
            printSolution(dist);
        }
    }

}

void drawBoard( int countOfVertex ){
    sf::Vector2f mousePos;
    vector <MyVertex> vertex;

    for(int i=0;i<countOfVertex;){

        if( sf::Mouse::isButtonPressed(sf::Mouse::Left) ){
            mousePos.x = (float) sf::Mouse::getPosition(window).x;
            mousePos.y = (float) sf::Mouse::getPosition(window).y;
            //cout << sf::Mouse::getPosition(window).y<<":"<<sf::Mouse::getPosition(window).x<<endl;

            cout<<i<<endl;

            vertex.push_back( *(new MyVertex(i,mousePos)));
            vertex[i].printMyVertex();

            window.display();
            i++;
            usleep(1000000);
        }

    }

    vector <MyEdge*> edge;

    int counter=0; // selecting vertex

    vector <MyVertex> SelectedVertex;
    while( !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) ){
    usleep(100000);

    if( SelectedVertex.size()==2 ){
       MyEdge test( SelectedVertex[0],SelectedVertex[1],5 );
        test.DrawEdge();
        window.display();
        SelectedVertex[0].unSelect();
        SelectedVertex[1].unSelect();

        window.display();
        SelectedVertex.pop_back();
        SelectedVertex.pop_back();
    }

        if( sf::Mouse::isButtonPressed(sf::Mouse::Left) ){
            cout<<"------------------------------"<<endl;
            mousePos.x = (float) sf::Mouse::getPosition(window).x;
            mousePos.y = (float) sf::Mouse::getPosition(window).y;
            usleep(100000);

            int ite=0;
            for(MyVertex v : vertex) {

                if( v.distance(mousePos) <= v.getRadius() ){

                    if( !v.isSelected() ){
                        v.Select();

                        SelectedVertex.push_back(v);
                    }
                    else{

                        v.unSelect();
                        SelectedVertex.pop_back();
                    }
                    usleep(100000);
                    window.display();
                }
            }
        }
    }



}
void printGraph(){}
void printVertex(){}
void printEdge(){}


