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
#include "InfoText.h"
#include <random>

using namespace std;

#define V 9

const int height=600;
const int width=1200;

sf::RenderWindow window(sf::VideoMode(width,height ),
"Algorytm Dijkstry",sf::Style::Default);

int minDistance(int dist[], bool sptSet[]);
int printSolution(int dist[]);
void dijkstra(vector<MyEdge*>& vectorEdge,int** graph, int src);
int getGraphSize();
void drawBoard( int countOfVertex,vector <MyVertex>& vertex,vector<MyEdge*>& vectorEdge,int** graph  );
void drawVertex(vector <MyVertex>& vertex);
void drawEdge(vector<MyEdge*>& vectorEdge);
void connectVertex(vector <MyVertex*>& SelectedVertex,vector <MyVertex>& vertex,vector<MyEdge*>& vectorEdge ,int** graph);
void displayVectors(vector <MyVertex*>& SelectedVertex,vector <MyVertex>& vertex,vector<MyEdge*>& vectorEdge);
void edit(InfoText info,vector <MyVertex*>& SelectedVertex,vector <MyVertex>& vertex,vector<MyEdge*>& edge ,int** tab);
vector <MyVertex> vertex;
vector <MyEdge*> edge;
sf::Sprite sprite;
sf::Sprite dataSection;

int chooseVertex(vector <MyVertex>& vertex){
    sf::Vector2f mousePos;
while(true){
    usleep(3000);
    if( sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            cout<<"------------------------------"<<endl;
            mousePos.x = (float) sf::Mouse::getPosition(window).x;
            mousePos.y = (float) sf::Mouse::getPosition(window).y;
                for(int i = 0;i<vertex.size();i++)
                    if( vertex[i].distance(mousePos) <= vertex[i].getRadius() ){
                            return vertex[i].getNumberInt();
                            vertex[i].Select();
                    }
        }
    }
}

int main()
{
    //first sprite
    sf::Texture background_texture;
    background_texture.loadFromFile("neural-networks_featured-image.jpg");

    sf::Sprite background_sprite(background_texture);

    sf::RenderTexture render_texture;
    render_texture.create(width*12/16, height);
    //...
    background_sprite.move(1, 0);
    render_texture.clear();
    render_texture.draw(background_sprite);
    render_texture.display();
    const sf::Texture& texture = render_texture.getTexture();
    sprite.setTexture(texture);

    //second sprite
    sf::Texture background_texture2;
    background_texture2.loadFromFile("zwoj.png");

    sf::Sprite background_sprite2(background_texture2);

    sf::RenderTexture render_texture2;
    render_texture2.create(width*4/16, height);
    //...
    background_sprite2.move(1, 0);
    render_texture2.clear();
    render_texture2.draw(background_sprite2);
    render_texture2.display();
    const sf::Texture& texture2 = render_texture2.getTexture();
    dataSection.setTexture(texture2);
    dataSection.setPosition(width*12/16,0);




    InfoText info;
    int w=V;
    int k=V;
    int startVertex=0;
    int** tab = new int *[w];
    for(int i=0;i<w;i++){
        tab[i] = new int[k];
            for(int j=0;j<k;++j)
            {
                tab[i][j] = 0;
            }
    }

    vector <MyVertex*> SelectedVertex; // zbiór wskaźników na wektory zaznaczone

    window.clear();
    window.draw(sprite);
    window.draw(dataSection);
    info.displayInfoText("Arrange vertices on the surface");
    window.display();


    drawBoard(V,vertex,edge,tab);
    usleep(3000);
    window.clear();
    window.draw(sprite);
    window.draw(dataSection);
    drawVertex(vertex);
    window.display();

usleep(3000);

    edit(info,SelectedVertex,vertex,edge,tab);

    while (window.isOpen())
    {
        //sf::Event event;
        window.draw(sprite);
        window.draw(dataSection);
        drawVertex(vertex);
        drawEdge(edge);
        info.displayInfoText("Choose start Vertex");
        window.display();
        usleep(10000);

        startVertex=chooseVertex(vertex);

        for(int i=0;i<w;i++){for(int j=0;j<k;++j){cout << tab[i][j] <<" ";}cout<<endl;}
        window.draw(sprite);
        window.draw(dataSection);
        dijkstra(edge,tab, startVertex);

        info.displayInfoText("Press Enter to repeat simulation or Q to exit or E to edit");
        window.display();
        while( true ){

            if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) ){
                break;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)){
                return 0;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)){
                window.clear();
                window.draw(sprite);
                window.draw(dataSection);
                edit(info,SelectedVertex,vertex,edge,tab);
                window.draw(sprite);
                window.draw(dataSection);
                drawEdge(edge);
                info.displayInfoText("Press Enter to repeat simulation or Q to exit or E to edit");
                window.display();
            }

            usleep(1000);
        }
        window.clear();
        window.draw(sprite);
        window.draw(dataSection);
    }

    return 0;
}

