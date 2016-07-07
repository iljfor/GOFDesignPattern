
#pragma once

//
// 이 프로젝트는 GoF Design Patterns의 Abstact Pattern 샘플이다.
// (Maze, MapSite, Room, Wall, Door의 Object들로 구성되어 있다.)
// This project is GoF Design Pattern of Abstact Pattern Sample


#include <iostream>
#include <list>

using namespace std;



//
// 방향을 타나태는 타입 (Type of direction)
enum Direction {
	dirNorth = 0,
	dirSouth,
	dirEast,
	dirWest,
	dirMax,
};


//
// Interface Class MapSite
class MapSite
{
public:
	virtual void Enter(void) = NULL;
};


//
// Wall class
class Wall : public MapSite
{
public:
	virtual void Enter(void) { cout << "Is Wall Not Enter" << endl; }
};


//
// Bombed Wall class
class BombedWall : public Wall
{
public:
	virtual void Enter(void) { cout << "Is Boomed Wall!!!" << endl; }
};


//
// Room class
class Room : public MapSite
{
public:
	Room(int nRoomNo) { m_nRoomNo = nRoomNo; }

	MapSite*	GetSite(Direction direct) { return m_lpMapSite[direct]; }
	void	SetSite(Direction direct, MapSite* lpMapSite) { m_lpMapSite[direct] = lpMapSite; }

	virtual void Enter(void) { cout << "Is Room " << m_nRoomNo << endl; }

protected:
	MapSite*	m_lpMapSite[dirMax];
	int		m_nRoomNo;
};


//
// Enchanted Room class
class EnchantedRoom : public Room
{
public:
	EnchantedRoom(int nRoomNo)
		: Room(nRoomNo)
	{ }

	MapSite*	GetSite(Direction direct) { return m_lpMapSite[direct]; }
	void	SetSite(Direction direct, MapSite* lpMapSite) { m_lpMapSite[direct] = lpMapSite; }

	virtual void Enter(void) { cout << "Is Enchanted Room " << m_nRoomNo << endl; }
};


//
// Room with a Bomb class
class RoomWithABomb : public Room
{
public:
	RoomWithABomb(int nRoomNo)
		: Room(nRoomNo)
	{ }

	MapSite*	GetSite(Direction direct) { return m_lpMapSite[direct]; }
	void	SetSite(Direction direct, MapSite* lpMapSite) { m_lpMapSite[direct] = lpMapSite; }

	virtual void Enter(void) { cout << "Is With a Bomb Room" << m_nRoomNo << endl; }
};



//
// Door class
class Door : public MapSite
{
public:
	Door(Room* lpRoomFront, Room* lpRoomBack) { m_lpRoomFront = lpRoomFront; m_lpRoomBack = lpRoomBack; m_fOpen = false; }

	virtual void Enter(void) { m_fOpen = true; cout << "Door Open" << endl; }

	bool	IsOpen(void) { return m_fOpen; }
	Room*	OtherSideFrom(const Room* lpRoom)
	{
		if (lpRoom == m_lpRoomFront)
			return m_lpRoomBack;
		if (lpRoom == m_lpRoomBack)
			return m_lpRoomFront;
	 }

protected:
	bool	m_fOpen;
	Room*	m_lpRoomFront;
	Room*	m_lpRoomBack;
};


//
// Door Needing Spell class
class DoorNeedingSpell : public Door
{
public:
	DoorNeedingSpell(Room* lpRoomFront, Room* lpRoomBack)
		: Door(lpRoomFront, lpRoomBack)
	{
	}

	virtual void Enter(void) { m_fOpen = true; cout << "Door Needing Spell Open" << endl; }
};


//
// Maze class
class Maze
{
public:
	void	AddRoom(Room* lpRoom)
	{ 
		if (NULL != lpRoom)
			m_Rooms.insert(m_Rooms.end(), lpRoom);
	}

	Room*	RoomNo(int nRoomNo)
	{
		if (m_Rooms.size() > nRoomNo && 0 <= nRoomNo)
		{
			int i = 0;
			list<Room*>::iterator it;
			for (it = m_Rooms.begin(); it != m_Rooms.end(); it++, i++)
			{
				if (i == nRoomNo)
					return *it;
			}
		}

		return NULL;
	}

protected:
	list<Room*>	m_Rooms;
};


//
// Maze Factory class
class MazeFactory
{
public:
	MazeFactory(void) { };

	virtual Maze*	MakeMaze(void) const { return new Maze; }
	virtual Wall*	MakeWall(void) const { return new Wall; }
	virtual Room*	MakeRoom(int nRoomNum) const { return new Room(nRoomNum); }
	virtual Door*	MakeDoor(Room* lpRoomFront, Room* lpRoomBack) { return new Door(lpRoomFront, lpRoomBack); }
};


//
// Enchanted Maze Factory
class EnchantedMazeFactory : public MazeFactory
{
public:
	EnchantedMazeFactory(void) { };

	virtual Room*	MakeRoom(int nRoomNum) const { return new EnchantedRoom(nRoomNum); }
	virtual Door*	MakeDoor(Room* lpRoomFront, Room* lpRoomBack) { return new DoorNeedingSpell(lpRoomFront, lpRoomBack); }
};


//
// Bombed Maze Factory
class BombedMazeFactory : public MazeFactory
{
public:
	BombedMazeFactory(void) { };

	virtual Wall*	MakeWall(void) const { return new BombedWall; }
	virtual Room*	MakeRoom(int nRoomNum) const { return new RoomWithABomb(nRoomNum); }
};


//
// MazeGame class
class MazeGate : public Maze
{
public:
	Maze*	CreateMaze(MazeFactory& Factory)
	{
		Maze* lpActiveMaze = Factory.MakeMaze();
		if (NULL == lpActiveMaze)
			return NULL;
		Room* lpRoomFront = Factory.MakeRoom(1);
		if (NULL == lpRoomFront)
			return NULL;
		Room* lpRoomBack = Factory.MakeRoom(2);
		if (NULL == lpRoomBack)
			return NULL;
		Door* lpDoor = Factory.MakeDoor(lpRoomFront, lpRoomBack);
		if (NULL == lpDoor)
			return NULL;

		lpActiveMaze->AddRoom(lpRoomFront);
		lpActiveMaze->AddRoom(lpRoomBack);

		lpRoomFront->SetSite(dirNorth, Factory.MakeWall());
		lpRoomFront->SetSite(dirEast, lpDoor);
		lpRoomFront->SetSite(dirSouth, Factory.MakeWall());
		lpRoomFront->SetSite(dirWest, Factory.MakeWall());

		lpRoomBack->SetSite(dirNorth, Factory.MakeWall());
		lpRoomBack->SetSite(dirEast, Factory.MakeWall());
		lpRoomBack->SetSite(dirSouth, Factory.MakeWall());
		lpRoomBack->SetSite(dirWest, lpDoor);

		return lpActiveMaze;
	}
};