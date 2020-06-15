#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <random>						//////////////////////////////////////////////////
#include "Bird.h"						//YOU CAN CHECK THE LATEST VERSION ON MY GITHUB	//
#include "Pipe.h"						//https://github.com/AdamStanekPolSl/FlappyAdam	//
#include "Cloud.h"						//////////////////////////////////////////////////
#include "InOut.h"						//Running this project require SFML for C++,	//
#include <iostream>						//visit SFML page to learn more about this lib	//
using namespace std;					//https://www.sfml-dev.org/tutorials/2.5/		//
using namespace sf;						//////////////////////////////////////////////////

//SETTINGS AND GLOBAL VARIABLES
string gameTitle{ "FlappyAdam" };
string directory{ };
unsigned int resX = 1280;
unsigned int resY = 720;
unsigned int fpsLimit = 60;
bool fullScreen = 0;
bool Vsync = 1;
bool loadingFailure = 0;
bool configure = 0;//true opens console where you can change game options

Event event;
Color background(173, 216, 230, 255);
InOut file;
default_random_engine generator;


//TEMPLATES AND FUNCTIONS
template <class type1, class type2> bool isInteract(type1& object1, type2& object2);//collision = true
template <class type1> bool outOfScreen(type1& object);//out of screen (left side) = true
template<class type1> bool settingValue(type1& variable);//true = success with setting new Value
bool mouse(Text text, const Window& window);//true = text and mouse collision
bool load(string fileToLoad);//testing loading game files, true = ok
bool loadDirectory();//load custom default path, false = localDirectory.txt not found
bool pointsToFile(unsigned int point);//saves personal best, true = success
unsigned int pointsFromFile(unsigned int point);//loads personal best, returns points



