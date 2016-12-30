#include "Graphique.hpp"

Graphique::Graphique(Socket &socket, const int &_x, const int &_y, const std::string &_title) : window(sf::VideoMode(_x, _y), _title), roomManager(socket), socket(socket)
{
	this->x = _x;
	this->y = _y;
	this->title = _title;
	this->open = true;
	this->ip = "";
	this->username = "";
	this->firstTime = true;
	this->user = Player;
	this->activeScene = ScenesEnum::InGame;
}

Graphique::~Graphique()
{
}

bool Graphique::initWindow(const int &_x, const int &_y, const std::string &_title)
{
	this->x = _x;
	this->y = _y;
	this->title = _title;
	return (true);
}

const std::string	&Graphique::getUsername() const
{
	return (username);
}

const StatusEnum	&Graphique::getStatusUser() const
{
	return (user);
}

void	Graphique::setStatusUser(const StatusEnum &state)
{
	this->user = state;
}

bool Graphique::loadCurrentScene()
{
	switch (activeScene)
	{
	case ScenesEnum::getIp:
		return (linkServerScene());
	case ScenesEnum::loading:
		return (loadingScene());
	case ScenesEnum::listRooms:
		return (showRoomScene());
	case ScenesEnum::lobby:
		return (lobbyScene());
	case ScenesEnum::InGame:
		return (inGameScene());
	default:
		return (linkServerScene());
	}
}

Scene	&Graphique::getActiveScene()
{
	switch (activeScene)
	{
	case ScenesEnum::getIp:
		return (linkServer);
	case ScenesEnum::loading:
		return (loading);
	case ScenesEnum::listRooms:
		return (listRooms);
	case ScenesEnum::lobby:
		return (lobby);
	case ScenesEnum::InGame:
		return (inGame);
	default:
		return (linkServer);
	}
}

bool Graphique::loadNextScene()
{
	firstTime = true;
	switch (activeScene)
	{
	case ScenesEnum::getIp:
		prevScene = activeScene;
		activeScene = ScenesEnum::loading;
		return (loadingScene());
	case ScenesEnum::loading:
		if (prevScene == ScenesEnum::getIp) {
			activeScene = ScenesEnum::listRooms;
			return (showRoomScene());
		} else {
			activeScene = ScenesEnum::getIp;
			prevScene = ScenesEnum::null;
			return (linkServerScene());
		}
	case ScenesEnum::listRooms:
		prevScene = activeScene;
		activeScene = ScenesEnum::lobby;
		return (lobbyScene());
	default:
		activeScene = ScenesEnum::getIp;
		prevScene = ScenesEnum::null;
		return (linkServerScene());
	}
}

bool Graphique::loadPrevScene()
{
	switch (prevScene)
	{
	case ScenesEnum::getIp:
		activeScene = prevScene;
		prevScene = ScenesEnum::null;
		return (linkServerScene());
	case ScenesEnum::null:
		activeScene = ScenesEnum::getIp;
		prevScene = ScenesEnum::null;
		return (linkServerScene());
	case ScenesEnum::listRooms:
		activeScene = prevScene;
		return (showRoomScene());
	default:
		activeScene = ScenesEnum::getIp;
		prevScene = ScenesEnum::null;
		return (linkServerScene());
	}
}

const std::string		&Graphique::getIp() const
{
	return (ip);
}

void					Graphique::setUsername(const std::string &str)
{
	this->username = str;
}

void					Graphique::setIp(const std::string &str)
{
	this->ip = str;
}

bool		Graphique::refreshFrame()
{
	bool	retValue;

	retValue = loadCurrentScene();
	window.clear(sf::Color::Black);
	if (drawObject() == false)
		return (false);
	window.display();
	return (retValue);
}

bool Graphique::drawObject()
{
	getActiveScene().draw(window);
	return (true);
}

bool Graphique::closeWindow()
{
	this->open = false;
	this->window.close();
	return (true);
}

bool Graphique::isOpen() const
{
	return this->open;
}

bool Graphique::loadingScene()
{
	if (firstTime) {
		if (!loading.loadFont("./assets/fonts/Inconsolata-Regular.ttf"))
			return (false);

		// Title
		loading.addText(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 50 * static_cast<float>(window.getSize().y) / 1080), "Loading...", 48);
		loading.setTextColor(0, sf::Color::White);
		firstTime = false;
	}
	return (true);
}

