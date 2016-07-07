
#pragma once

//
// 이 프로젝트는 GoF Design Patterns의 Builder Pattern 샘플이다.
// (Maze, MapSite, Room, Wall, Door의 Object들로 구성되어 있다.)
// This project is GoF Design Pattern of Builder Pattern Sample


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
	Room(int nRoomNo) { m_nRoomNo = nRoomNo; }

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
// Maze Builder class
class MazeBuilder
{
protected:
	MazeBuilder(void) { };

public:
	virtual void	BuilderMaze(void) { }
	virtual void	BuilderRoom(int nRoomNum) { }
	virtual void	BuilderDoor(int nRoomFrom, int nRoomTo) { }
	virtual Maze*	GetMaze(void) { return NULL; }
};


//
// Standard Maze Builder class
class StandardMazeBuilder : public MazeBuilder
{
public:
	StandardMazeBuilder(void) { m_CurrentMaze = NULL; }

	virtual void	BuilderMaze(void) { m_CurrentMaze = new Maze; }
	virtual void	BuilderRoom(int nRoomNum)
	{
		Room* lpRoom = new Room(nRoomNum);
		m_CurrentMaze->AddRoom(lpRoom);

		lpRoom->SetSite(dirNorth, new Wall);
		lpRoom->SetSite(dirEast, new Wall);
		lpRoom->SetSite(dirSouth, new Wall);
		lpRoom->SetSite(dirWest, new Wall);
	}
	virtual void	BuilderDoor(int nRoomFrom, int nRoomTo)
	{
		Room* lpRoomFront = m_CurrentMaze->RoomNo(0);
		Room* lpRoomBack = m_CurrentMaze->RoomNo(1);
		Door* lpDoor = new Door(lpRoomFront, lpRoomBack);

		lpRoomFront->SetSite(CommonWall(lpRoomFront, lpRoomBack), lpDoor);
		lpRoomBack->SetSite(CommonWall(lpRoomBack, lpRoomFront), lpDoor);
	}
	virtual Maze*	GetMaze(void) { return m_CurrentMaze; }

protected:
	Direction	CommonWall(Room* lpRoomFrom, Room* lpRoomTo)
	{
		Direction direction = dirMax;
		direction = (Direction)(::rand() % dirMax);

		return direction;
	}
	Maze*	m_CurrentMaze;
};


//
// Counting Maze Builder class
class CountingMazeBuilder : public MazeBuilder
{
public:
	CountingMazeBuilder(void) { m_nDoors = m_nRooms = 0; }

	virtual void	BuilderMaze(void) { }
	virtual void	BuilderRoom(int nRoomNum) { m_nRooms++; }
	virtual void	BuilderDoor(int nRoomFrom, int nRoomTo) { m_nDoors++; }
	virtual void	AddWall(int, Direction) { };
	virtual void	GetCounts(int& nRooms, int& nDoors) const { nRooms = m_nRooms; nDoors = m_nDoors; }

protected:
	int		m_nRooms;
	int		m_nDoors;
};

//
// MazeGame class
class MazeGate : public Maze
{
public:
	Maze*	CreateMaze(MazeBuilder& Builder)
	{
		Builder.BuilderMaze();
		Builder.BuilderRoom(1);
		Builder.BuilderRoom(2);
		Builder.BuilderDoor(0, 1);

		return Builder.GetMaze();
	}

	Maze*	CreateComplexMaze(MazeBuilder& Builder)
	{
		Builder.BuilderMaze();
		Builder.BuilderRoom(1);
		Builder.BuilderRoom(2);
		Builder.BuilderDoor(0, 1);

		return Builder.GetMaze();
	}
};