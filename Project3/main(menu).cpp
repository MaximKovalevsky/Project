#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <SFML/Audio.hpp>
using namespace sf;
void InitText(Text& mtext, float xpos, float ypos, String str, int size_font = 60, Color menu_text_color = Color::White, int bord = 0, Color border_color = Color::Black);

class setSound
{
public:
    SoundBuffer s, w, n, t;
    Sound score, win, fon, time;

    setSound()
    {

        n.loadFromFile("2.ogg");
        t.loadFromFile("3.ogg");

        fon.setBuffer(n);
        time.setBuffer(t);

        fon.setLoop(true);
        time.setLoop(true);

    }
};

setSound sound;

class Boolean
{
public:
    bool stop = true, play = false, pusk = false, pause = false;
    int puskgame = 1000;
};

Boolean boolean;
RenderWindow window(VideoMode(750, 512),"FF");

class Game
{
public:
    Sprite s[17];
    int w = 128;
    int grid[6][6] = { 0 };
    int n = 0;

    int b = 1, x = 0, y = 0;

    Game(Texture& image)
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                n++;
                s[n].setTexture(image);
                s[n].setTextureRect(IntRect(i * w, j * w, w, w));
                grid[i + 1][j + 1] = n;
            }
    }

    void update()
    {
        int dx = 0;
        int dy = 0;

        if (grid[x + 1][y] == b)
        {
            dx = 1;
            dy = 0;
        }
        if (grid[x - 1][y] == b)
        {
            dx = -1;
            dy = 0;
        }
        if (grid[x][y - 1] == b)
        {
            dx = 0;
            dy = -1;
        }
        if (grid[x][y + 1] == b)
        {
            dx = 0;
            dy = 1;
        }

        n = grid[x][y];
        grid[x][y] = b;
        grid[x + dx][y + dy] = n;

        s[b].move(-dx * w, -dy * w);
        float speed = 16;
        for (int i = 0; i < w; i += speed)
        {
            s[n].move(speed * dx, speed * dy);
            window.draw(s[b]);
            window.draw(s[n]);
            window.display();
        }

        if (boolean.play)
        {
            if (grid[1][1] == 1 && grid[1][2] == 2 && grid[1][3] == 3 && grid[1][4] == 4 &&
                grid[2][1] == 5 && grid[2][2] == 6 && grid[2][3] == 7 && grid[2][4] == 8 &&
                grid[3][1] == 9 && grid[3][2] == 10 && grid[3][3] == 11 && grid[3][4] == 12 &&
                grid[4][1] == 13 && grid[4][2] == 14 && grid[4][3] == 15 && grid[4][4] == 16)
            {
                boolean.play = false;
                boolean.stop = true;

                boolean.puskgame = 1000;

                window.setFramerateLimit(0);

                sound.fon.play();
                sound.time.stop();
            }
        }
    }
};

class Button
{
public:
    Texture t, s;
    Sprite start, prod, naczap;

    Button()
    {
        t.loadFromFile("5.png");
        s.loadFromFile("6.png");

        start.setTexture(t);
        start.setPosition(540, 400);
        start.setTextureRect(IntRect(0, 0, 196, 65));

        prod.setTexture(s);
        prod.setPosition(540, 150);
        prod.setTextureRect(IntRect(0, 0, 196, 65));

        naczap.setTexture(s);
        naczap.setPosition(540, 300);
        naczap.setTextureRect(IntRect(0, 65, 196, 65));
    }
};

class Stopwatch
{
public:
    Sprite min[2], sec[2], toc;
    int m[2], s[2], ms;

    Stopwatch(Texture& image)
    {
        for (int i = 0; i < 2; i++)
        {
            min[i].setTexture(image);
            sec[i].setTexture(image);

            min[i].setPosition(570 + 30 * i, 25);
            sec[i].setPosition(654 + 30 * i, 25);

            min[i].setTextureRect(IntRect(0, 0, 24, 38));
            sec[i].setTextureRect(IntRect(0, 0, 24, 38));

            m[i] = 0;
            s[i] = 0;
        }

        toc.setTexture(image);
        toc.setPosition(627, 25);
        toc.setTextureRect(IntRect(240, 0, 24, 38));

        ms = 0;
    }

    void update()
    {
        if (boolean.play)
            ms++;

        if (ms >= 7)
        {
            s[1]++;
            ms = 0;
        }

        if (s[1] == 10)
        {
            s[0]++;
            s[1] = 0;
        }

        if (s[0] == 6)
        {
            m[1]++;
            s[0] = 0;
        }

        if (m[1] == 10)
        {
            m[0]++;
            m[1] = 0;
        }

        for (int i = 0; i < 2; i++)
        {
            sec[i].setTextureRect(IntRect(24 * s[i], 0, 24, 38));
            min[i].setTextureRect(IntRect(24 * m[i], 0, 24, 38));
        }
    }
};