bool Graphique::linkServerScene()
{
	if (firstTime) {
		focus = 0;

		if (!linkServer.loadFont("./assets/fonts/Inconsolata-Regular.ttf"))
			return (false);


		// IP
		linkServer.addText(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 315 * static_cast<float>(window.getSize().y) / 1080), "Ip:");
		linkServer.addText(sf::Vector2f(90 * static_cast<float>(window.getSize().x) / 1920, 360 * static_cast<float>(window.getSize().y) / 1080), "");
		linkServer.addText(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 360 * static_cast<float>(window.getSize().y) / 1080), ">");

		// Username
		linkServer.addText(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 410 * static_cast<float>(window.getSize().y) / 1080), "Username:");
		linkServer.addText(sf::Vector2f(90 * static_cast<float>(window.getSize().x) / 1920, 455 * static_cast<float>(window.getSize().y) / 1080), "");
		linkServer.addText(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 455 * static_cast<float>(window.getSize().y) / 1080), ">");

		// Button
		linkServer.addButton(sf::Vector2f(230 * static_cast<float>(window.getSize().x) / 1920, 550 * static_cast<float>(window.getSize().y) / 1080), "Connect");
		linkServer.addButton(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 360 * static_cast<float>(window.getSize().y) / 1080), "", sf::Color::Transparent, 30, true);
		linkServer.addButton(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 455 * static_cast<float>(window.getSize().y) / 1080), "", sf::Color::Transparent, 30, true);

		linkServer.setTextColor(2, sf::Color::Yellow);
		linkServer.setTextColor(5, sf::Color::Yellow);

		// Title
		linkServer.addText(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 50 * static_cast<float>(window.getSize().y) / 1080), "R-Type", 48);
		linkServer.setTextColor(6, sf::Color::Red);
		firstTime = false;
	}

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			closeWindow();
			break;
		case sf::Event::MouseButtonPressed:
			pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			if (linkServer.buttonEvent(0, pos))
			{
				ip = linkServer.getText(1);
				username = linkServer.getText(4);
				if (ip.length() > 0 && username.length() > 0)
					loadNextScene();
				return (ip.length() > 0 && username.length() > 0);
			}
			else if (linkServer.buttonEvent(1, pos))
				focus = 0;
			else if (linkServer.buttonEvent(2, pos))
				focus = 1;
			break;
		case sf::Event::TextEntered:
			if (event.text.unicode < 128)
			{
				switch (event.text.unicode) {
				case 8:
					linkServer.removeBackText(focus == 0 ? 1 : 4);
					break;
				case 0:
					break;
				case 13:
					ip = linkServer.getText(1);
					username = linkServer.getText(4);
					if (ip.length() > 0 && username.length() > 0)
						loadNextScene();
					return (ip.length() > 0 && username.length() > 0);
					break;
				case 9:
					focus = focus ? 0 : 1;
					break;
				default:
					linkServer.addToText(focus == 0 ? 1 : 4, event.text.unicode);
					break;
				}
			}
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				closeWindow();
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
	linkServer.setTextColor(focus != 0 ? 4 : 1, sf::Color::Yellow);
	linkServer.setTextColor(focus != 0 ? 1 : 4, sf::Color::White);
	linkServer.setTextColor(focus != 0 ? 5 : 2, sf::Color::Yellow);
	linkServer.setTextColor(focus != 0 ? 2 : 5, sf::Color::White);
	return (true);
}