int main()
{
	while (true)//whole game
	{
		system("cls");
		if (!loadDirectory())
			cout << "Unable to load custom directory from localDirectory.txt" << endl;		//CONSOLE COMMANDS WHILE LOADING
		else
			file.setSettingName(directory);
		if (!file.loadConfig())
			file.saveConfig();
		else
			loadingFailure = 0;
		load("PNG/cloud1.png");//testing load functions
		load("PNG/pipe.png");
		load("PNG/bird.png");
		load("FONTS/prototype.ttf");
		if (loadingFailure)
		{
			cout << "All game files (ex. config.txt or PNG folder) should be in ";
			if (!directory.size() == 0)
				cout << directory;
			else
				cout << gameTitle << ".exe directory.";
			cout << endl
				<< "You can change default location of game files. Just edit localDirectory.txt," << endl
				<< "for example: C:/" + gameTitle + "/ Remember, that localDirectory.txt should be in " + gameTitle + ".exe directory."<<endl
				<< "Press any key to try to run the program with default settings." << endl;
			system("pause");
		}

		uniform_real_distribution<float> pipeDistribution(0, 0.29 * resY);//random pipe height
		uniform_int_distribution<int> cloudDistributionWidth(0, resX);//random clouds position
		uniform_int_distribution<int> cloudDistributionHeight(0, resY);

		bool pause{ 1 };
		bool gameOver{ 0 };
		float random{ pipeDistribution(generator) };
		unsigned int points{};
		unsigned int bestResult{};
		unsigned int fontSize{ static_cast<unsigned int>(resY) };
		const unsigned int numberOfClouds{ 10 };//stores how many clouds you want in game

		Vector2u resolution{ resX,resY };
		Clock pointsClock;//points counter
		Font prototype;
		Text score, play, exit, bestScore, set, setInfo;
		Bird bird;
		Pipe pipe1(resX, resY, 0);//initializing pipes
		Pipe pipe1up(resX, 0.15 * resY, 1);
		Pipe pipe2(1.5 * resX, resY + random, 0);
		Pipe pipe2up(1.5 * resX, 0.15 * resY + random, 1);
		pipe2.move();//moveng 2. pipes to correct position
		pipe2up.move();
		Cloud cloud[numberOfClouds];
		for (int i{}; i < numberOfClouds; i++)
		{
			int n = i % 3 + 1;
			cloud[i].restart(cloudDistributionWidth(generator), cloudDistributionHeight(generator), n);//loading different positions and textures
		}
		

		RenderWindow game;


		if (!prototype.loadFromFile(directory + "FONTS/prototype.ttf"))//loading font to variable
		{
			system("pause");
			return EXIT_FAILURE;
		}

		score.setFillColor(Color::Red);//setting for score text
		score.setFont(prototype);
		score.setCharacterSize(fontSize * 0.08f);
		score.setPosition(resX/2.f, 0.1*resY);


		bestScore.setFillColor(Color::Red);//for personal best
		bestScore.setFont(prototype);
		bestScore.setCharacterSize(fontSize * 0.10f);
		bestScore.setPosition(resX / 2.f, 0);


		play.setString("PLAY");//menu
		play.setFont(prototype);
		play.setCharacterSize(fontSize * 0.12f);
		play.setOrigin(play.getGlobalBounds().width / 2.f, play.getGlobalBounds().height / 2);
		play.setPosition(resX / 2.f, resY / 2 - resY * 0.12f);
		play.setFillColor(Color::Black);

		set.setString("SETTINGS");
		set.setFont(prototype);
		set.setCharacterSize(fontSize * 0.12f);
		set.setOrigin(set.getGlobalBounds().width / 2.f, set.getGlobalBounds().height / 2);
		set.setPosition(resX / 2.f, resY / 2);
		set.setFillColor(Color::Black);

		setInfo.setFont(prototype);//this text explains function of menu(for example "press spacebar to fly")
		setInfo.setCharacterSize(fontSize * 0.08f);
		setInfo.setPosition(resX/2.f, 0.9*resY);
		setInfo.setFillColor(Color::Black);

		exit.setString("EXIT");
		exit.setFont(prototype);
		exit.setCharacterSize(fontSize * 0.12f);
		exit.setOrigin(exit.getGlobalBounds().width / 2.f, exit.getGlobalBounds().height / 2);
		exit.setPosition(resX / 2.f, resY / 2 + resY * 0.12f);
		exit.setFillColor(Color::Black);

		if (fullScreen)
			game.create(VideoMode(resX, resY, 32), gameTitle, Style::Fullscreen);//recreating window with parameters
		else
			game.create(VideoMode(resX, resY, 32), gameTitle);

		game.setFramerateLimit(fpsLimit);
		game.setVerticalSyncEnabled(Vsync);

		Cursor cursor;
		if (cursor.loadFromSystem(Cursor::Hand))//setting mouuse to default hand cursor
			game.setMouseCursor(cursor);


		while (game.isOpen())//game loop
		{
			game.setSize(resolution);//prevents changing window size
			game.clear(background);
			game.pollEvent(event);
			for (int i{}; i < numberOfClouds; i++)
			{
				if (outOfScreen(cloud[i]))
					cloud[i].restart(resX, cloudDistributionHeight(generator),(i%3)+1);//move cloud to new starting position after it goes out of the window (left side)
				game.draw(cloud[i]);
			}

			if (event.type == Event::Closed || !game.hasFocus())
				pause = 1;
			if (event.type == Event::KeyPressed)//pause event
				if (event.key.code == Keyboard::Escape && !pause)
					pause = 1;
			if (!pause)//non pause instructions(GAME)
			{
				for (int i{};i<numberOfClouds;i++)
					cloud[i].update();
				game.setMouseCursorVisible(false);
				random = pipeDistribution(generator);
				if (outOfScreen(pipe1))
				{
					pipe1.restart(resX, resY + random);
					pipe1up.restart(resX, 0.15 * resY + random);//moving pipes after they go out of the left side of window
				}
				if (outOfScreen(pipe2))
				{
					pipe2.restart(resX, resY + random);
					pipe2up.restart(resX, 0.15 * resY + random);
				}
				if (pointsClock.getElapsedTime().asMilliseconds() >= 100.f)//add 1 point every 100 miliseconds
				{
					points++;
					pointsClock.restart();
				}
				pipe1.update();
				pipe1up.update();
				pipe2.update();
				pipe2up.update();
				bird.update();
			}
			else if (gameOver)// if fail
			{
				bird.restart();
				gameOver = 0;
			}
			score.setString("THIS RUN: "+to_string(points));
			score.setOrigin(score.getGlobalBounds().width/2.f, 0);//updating score string
			game.draw(bird);
			game.draw(pipe1);
			game.draw(pipe1up);
			game.draw(pipe2);
			game.draw(pipe2up);
			game.draw(score);
			if (bestResult)//draw best score if any
			{
				bestScore.setString("BEST: " + to_string(bestResult));
				bestScore.setOrigin(bestScore.getGlobalBounds().width / 2.f, 0);
				game.draw(bestScore);
			}
			if (pause)//pause menu
			{
				bestResult = pointsFromFile(bestResult);
				game.setMouseCursorVisible(true);
				if (mouse(play, game))//intersecting of mouse and "play" text
				{
					play.setFillColor(Color::Red);
					if (Mouse::isButtonPressed(Mouse::Left))
						pause = 0;
					setInfo.setString("Fly higher by pressing SPACEBAR");
					setInfo.setOrigin(setInfo.getGlobalBounds().width / 2.f, setInfo.getGlobalBounds().height / 2.f);
					game.draw(setInfo);
				}
				else
					play.setFillColor(Color::Black);
				if (mouse(set, game))
				{
					set.setFillColor(Color::Red);
					if (Mouse::isButtonPressed(Mouse::Left))
					{
						configure = 1;
						game.close();
					}
					setInfo.setString("Current run will be lost!");
					setInfo.setOrigin(setInfo.getGlobalBounds().width / 2.f, setInfo.getGlobalBounds().height / 2.f);
					game.draw(setInfo);
				}
				else
					set.setFillColor(Color::Black);
				if (mouse(exit, game))
				{
					exit.setFillColor(Color::Red);
					if (Mouse::isButtonPressed(Mouse::Left))
					{
						if (points > bestResult)
						{
							bestResult = points;
							if (!pointsToFile(bestResult))
								cout << "Unable to save personalBest.txt" << endl;
						}
						game.close();
					}
					setInfo.setString("Exits the game");
					setInfo.setOrigin(setInfo.getGlobalBounds().width / 2.f, setInfo.getGlobalBounds().height / 2.f);
					game.draw(setInfo);
				}
				else
					exit.setFillColor(Color::Black);
				game.draw(set);
				game.draw(play);
				game.draw(exit);
			}
			else if (bird.screenCollision() || isInteract(bird, pipe1) || isInteract(bird, pipe1up) ||//true when you hit pipe or screen frame
				isInteract(bird, pipe2) || isInteract(bird, pipe2up))
			{
				pause = 1;
				gameOver = 1;
				if (points > bestResult)
				{
					bestResult = points;
					if (!pointsToFile(bestResult))
						cout << "Unable to save personalBest.txt" << endl;
				}
				points = 0;//restarts game
				pipe1.restart(resX, resY + random);
				pipe1up.restart(resX, 0.15 * resY + random);
				pipe2.restart(1.5 * resX, resY + random);
				pipe2up.restart(1.5 * resX, 0.15 * resY + random);
				pipe2.move();
				pipe2up.move();
				pipe1.gameOver();
				pipe1up.gameOver();
				pipe2.gameOver();
				pipe2up.gameOver();
			}
			game.display();
		}
		if (configure) //setting options
		{
			if (points > bestResult)
			{
				bestResult = points;
				if (!pointsToFile(bestResult))
					cout << "Unable to save personalBest.txt" << endl;
			}
			while (true)//repeats if you try to set wrong value
			{
				system("cls");
				cout << "---SETTINGS---" << endl
					<< "Set resolution. For example \"1080\" to set FullHD. The game supports only 16:9 aspect ratio." << endl
					<<"Press Enter to skip this setting."<<endl;
				if (settingValue(resY))
					break;
			}
			resX = resY * 16 / 9;
			while (true)//repeats if you try to set wrong value
			{
				system("cls");
				cout << "---SETTINGS---" << endl
					<< "Full Screen Mode (1/0). For example \"1\" to enable." << endl
					<< "Press Enter to skip this setting." << endl;
				if (settingValue(fullScreen))
					break;
			}
			while (true)//repeats if you try to set wrong value
			{
				system("cls");
				cout << "---SETTINGS---" << endl
					<< "Vertical Sync Mode (1/0). For example \"1\" to enable." << endl
					<< "Press Enter to skip this setting." << endl;
				if (settingValue(Vsync))
					break;
			}
			configure = 0;
			file.saveConfig();//saving configuration
		}
		else
			return(0);
	}
}
//DEFINITIONS
template <class type1, class type2> bool isInteract(type1& object1, type2& object2)
{
	return (object1.right() >= object2.left() && object1.left() <= object2.right() &&
		object1.down() >= object2.up() && object1.up() <= object2.down());
}