void GameStart()
{
    srand(time(0));

    Texture t;
    t.loadFromFile("1.png");
    Game game(t);

    Sprite picture(t);
    picture.setScale(0.4, 0.4);
    picture.setPosition(530, 130);

    Button button;

    Texture ti;
    ti.loadFromFile("4.png");
    Stopwatch watch(ti);

    sound.fon.play();
    RenderWindow window(VideoMode::getDesktopMode(), L"Drive", Style::None);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                {
                    window.close();
                    sound.fon.stop();
                    sound.time.stop();
                }
            }
            /*if (event.type == Event::Closed)
                window.close();*/

            if (event.type == Event::MouseButtonPressed)
                if (event.key.code == Mouse::Left) {
                    Vector2i pos = Mouse::getPosition(window);

                    if (boolean.play)
                    {
                        if (pos.x <= 512)
                        {
                            game.x = pos.x / game.w + 1;
                            game.y = pos.y / game.w + 1;



                        }
                        else if (pos.x >= 540 && pos.x <= 736 && pos.y >= 400 && pos.y <= 465)
                        {
                            boolean.pause = true;
                            boolean.play = false;
                        }
                    }
                    else if (boolean.stop)
                    {
                        if (pos.x >= 540 && pos.x <= 736 && pos.y >= 400 && pos.y <= 465)
                        {
                            boolean.stop = false;
                            boolean.pusk = true;

                            window.setFramerateLimit(0);

                            for (int i = 0; i < 2; i++)
                            {
                                watch.m[i] = 0;
                                watch.s[i] = 0;
                            }
                            watch.ms = 0;


                            sound.fon.stop();
                            sound.time.play();

                            button.start.setTextureRect(IntRect(0, 65, 196, 65));
                        }
                    }
                    else if (boolean.pause)
                    {

                        if (pos.x >= 540 && pos.x <= 736 && pos.y >= 150 && pos.y <= 280)
                        {
                            boolean.pause = false;
                            boolean.play = true;
                        }
                        if (pos.x >= 540 && pos.x <= 736 && pos.y >= 300 && pos.y <= 430)
                        {
                            game.grid[1][1] = 1; game.grid[1][2] = 2; game.grid[1][3] = 3; game.grid[1][4] = 4;
                            game.grid[2][1] = 5; game.grid[2][2] = 6; game.grid[2][3] = 7; game.grid[2][4] = 8;
                            game.grid[3][1] = 9; game.grid[3][2] = 10; game.grid[3][3] = 11; game.grid[3][4] = 12;
                            game.grid[4][1] = 13; game.grid[4][2] = 14; game.grid[4][3] = 15; game.grid[4][4] = 16;

                            boolean.pause = false;
                            boolean.pusk = true;

                            boolean.puskgame = 1000;

                            for (int i = 0; i < 2; i++)
                            {
                                watch.m[i] = 0;
                                watch.s[i] = 0;
                            }
                            watch.ms = 0;

                            window.setFramerateLimit(0);
                        }
                    }
                }

        }

        if (boolean.pusk)
        {
            game.x = rand() % 4 + 1;
            game.y = rand() % 4 + 1;

            boolean.puskgame--;

            if (boolean.puskgame == 0)
            {
                boolean.pusk = false;
                boolean.play = true;


            }
        }
        else if (boolean.play)
        {
            window.setFramerateLimit(7.5);
        }
        else if (boolean.stop)
            button.start.setTextureRect(IntRect(0, 0, 196, 65));

        game.update();
        watch.update();
        window.clear(Color::Black);
        window.draw(picture);
        if (boolean.stop || boolean.play)
            window.draw(button.start);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                game.n = game.grid[i + 1][j + 1];
                game.s[game.n].setPosition(i * game.w, j * game.w);
                window.draw(game.s[game.n]);
            }
        }

        for (int i = 0; i < 2; i++)
        {
            window.draw(watch.min[i]);
            window.draw(watch.sec[i]);
        }
        window.draw(watch.toc);
        if (boolean.pause)
        {
            window.draw(button.prod);
            window.draw(button.naczap);
        }
        window.display();
    }

}



int main()
{
	RenderWindow window;
	window.create(VideoMode::getDesktopMode(), L"Drive", Style::Fullscreen);

	//window.setMouseCursorVisible(false);

	float width = VideoMode::getDesktopMode().width;
	float height = VideoMode::getDesktopMode().width;

	RectangleShape background(Vector2f(width, height));
	Texture texture_window;
	if (!texture_window.loadFromFile("7.jpeg")) return 4;
	background.setTexture(&texture_window);

	Font font;
	if (!font.loadFromFile("Mistral.ttf")) return 5;

	Text Titul;
	Titul.setFont(font);
	//InitText(Titul, 480, 50, L"Drive", 150, Color::Cyan, 3);

	String name_menu[5]{ L"Game", L"Options", L"Exit" };

	game::GameMenu mymenu(window, 950, 350, name_menu, 100, 120);

	mymenu.setColorTextMenu(Color(250, 0, 150), Color::White);
	mymenu.AlignMenu(2);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Up) 
                { 
                    mymenu.MoveUp(); 
                }
                if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }
                if (event.key.code == Keyboard::Return)
                {
                    switch (mymenu.getSelectedMenuNumber())
                    {
                        case 0:GameStart(); break;
                        case 2:window.close(); break;
                        
                    }
                }
            }

		}

		window.clear();
		window.draw(background);
		window.draw(Titul);
		mymenu.draw();
		window.display();
	}
	return 0;

}

void InitText(Text& mtext, float xpos, float ypos, String str, int size_font, Color menu_text_color, int bord, Color border_color)
{
	mtext.setCharacterSize(size_font);
	mtext.setPosition(xpos, ypos);
	mtext.setString(str);
	mtext.setFillColor(menu_text_color);
	mtext.setOutlineThickness(bord);
	mtext.setOutlineColor(border_color);

}