bool	Graphique::showRoomScene()
{
	unsigned int	j = 0;
	unsigned int	k = 0;

	if (firstTime) {

		if (!listRooms.loadFont("./assets/fonts/Inconsolata-Regular.ttf"))
			return (false);

		listRooms.addText(sf::Vector2f(100 * static_cast<float>(window.getSize().x) / 1920, 100 * static_cast<float>(window.getSize().y) / 1080), "List of Room", 48);
		listRooms.setTextColor(0, sf::Color::Blue);

		//roomManager.roomList();
		for (std::list<Room>::const_iterator i = roomManager.getRooms().begin(); i != roomManager.getRooms().end(); i++) {
			if (i->getState() == RtypeProtocol::roomState::Waiting)
				listRooms.addButs(i->getText(), sf::Vector2f(50, j * 50 + 150), sf::Vector2f(400, 40), sf::Color::Green, sf::Color::Transparent, Button::buttonEnum::Room);
			else if (i->getState() == RtypeProtocol::roomState::Full)
				listRooms.addButs(i->getText(), sf::Vector2f(50, j * 50 + 150), sf::Vector2f(400, 50), sf::Color::Yellow, sf::Color::Transparent, Button::buttonEnum::Room);
			else
				listRooms.addButs(i->getText(), sf::Vector2f(50, j * 50 + 150), sf::Vector2f(400, 50), sf::Color::Red, sf::Color::Transparent, Button::buttonEnum::Room);
			j++;
		}
		listRooms.addButs("Player", sf::Vector2f(100, 600), sf::Vector2f(100, 50), sf::Color::Red, sf::Color::Transparent, Button::buttonEnum::Player);
		listRooms.addButs("Spectator", sf::Vector2f(300, 600), sf::Vector2f(160, 50), sf::Color::White, sf::Color::Transparent, Button::buttonEnum::Spectat);
		listRooms.addButs("Create", sf::Vector2f(500, 600), sf::Vector2f(100, 50), sf::Color(204, 51, 102), sf::Color::Transparent, Button::buttonEnum::Create);
		firstTime = false;
	}

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			closeWindow();
			break;
		case sf::Event::MouseButtonPressed:
			pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			for (std::list<Room>::const_iterator l = roomManager.getRooms().begin(); l != roomManager.getRooms().end(); l++) {
				if (listRooms.buttonClik(k, pos)) {
					if (k < roomManager.getRooms().size() && l->getState() == RtypeProtocol::roomState::Waiting) {
						user == Player ?
						std::cout << "You're joining the room as Player" << std::endl :
						std::cout << "You're joining the room as spectator" << std::endl;
						if (roomManager.joinRoom(l->getId(), user == Player ? false : true)) {
							return (loadNextScene());
						}
						// To delete once the connection with the server is correctly established or the demo is finished
						else {
							return (loadNextScene());
						}
					}
				}
				k++;
			}
			k = 0;
			for (std::vector<Button *>::const_iterator i = listRooms.getButtons().begin(); i != listRooms.getButtons().end(); i++) {
				if (listRooms.buttonClik(k, pos)) {
					if ((*i)->getId() == Button::buttonEnum::Player) {
						setStatusUser(Player);
						listRooms.getButtons()[k]->setTxtColor(sf::Color::Red);
						listRooms.getButtons()[k + 1]->setTxtColor(sf::Color::White);
					}
					else if ((*i)->getId() == Button::buttonEnum::Spectat) {
						setStatusUser(Spectator);
						listRooms.getButtons()[k]->setTxtColor(sf::Color::Red);
						listRooms.getButtons()[k - 1]->setTxtColor(sf::Color::White);
					}
					else if ((*i)->getId() == Button::buttonEnum::Room) {
						// create room
					}
				}
				k++;
			}


		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				closeWindow();
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
	return (true);
}

