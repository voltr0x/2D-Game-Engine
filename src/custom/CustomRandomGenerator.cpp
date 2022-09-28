#include "CustomRandomGenerator.hpp"
#include <set>
#include <chrono>
#include <algorithm>
#include <queue>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <set>
#include <map>
#include <random>

struct Location
{
    int x;
    int y;
    int columns;
    int setId;
    std::set<Location*> connectedLoc;
    char locType;
    bool visited;
};

int edgeCount = 0;

struct Edge
{
    Location* first;
    Location* second;
    int edgeId;

    Edge(Location* firstP, Location* secondP) 
    {
        first = firstP;
        second = secondP;
        edgeId = edgeCount;
        edgeCount++;
    }


    bool operator<(const Edge& a) const
    {
        return this->edgeId < a.edgeId;
    }
};

void MergeSet(std::vector<std::vector<Location*>>& buckets, int fromId, int ToId)
{
    if (fromId == ToId)
    {
        return;
    }

    // Set new bucket id for each melding cell
    for (auto it = buckets[fromId].begin(); it != buckets[fromId].end(); ++it)
    {
        (*it)->setId = ToId;
        buckets[ToId].push_back(*it);
    }

    buckets[fromId].clear();
}


void generateRandomLevel(std::vector<std::vector<Location>>& maze, int rows, int columns, uint64_t seed)
{
    std::mt19937 mt(seed); 

    maze.clear();
    maze.resize(columns);
    for (std::vector<Location>& row : maze)
    {
        row.resize(rows);
    }

    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++) 
        {
            maze[i][j].x = i;
            maze[i][j].y = j;
            maze[i][j].locType = 'X';
        }
    }

    std::set<Edge> edges;                             
    std::vector<std::vector<Location*>> bucketCells; 

    uint64_t nodeId = 0;
    bucketCells.resize(rows * columns); 
    int edgeCount = 0;
    for (int x = 0; x < columns; ++x)
    {
        for (int y = 0; y < rows; ++y)
        {

            if (x % 2 == 1 && y % 2 == 1) 
            {
                ++nodeId;
                maze[x][y].setId = nodeId;
                bucketCells[nodeId].push_back(&maze[x][y]);

                // Insert Right edge
                if (x + 2 < columns)
                {
                    Location* one = &maze[x][y];
                    Location* two = &maze[x + 2][y];
                    Edge e(one, two);
                    edges.insert(e);
                    edgeCount++;
                }
                // Insert Bottom edge
                if (y + 2 < rows)
                {
                    Location* one = &maze[x][y];
                    Location* two = &maze[x][y + 2];
                    Edge e(one, two);
                    edges.insert(e);
                    edgeCount++;
                }
            }

            
        }
    }

    // While the set of edges is not empty randomly get an edge (connecting two cells):"
    while (!edges.empty())
    {
        auto edgeIt = edges.begin();
        auto move = mt() % edges.size();
        std::advance(edgeIt, move);
        int firstBucket = edgeIt->first->setId;
        int secondBucket = edgeIt->second->setId;

        // Add connection and merge buckets if not already in the same one
        if (firstBucket != secondBucket)
        {
            // maze->Connect(edgeIt->first, edgeIt->second);

            Location* firstLoc = &maze[edgeIt->first->x][edgeIt->first->y];
            Location* secondLoc = &maze[edgeIt->second->x][edgeIt->second->y];

            firstLoc->connectedLoc.insert(secondLoc);
            secondLoc->connectedLoc.insert(firstLoc);

            MergeSet(bucketCells, firstBucket, secondBucket);
        }

        // Remove computed cell from the set
        edges.erase(edgeIt);
    }

    for (int i = 0; i <  (int) maze.size(); ++i)
    {
        for (int j = 0; j < (int) maze[i].size(); ++j)
        {
            if (i % 2 == 1 && j % 2 == 1)
            {
                Location* currentLoc = &maze[i][j];
                currentLoc->locType = '.';
                for (auto& connectedLoc : currentLoc->connectedLoc)
                {
                    Location* intermediate = nullptr;
                    if (currentLoc->x != connectedLoc->x)
                    {
                        int newX = std::max(currentLoc->x, connectedLoc->x);
                        newX = newX - 1;

                        intermediate = &maze[newX][j];
                    }
                    else if (currentLoc->y != connectedLoc->y)
                    {
                        int newY = std::max(currentLoc->y, connectedLoc->y);
                        newY = newY - 1;
                        intermediate = &maze[i][newY];
                    }

                    if (intermediate) 
                    {
                        intermediate->locType = '.';
                        intermediate->connectedLoc.insert(currentLoc);
                        intermediate->connectedLoc.insert(connectedLoc);

                        currentLoc->connectedLoc.insert(intermediate);
                        connectedLoc->connectedLoc.insert(intermediate);
                    }
                }
            }
        }

    }
}