int getGraphSize(){
        sf::RectangleShape button(sf::Vector2f(100.f,200.f));
        button.setFillColor(sf::Color::Yellow);
        button.setPosition( (height/10)*1,(width/10)*2);

        cout << button.getPosition().x<<":"<<button.getPosition().y<<endl;
        window.clear();
        window.draw(sprite);
        window.draw(button);
        window.display();
        sleep(1);
        return 9;
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
    DistanceTable table;
    table.MakeTable(V,dist);
}

void dijkstra(vector<MyEdge*>& vectorEdge,int** graph, int src)
{
    int dist[V];
    bool sptSet[V]; //tablica zapisująca informacje o przeanalizowanych wierzchołkach

    auto edgeExist=[vectorEdge](int u,int v){

            for( MyEdge* e : vectorEdge ){

                if  (( e->getBeginVertex().getNumberInt()==u and e->getEndVertex().getNumberInt()==v)
                  or ( e->getBeginVertex().getNumberInt()==v and e->getEndVertex().getNumberInt()==u))
                {
                    e->ActiveEdge();


                    return 1;
                }
            }
            return 0;
    };
    auto markVertex=[vectorEdge](int u){

            for( MyEdge* e : vectorEdge ){

                if  ( e->getBeginVertex().getNumberInt()==u )

                {
                    e->getBeginVertex().Select();

                    return 1;
                }
            }
            return 0;
    };


    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;
    window.draw(sprite);
    window.draw(dataSection);
    for( MyEdge* e : vectorEdge ){
        e->UnActiveEdge();
    }
    drawVertex(vertex);
    window.display();
    window.draw(sprite);
    window.draw(dataSection);
    drawEdge(edge);

    for (int count = 0; count < V - 1; count++) {

        int u = minDistance(dist, sptSet);

        sptSet[u] = true;
        cout << "analizowany wierzchołek: "<<u<<endl;

        for (int v = 0; v < V; v++){


            //aktualizacja kosztów
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v]){

                dist[v] = dist[u] + graph[u][v];

                drawVertex(vertex);
                drawEdge(edge);
                markVertex(u);
                if ( edgeExist(u,v)  ){
                    cout<<"aktywacja wezła!"<<endl;
                }

                usleep(3000);
                window.display();
                sleep(1);


                //dezaktywacja wszystkiego
                for( MyEdge* e : vectorEdge ){
                    e->UnActiveEdge();
                }
                //aktywacja bierzącego
                markVertex(u);
                printSolution(dist);
                usleep(300);
                window.display();
                sleep(1);
            }



        }


    }

}