bool	Graphique::lobbyScene()
{
	int			k = 0;
	std::string	room_str;

	if (firstTime) {

		if (!lobby.loadFont("./assets/fonts/Inconsolata-Regular.ttf"))
			return (false);
		room_str = "Lobby - Room " + std::to_string(roomManager.getCurrentRoom().getId());
		lobby.addText(sf::Vector2f(100 * static_cast<float>(window.getSize().x) / 1920, 100 * static_cast<float>(window.getSize().y) / 1080), room_str, 48);
		lobby.setTextColor(0, sf::Color::Yellow);

		if (roomManager.getCurrentRoom().getPlayer1() != "")
			lobby.addText(sf::Vector2f(100, 200), roomManager.getCurrentRoom().getPlayer1() + (roomManager.getCurrentRoom().getP1Ready() ? "\tReady" : "\tNot ready"), 30);
		if (roomManager.getCurrentRoom().getPlayer2() != "")
			lobby.addText(sf::Vector2f(100, 250), roomManager.getCurrentRoom().getPlayer2() + (roomManager.getCurrentRoom().getP2Ready() ? "\tReady" : "\tNot ready"), 30);
		if (roomManager.getCurrentRoom().getPlayer3() != "")
			lobby.addText(sf::Vector2f(100, 300), roomManager.getCurrentRoom().getPlayer3() + (roomManager.getCurrentRoom().getP3Ready() ? "\tReady" : "\tNot ready"), 30);
		if (roomManager.getCurrentRoom().getPlayer4() != "")
			lobby.addText(sf::Vector2f(100, 350), roomManager.getCurrentRoom().getPlayer4() + (roomManager.getCurrentRoom().getP4Ready() ? "\tReady" : "\tNot ready"), 30);

		lobby.addButs("Ready", sf::Vector2f(100, 600), sf::Vector2f(160, 50), sf::Color::White, sf::Color::Transparent, Button::buttonEnum::Ready);
		lobby.addButs("Not Ready", sf::Vector2f(350, 600), sf::Vector2f(160, 50), sf::Color::Red, sf::Color::Transparent, Button::buttonEnum::NotReady);
		lobby.addButs("Leave", sf::Vector2f(600, 600), sf::Vector2f(160, 50), sf::Color::Blue, sf::Color::Transparent, Button::buttonEnum::Leave);
		firstTime = false;
	}

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			closeWindow();
			break;
		case sf::Event::MouseButtonPressed:
			pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			for (std::vector<Button *>::const_iterator i = lobby.getButtons().begin(); i != lobby.getButtons().end(); i++) {
				if (lobby.buttonClik(k, pos)) {
					switch ((*i)->getId())
					{
					case Button::buttonEnum::Ready:
						roomManager.setCurrentPlayerReadiness(true);
						std::cout << "READY !" << std::endl;
						/*if (username == roomManager.getCurrentRoom().getPlayer1())
							roomManager.getCurrentRoom().setP1Ready(true);
						else if (username == roomManager.getCurrentRoom().getPlayer2())
							roomManager.getCurrentRoom().setP2Ready(true);
						else if (username == roomManager.getCurrentRoom().getPlayer3())
							roomManager.getCurrentRoom().setP3Ready(true);
						else if (username == roomManager.getCurrentRoom().getPlayer4())
							roomManager.getCurrentRoom().setP4Ready(true);*/
						break;
					case Button::buttonEnum::NotReady:
						roomManager.setCurrentPlayerReadiness(false);
						std::cout << "NOT READY !" << std::endl;
						/*if (username == roomManager.getCurrentRoom().getPlayer1())
							roomManager.getCurrentRoom().setP1Ready(false);
						else if (username == roomManager.getCurrentRoom().getPlayer2())
							roomManager.getCurrentRoom().setP2Ready(false);
						else if (username == roomManager.getCurrentRoom().getPlayer3())
							roomManager.getCurrentRoom().setP3Ready(false);
						else if (username == roomManager.getCurrentRoom().getPlayer4())
							roomManager.getCurrentRoom().setP4Ready(false);*/
						break;
					case Button::buttonEnum::Leave:
						std::cout << "LEAVE !" << std::endl;
						return (loadPrevScene());
					default:
						break;
					}
				}
				k++;
			}

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				closeWindow();
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
	return (true);
}

bool Graphique::handleServerCode()
{
	RtypeProtocol::Data::Code			code;
	RtypeProtocol::Data::PlayerCharge	charge;
	RtypeProtocol::Data::ObjectCreate	create;

	if (!socket.receive(sizeof(RtypeProtocol::Data::RoomJoined)))
		return (false);
	socket.getReceivedData().read(reinterpret_cast<char *>(&(code.code)), sizeof(code.code));
	switch (RtypeProtocol::convertServer(code.code)) {
	case RtypeProtocol::serverCodes::ErrServerClosing:
		socket.setInternalError(true);
		break;
	case RtypeProtocol::serverCodes::GameOver:
		// TODO QUIT THE GAME
		break;
	case RtypeProtocol::serverCodes::PlayerCharge:
		socket.getReceivedData().read(reinterpret_cast<char *>(&(charge.charge1)), sizeof(charge.charge1));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(charge.charge2)), sizeof(charge.charge2));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(charge.charge3)), sizeof(charge.charge3));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(charge.charge4)), sizeof(charge.charge4));
		// TODO Charge Player

		break;
	case RtypeProtocol::serverCodes::PlayerDead:
		// TODO kill Player
		break;
	case RtypeProtocol::serverCodes::PlayerLeft:
		// TODO leave Player
		break;
	case RtypeProtocol::serverCodes::PlayerLives:
		// TODO set player's life
		break;
	case RtypeProtocol::serverCodes::PlayerScore:
		// TODO set player' score
		break;
	case RtypeProtocol::serverCodes::ObjectCreate:
		// TODO Create an object
		socket.getReceivedData().read(reinterpret_cast<char *>(&(create.id)), sizeof(create.id));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(create.posX)), sizeof(create.posX));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(create.posY)), sizeof(create.posY));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(create.vecX)), sizeof(create.vecX));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(create.vecY)), sizeof(create.vecY));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(create.name)), sizeof(create.name));
		newObject = Object(create.name, sf::Vector2i(create.posX, create.posY), sf::Vector2i(create.vecX, create.vecY), create.id);
		inGame.addObject(newObject);
		break;
	case RtypeProtocol::serverCodes::ObjectDestroy:
		// TODO Destroy an object
		break;
	case RtypeProtocol::serverCodes::ObjectUpdate:
		// TODO Update an object
		break;
	default:
		break;
	}
	return (true);
}