std::pair<int, int> pickRandomOpenPoint(std::vector<std::vector<Location>>& maze, uint64_t seed) {

    bool choosing = true;
    std::mt19937 mt(seed);

    int xBound = maze.size();
    int yBound = maze[0].size();

    int x, y;
    while (choosing)
    {
        x = mt() % xBound;
        y = mt() % yBound;

        // Check if the point is open
        if (maze[x][y].locType == '.')
        {
            choosing = false;
        }

    }

    return { x, y };
}

void BFS_Path(std::pair<int, int>  startPoint, std::pair<int, int> endPoint, 
    std::vector<std::vector<Location>>& maze, std::vector<Location*>& traversalOrder)
{
    for (auto& r : maze) 
    {
        for (auto& c : r) 
        {
            c.visited = false;
        }
    }

    std::queue<Location*> queue;

    Location* startingLocation = &maze[startPoint.first][startPoint.second];
    startingLocation->visited = true;
    queue.push(startingLocation);

    while (!queue.empty())
    {
        Location* nextLoc = queue.front();
        queue.pop();
        for (Location* neighbor : nextLoc->connectedLoc) 
        {
            if (!neighbor->visited) 
            {
                neighbor->visited = true;
                queue.push(neighbor);

                if (neighbor->x == endPoint.first && neighbor->y == endPoint.second) 
                {
                    return;
                }
                else 
                {
                    traversalOrder.push_back(neighbor);
                }
            }
        }
    }
}

void addRandomBoundOfEntity(int randomBound, char entity, std::vector<std::vector<Location>>& maze, uint64_t seed) {
    std::mt19937 mt(seed);
    int count = mt() % randomBound;
    if (count == 0) count++;

    for (int i = 0; i < count; i++)
    {
        std::pair<int, int> nextPoint = pickRandomOpenPoint(maze, seed);
        maze[nextPoint.first][nextPoint.second].locType = entity;
    }
}

void decorateMaze(std::vector<std::vector<Location>>& maze, uint64_t seed)
{
    std::mt19937 mt(seed);
    std::pair<int, int> playerStart = pickRandomOpenPoint(maze, seed);

    maze[playerStart.first][playerStart.second].locType = 'P';

    std::pair<int, int> goalPoint = pickRandomOpenPoint(maze, seed);
    maze[goalPoint.first][goalPoint.second].locType = 'G';

    std::vector<Location*> pathToGoal;
    BFS_Path(playerStart, goalPoint, maze, pathToGoal);
    
    int halfPathLength = pathToGoal.size() / 2;
    int keyPoint = mt() % halfPathLength;
    Location* keyLoc = pathToGoal.at(keyPoint);
    keyLoc->locType = 'K';

    int doorPoint = mt() % halfPathLength;
    doorPoint += halfPathLength;
    Location* doorLoc = pathToGoal.at(doorPoint);
    doorLoc->locType = 'D';

    addRandomBoundOfEntity(3, 'E', maze, seed);
    addRandomBoundOfEntity(4, 'C', maze, seed);
    addRandomBoundOfEntity(5, 'H', maze, seed);
}

std::vector<std::vector<std::string>> CustomRandomLevelGenerator::generateLevel(int rows, int cols, uint64_t seed)
{
    std::vector<std::vector<Location>> maze;
    generateRandomLevel(maze, rows, cols, seed);
    decorateMaze(maze, seed);

    std::vector<std::vector<std::string>> stringRep;

    for(auto& row : maze)
    {
        std::vector<std::string> line;
        for(auto& loc : row)
        {
            std::string block(1, loc.locType);
            line.push_back(block);
        }
        stringRep.push_back(line);
    }

    return stringRep;
}