void drawBoard( int countOfVertex,vector <MyVertex>& vertex,vector<MyEdge*>& vectorEdge ,int** graph){
    sf::Vector2f mousePos;
    float margin = 40;

/*****************************Arrage vertex on board*********************************************/

    for(int i=0;i<countOfVertex;){
        usleep(3000);
        auto checker=[vertex,margin](sf::Vector2f m){
            std::cout << vertex.size()<<endl;
            for(MyVertex v : vertex){

                if(v.distance(m)<=margin*4){
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
            usleep(10000);
        }
    }
}
void connectVertex(vector <MyVertex*>& SelectedVertex, vector <MyVertex>& vertex,vector<MyEdge*>& vectorEdge ,int** graph){
/*****************************CONNECT VERTEX IN GRAPH***************************************/
    sf::Vector2f mousePos;

    /*****************************checking if is 2 selected vertex then connect***************************************/
    if( SelectedVertex.size()==2 ){
            cout<<" są 2! "<<endl;
            int cost = 0;
            int counter = 0;
            int delay = 300000;
            while( !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)  ){ //!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0)){
                    cost *= 10;
                    cost += 0;
                    counter++;
                    cout<<"+"<<endl;
                    usleep(delay);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)){
                    cost *= 10;
                    cost += 1;
                    counter++;
                    cout<<"+"<<endl;
                    usleep(delay);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)){
                    cost *= 10;
                    cost += 2;
                    counter++;
                    cout<<"+"<<endl;
                    usleep(delay);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)){
                    cost *= 10;
                    cost += 3;
                    counter++;
                    cout<<"+"<<endl;
                    usleep(delay);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)){
                    cost *= 10;
                    cost += 4;
                    counter++;
                    usleep(delay);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5)){
                    cost *= 10;
                    cost += 5;
                    counter++;
                    usleep(delay);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6)){
                    cost *= 10;
                    cost += 6;
                    counter++;
                    usleep(delay);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7)){
                    cost *= 10;
                    cost += 7;
                    counter++;
                    usleep(delay);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8)){
                    cost *= 10;
                    cost += 8;
                    counter++;
                    usleep(delay);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9)){
                    cost *= 10;
                    cost += 9;
                    counter++;
                    usleep(delay);
                }

            } /// end of enter while

            if(cost>999) cost = 999;
            MyEdge* edge = new MyEdge( *SelectedVertex[0],*SelectedVertex[1],cost );

            edge->DrawEdge();

            vectorEdge.push_back(edge);

            graph[SelectedVertex[0]->getNumberInt()][SelectedVertex[1]->getNumberInt()] = cost;
            graph[SelectedVertex[1]->getNumberInt()][SelectedVertex[0]->getNumberInt()] = cost;

            SelectedVertex[0]->unSelect();
            SelectedVertex[1]->unSelect();
            usleep(3000);
            //window.display();

            SelectedVertex.pop_back();
            SelectedVertex.pop_back();
        }



    /* ******************Selecting vertex to connect********************* */
    if( sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            cout<<"------------------------------"<<endl;
            mousePos.x = (float) sf::Mouse::getPosition(window).x;
            mousePos.y = (float) sf::Mouse::getPosition(window).y;

            usleep(100000);

            for(int i=0;i<vertex.size();i++)
             {

                if( vertex[i].distance(mousePos) <= vertex[i].getRadius() ){
                    cout <<"isSelected:"<<vertex[i].isSelected()<<endl;
                    if( !vertex[i].isSelected() ){
                        cout<<"wybieram!"<<endl;
                        vertex[i].Select();
                        SelectedVertex.push_back(&vertex[i]);
                        break;
                    }
                    else{
                        cout <<"Już wybrany!"<<endl;
                        vertex[i].unSelect();
                        SelectedVertex.pop_back();
                        break;
                    }
                    usleep(100000);
                    window.display();
                }
            }
            /*******************************Usuwanie krawędzi************************************/
            int index=0;
            for( MyEdge* e : vectorEdge ){
                cout << e->getCenterPosition().x << " " << e->getCenterPosition().y <<endl;
                cout << mousePos.x << " " << mousePos.y <<endl;

                if ( mousePos.x >= e->getCenterPosition().x - 5
                     and mousePos.x <= e->getCenterPosition().x + 50
                     and mousePos.y >= e->getCenterPosition().y - 5
                     and mousePos.y <= e->getCenterPosition().y + 50
                     ) {
                    cout<<"usuwam połączenie"<<endl;

                    graph[e->getBeginVertex().getNumberInt()][e->getEndVertex().getNumberInt()] = 0;
                    graph[e->getEndVertex().getNumberInt()][e->getBeginVertex().getNumberInt()] = 0;

                    vectorEdge.erase(vectorEdge.begin() + index);


                    window.clear();
                    window.draw(sprite);
                    window.draw(dataSection);
                    for(int i=0;i<vertex.size();i++){
                        vertex[i].unSelect();
                    }
                    SelectedVertex.clear();
                    drawEdge(vectorEdge);
                    drawVertex(vertex);


                }
                index++;
            }

    } // end mouseclick detection

}

void drawVertex(vector <MyVertex>& vertex){
    for(MyVertex v : vertex) {
        v.drawMyVertex();
        usleep(3000);
    }
}

void drawEdge(vector<MyEdge*>& vectorEdge){
    for( MyEdge* e : vectorEdge ){
        e->DrawEdge();
        usleep(3000);
    }
}
void displayVectors(vector <MyVertex*>& SelectedVertex,vector <MyVertex>& vertex,vector<MyEdge*>& vectorEdge){
    cout<<"------"<<endl;
    for( MyEdge* e : vectorEdge ){

        cout << e->getCost()<<endl;

    }
    cout<<"------"<<endl;
    for( MyVertex e : vertex ){
        cout<<e.getNumberInt()<<"->"<<e.isSelected()<<endl;
    }
    cout<<"------"<<endl;
    for( MyVertex* e : SelectedVertex ){
        cout << e->getNumberInt()<<"->"<<e->isSelected() <<endl;
    }
    cout<<"------"<<endl;
}

void edit(InfoText info,vector <MyVertex*>& SelectedVertex,vector <MyVertex>& vertex,vector<MyEdge*>& edge ,int** tab){
    window.clear();
    window.draw(sprite);
    window.draw(dataSection);
    drawVertex(vertex);
    drawEdge(edge);
    info.displayInfoText("Press Tab to end connecting");
    window.display();
    while( !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab) ){


        info.displayInfoText("Press Tab to end connecting");
        usleep(1000);

        displayVectors(SelectedVertex,vertex,edge);

        connectVertex(SelectedVertex,vertex,edge,tab);
        usleep(1000);
        window.display();
        usleep(1000);

    }

    window.clear();
    window.draw(sprite);
}
