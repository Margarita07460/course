#include "Header.h"
const int field_height = 30;
const int field_width = 20;
int field[field_height][field_width]{ };
int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // S
	3,5,4,6, // Z
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};
int checkLine(int& userPoints)
{

	
	int k = field_height - 1;                
	for (int i = field_height - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < field_width; j++)
		{
			if (field[i][j])
			{
				count++;
			}
			field[k][j] = field[i][j];
		}

		if (count < field_width)
		{
			k--;
		}

		else
		{
			userPoints += 1;
		}
		printf(" % d", userPoints);
	}
	return userPoints;
}



class Tetramino
{
public:
	int color{ };
	int type{ };
	int blockPositions[4]{ };

	struct Coordinates
	{
		int x;
		int y;
	};

	Coordinates coordinates[4]{ };
	void create()
	{
		std::cout << "new tetramino created" << std::endl;
		color = 1 + rand() % 7;
		type = rand() % 7;
		for (int i = 0; i < 4; i++)
		{
			blockPositions[i] = figures[type][i];
		}
		for (int i = 0; i < 4; i++)
		{
			coordinates[i].x = blockPositions[i] % 2 + 7;
			coordinates[i].y = blockPositions[i] / 2;
		}
	};
	void draw(sf::RenderWindow& thatWindow,
		sf::Sprite& thatSprite,
		int marginLeft,
		int marginTop)
	{

		for (int i = 0; i < 4; i++)
		{
			
			thatSprite.setTextureRect(sf::IntRect(color * 18, 0, 18, 18));

			thatSprite.setPosition(coordinates[i].x * 18, coordinates[i].y * 18);
			thatSprite.move(marginLeft, marginTop); 

			
			thatWindow.draw(thatSprite);
		}
	};

	bool check()
	{
		for (int i = 0; i < 4; i++)
		{
			if (coordinates[i].x < 0 || coordinates[i].x >= field_width || coordinates[i].y >= field_height)
			{
				std::cout << std::endl << "field X" << coordinates[i].x << "Y " << coordinates[i].y << "is out of board" << std::endl;
				return false;
			}
			else if (field[coordinates[i].y][coordinates[i].x])
			{
				std::cout << std::endl << "field X" << coordinates[i].x << "Y " << coordinates[i].y << "is occupied" << std::endl;
				return false;
			}

		}
		return true;
	}
	void moveDown(sf::RenderWindow& thatWindow)
	{
		sf::RenderWindow Window;
		int x[4]{};
		int y[4]{};

		for (int i = 0; i < 4; i++)
		{
			y[i] = coordinates[i].y;
			x[i] = coordinates[i].x;
		}

		for (int i = 0; i < 4; i++)
		{
			coordinates[i].y += 1;
		}

		if (check() == false)
		{
		
			std::cout << "stop here" << std::endl;
			for (int i = 0; i < 4; i++)
			{

				coordinates[i].y = y[i];
				std::cout << "coloring the field" << std::endl;
				field[y[i]][x[i]] = color;
			}
			create();
			if (check() == false)
			{
				std::cout << "GAME OVER " << std::endl;
				tabl(thatWindow);
			}
		}
		else
		{
			;
		}
	}
	inline void tabl(RenderWindow& window) {
		char lider[10];
		int i = -1;
		Font font;
		font.loadFromFile("ofont.ru_Roboto.ttf");
		Text text;
		text.setFont(font);
		Texture fon;
		fon.loadFromFile("tex.png");
		Sprite fn(fon);
		window.draw(fn);
		text.setString(L"¬ведите им€ - счет:");
		text.setPosition(20, 20);
		text.setCharacterSize(40);
		text.setFillColor(Color::Black);
		(window).draw(text);
		(window).display();
		text.setCharacterSize(90);
		text.setFillColor(Color::Black);
		FILE* file;
		fopen_s(&file, "tabl.txt", "a");
		String string;
		char mas[10];

		while ((window).isOpen())
		{
			Event event;
			while ((window).pollEvent(event))
			{


				if (event.type == sf::Event::Closed)
				{
					(window).close();
				}
				if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					for (int a = 0; a <= i; a++) {
						fprintf(file, "%c", lider[a]);
					}
					fprintf(file, "\n");
					fclose(file);
					Texture fon;
					fon.loadFromFile("tex.png");
					Sprite fn(fon);
					window.draw(fn);
					text.setString(L"»гроки и счет : ");
					text.setPosition(20, 20);
					text.setCharacterSize(60);
					text.setFillColor(Color::Black);
					(window).draw(text);
					fopen_s(&file, "tabl.txt", "r+");
					int peremeshenie_po_y = 0;
					while (fgets(mas, 10, file)) {

						text.setString(mas);
						text.setPosition(20, 100 + peremeshenie_po_y);
						text.setCharacterSize(40);
						text.setFillColor(Color::White);
						(window).draw(text);
						peremeshenie_po_y += 50;
					}

					(window).display();
					
					Sleep(10000);

				}
				if ((event.type == Event::TextEntered || Keyboard::isKeyPressed(Keyboard::LShift))) {

					Texture fon;
					fon.loadFromFile("tex.png");
					Sprite fn(fon);
					window.draw(fn);
					text.setString(L"¬ведите им€ и счет:");
					text.setPosition(20, 20);
					text.setCharacterSize(40);
					text.setFillColor(Color::Black);
					(window).draw(text);
					text.setCharacterSize(80);
					text.setFillColor(Color::Black);
					if (event.type == Event::TextEntered) {
						i++;
						lider[i] = event.key.code;
						for (int g = 0; g <= i; g++) {
							text.setString(lider[g]);
							text.setPosition(20 + g * 50, 200);
							(window).draw(text);
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::LShift)) {

						lider[i] = NULL;
						i--;
						printf("-%d", i);
						for (int g = 0; g <= i; g++) {
							text.setString(lider[g]);
							text.setPosition(20 + g * 50, 200);
							(window).draw(text);
						}
					}
					(window).display();
					Sleep(200);


				}

			}

		}
	}
	
	void moveHoriz(sf::RenderWindow& thatWindow, int direction)
	{
		int x[4]{};
		int y[4]{};

		for (int i = 0; i < 4; i++)
		{
			y[i] = coordinates[i].y;
			x[i] = coordinates[i].x;
		}

		for (int i = 0; i < 4; i++)
		{
			coordinates[i].x += direction;
		}

		if (check() == false)
		{
			for (int i = 0; i < 4; i++)
			{
				coordinates[i].x = x[i];
			}

		}
		else
		{
			;
		}
	}
	void rotate()
	{
		int x[4]{};
		int y[4]{};
		for (int i = 0; i < 4; i++)
		{
			y[i] = coordinates[i].y;
			x[i] = coordinates[i].x;
		}

		int originX = coordinates[1].x;
		int originY = coordinates[1].y;
		for (int i = 0; i < 4; i++)
		{

			int dy = coordinates[i].y - originY; 
			int dx = coordinates[i].x - originX; 
			coordinates[i].x = originX - dy; 
			coordinates[i].y = originY + dx;
		}
		if (check() == false)
		{
			for (int i = 0; i < 4; i++)
			{
				coordinates[i].x = x[i];
			}

		}
		else
		{
			;
		}
	}

};