template <class type1> bool outOfScreen(type1& object)
{
	return object.right() < 0;
}

template<class type1> bool settingValue(type1& variable)
{
	string dataFromKeybord{};
	getline(cin, dataFromKeybord);
	if (dataFromKeybord.size() == 0)
		return true;
	if (typeid(variable) == typeid(bool))
	{
		if (dataFromKeybord.size() == 1)
		{
			if (dataFromKeybord[0] == 48)
				variable = 0;
			else if (dataFromKeybord[0] == 49)
				variable = 1;
			else
				return false;
		}
		else
			return false;
	}
	else
	{
		int j{};
		for (int i{}; i < dataFromKeybord.size(); i++)
		{
			if (dataFromKeybord[i] >= 48 && dataFromKeybord[i] <= 57)
				j++;
		}
		if (j == dataFromKeybord.size() && stoi(dataFromKeybord)>=144)
		{
			variable = stoi(dataFromKeybord);
		}
		else
			return false;
	}
	return true;
}

bool mouse(Text text, const Window& window)
{
	return ((text.getPosition().x - text.getOrigin().x) <= Mouse::getPosition(window).x &&
		(text.getPosition().x + text.getOrigin().x) >= Mouse::getPosition(window).x &&
		(text.getPosition().y) <= Mouse::getPosition(window).y &&
		(text.getPosition().y) + 2 * text.getOrigin().y >= Mouse::getPosition(window).y);
}

bool load(string fileToLoad)
{
	string settingName{ directory + fileToLoad };
	ifstream read(settingName);
	if (!read.is_open())
	{
		cout << "Cannot open " << settingName << endl;
		read.close();
		loadingFailure = 1;
		return false;
	}
	read.close();
	return true;
}

bool loadDirectory()
{
	ifstream read{ "localDirectory.txt" };
	if (read.is_open())
	{
		getline(read, directory);
		read.close();
		return true;
	}
	read.close();
	return false;
}

bool pointsToFile(unsigned int point)
{
	string path{ directory + "personalBest.bin"};
	ofstream write;
	write.open(path, ios::trunc | ios::binary);
	if (!write.is_open())
		return false;
	else
		write << point;
	write.close();
	return true;
}

unsigned int pointsFromFile(unsigned int point)
{
	string path{ directory + "personalBest.bin" };
	ifstream read;
	read.open(path, ios::binary);
	if (!read.is_open())
		return 0;
	else
		read >> point;
	read.close();
	return point;
}