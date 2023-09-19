#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <cmath>
#include <random>

int lvlCounter = 0;
const int szerokosc = 800;
const int wysokosc = 600;
sf::RenderWindow window(sf::VideoMode(szerokosc, wysokosc), "Cziken Shooter");
sf::RectangleShape player;
const int N = 1;
int score;
sf::RectangleShape przeszkody[N];
float px = (szerokosc/2)-40;
float py = wysokosc-30;
float bVelx = 0;
float bVely = 0;
sf::CircleShape ball(20.f);
int nk[N];
int nkPosx[N], nkPosy[N];



bool lf_bCheckForMouseTrigger(sf::Sprite &av_Sprite, sf::RenderWindow &av_Window)
{

    int mouseX = sf::Mouse::getPosition().x;
    int mouseY = sf::Mouse::getPosition().y;

    sf::Vector2i windowPosition = av_Window.getPosition();

    if(mouseX > av_Sprite.getPosition().x + windowPosition.x && mouseX < ( av_Sprite.getPosition().x + av_Sprite.getGlobalBounds().width + windowPosition.x)
        && mouseY > av_Sprite.getPosition().y + windowPosition.y + 30  && mouseY < ( av_Sprite.getPosition().y + av_Sprite.getGlobalBounds().height + windowPosition.y + 30) )
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            lvlCounter = 1;
        }
    }
}


void przeszkodyInit(){
    for(int i=0; i<N; i++){
        nkPosx[i] = (rand()%szerokosc)/1.2 + 40;
        nkPosy[i] = rand()%(wysokosc/2);
        przeszkody[i].setSize(sf::Vector2f(40, 40));
        przeszkody[i].setPosition(nkPosx[i],nkPosy[i]);
    }
}


void przeszkodyKolizja(sf::CircleShape ball, sf::RectangleShape &przeszkoda){
    if((floor(przeszkoda.getPosition().x) <=  floor(ball.getPosition().x) && (floor(przeszkoda.getPosition().x)+40 >= floor(ball.getPosition().x)))){
        if((floor(przeszkoda.getPosition().y) <=  floor(ball.getPosition().y) && (floor(przeszkoda.getPosition().y)+40 >= floor(ball.getPosition().y)))){
            przeszkoda.setPosition(-100,-100);
            score += 1;
            przeszkodyInit();
        }
    }
}



void menu(){
    //Tlo
	sf::Texture tlo;
	tlo.loadFromFile("src/img/tlo.jpg");
	sf::Sprite tloSprite;
	tloSprite.setTexture(tlo);
	tloSprite.setPosition(sf::Vector2f(-120,-20));
	tloSprite.scale(sf::Vector2f(1,1));
	window.draw(tloSprite);

    //Graj teraz
	sf::Texture grajTexture;
	grajTexture.loadFromFile("src/img/graj.png");
	sf::Sprite grajButton;
	grajButton.setTexture(grajTexture);
	grajButton.setPosition(sf::Vector2f(310,480));
	grajButton.scale(sf::Vector2f(0.2,0.2));
	window.draw(grajButton);

	lf_bCheckForMouseTrigger(grajButton, window);
}

void ballHandler(){

    bVely += 0.00001;

}

void playerHandler(){


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && px>0)
    {
        px -= 0.3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)&& px<800-120)
    {
        px += 0.3;
    }
}

void gra(){
    playerHandler();
    ballHandler();
}

int main(){

    score = 0;

    przeszkodyInit();

    time_t current_time = time(NULL);
    srand((unsigned) time(NULL));

    sf::RectangleShape player;
    player.setSize(sf::Vector2f(120, 20));

    sf::CircleShape ball(20.f);
    ball.setPosition(szerokosc/2, wysokosc/2);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
    }

   window.clear(sf::Color::Black);


    if(lvlCounter == 0)
		menu();
	if(lvlCounter == 1)
    {
        gra();
        player.setPosition(px, py);

        for(int i=0; i<N; i++)
            window.draw(przeszkody[i]);

        for(int i=0; i<N; i++)
            przeszkodyKolizja(ball,przeszkody[i]);


        ball.move(bVelx, bVely);


if((floor(ball.getPosition().x)-120 <=  floor(player.getPosition().x) && (floor(ball.getPosition().x)+80 >= floor(player.getPosition().x)))){
    if((floor(ball.getPosition().y) ==  floor(player.getPosition().y-20))){
        bVely *= -1.05;
        bool neg = rand()%2;
        int negVal = -1;
        if(neg){
            int negVal = 1;
        }
        bVelx += rand() / static_cast<float>(RAND_MAX)/10.f * negVal;
    }
}

if((floor(ball.getPosition().y)) <= 0){
    bVely *= -1;
}

if((floor(ball.getPosition().x)) <= 0){
    bVelx *= -1;
}
if((floor(ball.getPosition().x))+40 >= szerokosc){
    bVelx *= -1;
}

        window.draw(ball);
        window.draw(player);
}

    window.display();
    }
    return 0;
}