bool	Graphique::inGameScene()
{

	if (user == Spectator) {
		return (true);
	}

	if (firstTime) {

		// set limit FPS
		window.setFramerateLimit(60);

		// set Background
		newObject.setLongName(100);
		newObject.setId(100);
		newObject.addAComponent(1, Sprite::TypeSpriteEnum::Background, 0);
		inGame.addObject(newObject);
		newObject = Object();
		newObject.setLongName(101);
		newObject.setId(101);
		newObject.addAComponent(1, Sprite::TypeSpriteEnum::Background, 0);
		newObject.setPos(static_cast<int>(newObject.getComponent(1).getCSprite().getTexture().getSize().x), 0);
		inGame.addObject(newObject);
		//inGame.setBGSprite("./assets/Sprites/espace_background_rtype.jpg");


		// set Var ship
		maxspeed = 4.0f;
		accel = 1.5f;
		decel = 0.1f;
		// To delete down
		position.x = (10 * static_cast<float>(window.getSize().x)) / 100;
		position.y = (40 * static_cast<float>(window.getSize().y)) / 100;
		// To delete up
		velocity.x = 0.1f;
		velocity.y = 0.1f;




		// set the mainShip
		mainShip.setLife(1);
		mainShip.setScore(0);
		mainShip.setId(1);
		mainShip.addAComponent(1, Sprite::TypeSpriteEnum::Player1, 0);
		mainShip.setPos(position.x, position.y);
		// SEND POS
		inGame.addObject(mainShip);

		firstTime = false;
	}

	inGame.refreshAnimation();
	inGame.restartClock();

	// REMETTRE AVANT DE PUSH
	//handleServerCode();


	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			//
			// SEND MSG SERVER LEAVE / QUIT
			//

			closeWindow();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				//
				// SEND MSG SERVER LEAVE / QUIT
				//
				closeWindow();
				break;
			case sf::Keyboard::Return:
				//
				// SEND MSG SERVER LEAVE
				//

				break;
			case sf::Keyboard::Space:
				std::cout << "Charge !" << std::endl;
				//
				// TODO AXELOPETO CHARGE
				//

				break;
			default:
				break;
			}
			break;
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::Space) {
				std::cout << "Shot !" << std::endl << std::endl;
				//
				// TODO AXELOPETO SHOOT
				//

			}
			break;
		default:
			break;
		}
	}


	// update Velocity
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		velocity.y -= accel;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		velocity.y += accel;
	}
	else {
		velocity.y *= decel;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		velocity.x -= accel;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		velocity.x += accel;
	}
	else {
		velocity.x *= decel;
	}

	// Check maximum speed
	actualspeed = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
	if (actualspeed > maxspeed)
	{
		velocity *= maxspeed / actualspeed;
	}

	// set Position
	position += velocity;
	if (position.x < 0)
		position.x = 0;
	else if (position.x > static_cast<float>(window.getSize().x) - static_cast<float>(inGame.getObj(1).getComponent(1).getCSprite().getSprite().getGlobalBounds().width))
		position.x = static_cast<float>(window.getSize().x) - static_cast<float>(inGame.getObj(1).getComponent(1).getCSprite().getSprite().getGlobalBounds().width);
	if (position.y < 0)
		position.y = 0;
	else if (position.y > static_cast<float>(window.getSize().y) - static_cast<float>(inGame.getObj(1).getComponent(1).getCSprite().getSprite().getGlobalBounds().height))
		position.y = static_cast<float>(window.getSize().y) - static_cast<float>(inGame.getObj(1).getComponent(1).getCSprite().getSprite().getGlobalBounds().height);
	inGame.setObjPos(1, sf::Vector2i(position.x, position.y));
	//
	//  SEND MSG SERVER POSITION
	//


	return (true);
}
