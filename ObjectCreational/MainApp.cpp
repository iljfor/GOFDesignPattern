
#include "MainApp.h"


int main()
{
	
	MazeGate* lpMazeGate = new MazeGate;
	if (NULL == lpMazeGate)
		return 0;

	Maze* lpMaze = lpMazeGate->CreateMaze();
	if (NULL == lpMaze)
		return 0;

	Room* lpRoom1 = lpMaze->RoomNo(0);
	lpRoom1->Enter();

	cout << "North ";
	MapSite* lpMap = lpRoom1->GetSite(dirNorth);
	if (NULL != lpMap)
		lpMap->Enter();

	cout << "South ";
	lpMap = lpRoom1->GetSite(dirSouth);
	if (NULL != lpMap)
		lpMap->Enter();

	cout << "East ";
	lpMap = lpRoom1->GetSite(dirEast);
	if (NULL != lpMap)
		lpMap->Enter();

	cout << "West ";
	lpMap = lpRoom1->GetSite(dirWest);
	if (NULL != lpMap)
		lpMap->Enter();

	Room* lpRoom2 = lpMaze->RoomNo(1);
	lpRoom2->Enter();

	cout << "North ";
	lpMap = lpRoom1->GetSite(dirNorth);
	if (NULL != lpMap)
		lpMap->Enter();

	cout << "South ";
	lpMap = lpRoom2->GetSite(dirSouth);
	if (NULL != lpMap)
		lpMap->Enter();

	cout << "East ";
	lpMap = lpRoom2->GetSite(dirEast);
	if (NULL != lpMap)
		lpMap->Enter();

	cout << "West ";
	lpMap = lpRoom2->GetSite(dirWest);
	if (NULL != lpMap)
		lpMap->Enter();

	int i;
	cin >> i;

	return 0;
}