int main()
{
	srand(time(0));
	int window_width{ 500 };
	int window_height{ 700 };
	int userPoints{ 0 };
	Tetramino tetramino;
	tetramino.create();
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), " Tetris!");
	menu(window);
	sf::Texture texture, texture_background, texture_frame;
	texture.loadFromFile("bl.png");
	texture_background.loadFromFile("tex.png");
	sf::Sprite sprite(texture), sprite_background(texture_background);

	sprite.setTextureRect(sf::IntRect(0, 0, 18, 18));
	float timer;
	__asm {

		mov			eax, 10
		mov 		ebx, 10
		sub		    eax, ebx
		mov			timer, eax
		

	}
	std::cout << timer;
	float delay= 0.3;
	
	sf::Clock clock;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		sf::Event event;
		while (window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed)
				
				window.close();
			
			if (event.type == sf::Event::KeyPressed)
			{
				
				if (event.key.code == sf::Keyboard::Left)
				{
					tetramino.moveHoriz(window, -1);
				}
				
				else if (event.key.code == sf::Keyboard::Right)
				{
					tetramino.moveHoriz(window, 1);
				}
				
				else if (event.key.code == sf::Keyboard::Up)
				{
					tetramino.rotate();
				}
			}
	
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) delay = 0.05;
		}
		if (timer > delay)
		{
			tetramino.moveDown(window);
			timer = 0;
		}
		checkLine(userPoints);
		delay = 0.3;
		window.clear(sf::Color::Color(240,128,128));
		int tetrisFeildTop{ 100 };
		int tetrisFeildLeft{ 90 };
		window.draw(sprite_background);
		for (int varHeight = 0; varHeight < field_height; varHeight++)
		{
			for (int j = 0; j < field_width; j++)
			{
				if (field[varHeight][j] == 0)
				{
					std::cout << "empty field" << std::endl;
					sprite.setTextureRect(sf::IntRect(8 * 18, 0, 18, 18));
					sprite.setPosition(tetrisFeildLeft + j * 18, tetrisFeildTop + varHeight * 18);
					window.draw(sprite);
				}
				else
				{
					sprite.setTextureRect(sf::IntRect(field[varHeight][j] * 18, 0, 18, 18));
				}
				sprite.setPosition(tetrisFeildLeft + j * 18, tetrisFeildTop + varHeight * 18);
				window.draw(sprite);
			}
		}
		tetramino.draw(window, sprite, tetrisFeildLeft, tetrisFeildTop);
		sf::Font font;
		if (!font.loadFromFile("ofont.ru_Roboto.ttf"))
		{
			
		}
		sf::Text text;
		text.setFont(font);
		std::string userPointsString = "Score: " + std::to_string(userPoints);
		text.setString(userPointsString);
		text.setCharacterSize(48);
		text.setFillColor(sf::Color::Black);
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		text.setPosition(190.f, 10.f);
		window.draw(text);
		window.display();	
	}
	return 0;
}