#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unistd.h>
#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <vector>
#include "MyVertex.h"
#include "MyEdge.h"
#include <random>

using namespace std;

#define V 9

const int height=600;
const int width=1200;

sf::RenderWindow window(sf::VideoMode(width,height ),
"Algorytm Dijkstry",sf::Style::Default);



int minDistance(int dist[], bool sptSet[]);
int printSolution(int dist[]);
void dijkstra(int** graph, int src);
int getGraphSize();
void drawBoard( int countOfVertex,vector <MyVertex>& vertex,vector <MyEdge*> edge,int** graph  );
void printGraph();
void printVertex();
void printEdge();

int main()
{

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


        }break;

        default:
            break;
        }

        //sleep(30);


        window.clear();
        vector <MyVertex> vertex;
        vector <MyEdge*> edge;

        int w=V;
        int k=V;

        int** tab = new int *[w];
        for(int i=0;i<w;i++){
            tab[i] = new int[k];
                for(int j=0;j<k;++j)
                {
                    tab[i][j] = 0;
                }
        }

        drawBoard(V,vertex,edge,tab);
        for(int i=0;i<w;i++){
                for(int j=0;j<k;++j)
                {
                    cout << tab[i][j] <<" ";
                }
                cout<<endl;
        }
        dijkstra(tab, 0);


        window.display();
        usleep(10000);

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
    sf::RectangleShape cleaner;
    sf::RectangleShape b[256];
    sf::Text t[V];
    sf::Text t2[V];
    sf::Text vertex,distance;

    sf::Font font;
    font.loadFromFile("Arial.ttf");

    distance.setFont(font);
    distance.setString("Distance");
    distance.setPosition(width*14/16+4,height*(10)/64);

    vertex.setFont(font);
    vertex.setString("Vertex");
    vertex.setPosition(width*12/16,height*(10)/64);


    cleaner.setSize(sf::Vector2f(width/4,height));
    cleaner.setFillColor(sf::Color::Black);
    cleaner.setPosition( width*14/16+1,height*(16)/64+1 );

    b[0].setSize(sf::Vector2f(width/4,4));
    b[0].setFillColor(sf::Color::White);
    b[0].setPosition( width*0.75,height*1/4 );
    b[1].setSize(sf::Vector2f(4,height));
    b[1].setFillColor(sf::Color::White);
    b[1].setPosition( width*14/16,height*10/64 );
    usleep(30000);
    window.draw(cleaner);
    usleep(30000);
    window.display();
    window.draw(vertex);
    window.draw(distance);
    window.draw(b[0]);
    window.draw(b[1]);
    for(int i=2,j=0;i<64;i++,j+=2){

        b[i].setSize(sf::Vector2f(4,height/64));
        b[i].setFillColor(sf::Color::White);
        b[i].setPosition( width*11/16,height/32*j );
        window.draw(b[i]);

    }

    window.display();
    usleep(30000);
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++){
        printf("%d \t\t %d\n", i, dist[i]);

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
    usleep(30000);
    window.display();
    sleep(1);

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
            usleep(30000);
        }
    }

}

void drawBoard( int countOfVertex,vector <MyVertex>& vertex,vector <MyEdge*> edge ,int** graph){
    sf::Vector2f mousePos;
    float margin = 40;
/*****************************Arrage vertex on board*********************************************/



    for(int i=0;i<countOfVertex;){
        usleep(3000);
        auto checker=[vertex,margin](sf::Vector2f m){
            std::cout << vertex.size()<<endl;
            for(MyVertex v : vertex){

                if(v.distance(m)<=margin*2){
                    return false;
                }
            }
            return true;
        };

        mousePos.x = (float) sf::Mouse::getPosition(window).x;
        mousePos.y = (float) sf::Mouse::getPosition(window).y;
        if(( sf::Mouse::isButtonPressed(sf::Mouse::Left)
             and mousePos.x < width*11/16-margin
             and mousePos.x>margin
             and mousePos.y>margin
             and mousePos.y<height-margin
             and checker(mousePos))){

            vertex.push_back( *(new MyVertex(i,mousePos)));
            vertex[i].drawMyVertex();

            window.display();
            i++;
            usleep(1000000);

        }

    }


/*****************************CONNECT VERTEX IN GRAPH***************************************/
    vector <MyVertex> SelectedVertex;
    while( !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) ){

    /* ******************Selecting vertex to connect latter********************* */
    if( sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            cout<<"------------------------------"<<endl;
            mousePos.x = (float) sf::Mouse::getPosition(window).x;
            mousePos.y = (float) sf::Mouse::getPosition(window).y;



            usleep(100000);

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
        usleep(100000);
        if( SelectedVertex.size()==2 ){
            MyEdge edge( SelectedVertex[0],SelectedVertex[1],5 );

            edge.DrawEdge();
            graph[SelectedVertex[0].getNumberInt()][SelectedVertex[1].getNumberInt()] = 5;
            graph[SelectedVertex[1].getNumberInt()][SelectedVertex[0].getNumberInt()] = 5;

            SelectedVertex[0].unSelect();
            SelectedVertex[1].unSelect();

            window.display();

            SelectedVertex.pop_back();
            SelectedVertex.pop_back();
        }


    } // end of while (ENTER)



}



void printGraph(){}
void printVertex(){}
void printEdge(){}


