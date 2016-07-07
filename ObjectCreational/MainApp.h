
#pragma once

//
// 이 프로젝트는 GoF Design Patterns의 생성 패턴 샘플이다.
// (Maze, MapSite, Room, Wall, Door의 Object들로 구성되어 있다.)
// This project is GoF Design Pattern of Creational Pattern Sample


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
// Room class
class Room : public MapSite
{
public:
	Room(int nRoomNo)
	{
		m_nRoomNo = nRoomNo;

		for (int i = 0; i < dirMax; i++)
		{
			m_lpMapSite[i] = new Wall;
			if (NULL == m_lpMapSite[i])
				exception("Failed Room Object Create");
		}
	}

	MapSite*	GetSite(Direction direct) { return m_lpMapSite[direct]; }
	void	SetSite(Direction direct, MapSite* lpMapSite) { m_lpMapSite[direct] = lpMapSite; }

	virtual void Enter(void) { cout << "Is Room " << m_nRoomNo << endl; }

protected:
	MapSite*	m_lpMapSite[dirMax];
	int		m_nRoomNo;
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
// MazeGame class
class MazeGate : public Maze
{
public:
	Maze*	CreateMaze(void)
	{
		Maze* lpActiveMaze = new Maze;
		if (NULL == lpActiveMaze)
			return NULL;
		Room* lpRoom1 = new Room(1);
		if (NULL == lpRoom1)
			return NULL;
		Room* lpRoom2 = new Room(2);
		if (NULL == lpRoom2)
			return NULL;
		Door* lpDoor = new Door(lpRoom1, lpRoom2);
		if (NULL == lpDoor)
			return NULL;

		lpActiveMaze->AddRoom(lpRoom1);
		lpActiveMaze->AddRoom(lpRoom2);

		lpRoom1->SetSite(dirEast, lpDoor);
		lpRoom2->SetSite(dirWest, lpDoor);

#if ROOM_NOT_CREATE_WALL	// Room class에서 contructor에서 Wall를 기본으로 생성함.
		lpRoom1->SetSite(dirNorth, new Wall);
		lpRoom1->SetSite(dirEast, lpDoor);
		lpRoom1->SetSite(dirSouth, new Wall);
		lpRoom1->SetSite(dirWest, new Wall);

		lpRoom2->SetSite(dirNorth, new Wall);
		lpRoom2->SetSite(dirEast, new Wall);
		lpRoom2->SetSite(dirSouth, new Wall);
		lpRoom2->SetSite(dirWest, lpDoor);
#endif // ROOM_NOT_CREATE_WALL
		return lpActiveMaze;
	}
};