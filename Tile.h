#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include <ostream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>

using std::ostream;
using std::cout;
using std::endl;
using std::rand;
using std::string;
using std::stringstream;


class Tile
{
public:
	enum Type{ MINE, GROUND, BORDER };

	/*
	 * Default Tile constructor
	 * Sets type to Tile::GROUND
	 * Sets adjacentMines to 0, revealed to false, and marked to false
	 */
	Tile();

	/*
	 * Tile constructor
	 * Takes a Tile::Type
	 * Tets the type to passed value
	 * Sets adjacenetMines to 0, revealed to false, and marked to false
	 */
	Tile(Type t);

	/*
	 * Tile constructor
	 * Takes a Tile::Type, bool for revealed, bool for marked
	 * Sets adjacenetMines to 0, and the other values to passed values
	 */
	Tile(Type t, bool revealed, bool marked, int cover);

	/*
	 * Tile copy constructor
	 */
	Tile(const Tile &other);

	/*
	 * Tile destructor
	 * sets tile to default values
	 */
	~Tile();

	/*
	 * RemoveMine function
	 * Sets type to Tile::GROUND
	 */
	void removeMine();

	/*
	 * PlaceMine function
	 * Sets type to Tile::MINE
	 */
	void placeMine();

	/*
	 * SetType function
	 * Sets type to passed Type
	 * Must pass Tile::Type
	 * Valid Types are Tile::GROUND, Tile::MINE, Tile::BORDER
	 */
	void setType(Type t);

	/*
	 * GetType function
	 * Returns Tile::Type
	 */
	Type getType();

	/*
	 * GetAdjacentMines function
	 * Returns int adjacentMines
	 */
	int getAdjacentMines();

	/*
	 * Reveal function
	 * Sets revealed to true
	 */
	void reveal();

	/*
	 * SetRevealed function
	 * Sets revealed to the passed boolean
	 */
	void setRevealed(bool r);

	/*
	 * GetRevealed function
	 * Returns boolean revealed
	 */
	bool getRevealed();

	/*
	 * SetMarked function
	 * Sets marked to the passed boolean
	 */
	void setMarked(bool m);

	/*
	 * GetMarked functioin
	 * Returns bool marked
	 */
	bool getMarked();

	/*
	 * Mark function
	 * Sets marked to true
	 */
	void mark();

	/*
	 * Pre-increment operator
	 * Incremenets the adjacentMines value of the Tile
	 */
	Tile& operator++();

	/*
	 * Post-increment operator
	 * Increments the adjacenentMines value of the Tile
	 */
	Tile operator++(int i);

	/*
	 * Pre-decrement operator
	 * Decrements the adjacentMines value of the Tile
	 */
	Tile& operator--();

	/* 
	 * Post-decrement operator
	 * Decrements the adjacentMines value of the Tile
	 */
	Tile operator--(int i);

	/*
	 * Assignment opreator
	 * Returns a copy of the right hand side value
	 * Calls the copy constructor
	 */
	Tile * operator=(const Tile &rhs) const;

	/*
	 * Insertion operator
	 * Prints out a Tile representation
	 * Defaults to cout
	 * Prints "[x]" for Mined Tiles
	 * Prints "[n]" for all other Tiles, where 'n' is the adjacentMines value
	 */
	friend ostream& operator<<(ostream &os, const Tile &rhs);

	/*
	 * GetCover function
	 * Returns int
	 * Cover var is randomized when map is seeded
	 * Allows different types of grass/shrubs
	 */
	int getCover();

	/*
	 * Checked function
	 * Returns bool
	 * Tracks tiles that have been checked
	 * For recursive tile clearing
	 */
	bool checked();

	/*
	 * Check function
	 * Sets check bool to true
	 */
	void check();

	/*
	 * Detonate function
	 * Sets detonated bool to true
	 */
	void detonate();

	/*
	 * SetDetonated function
	 * Takes a bool
	 * Sets detonated to the passed value
	 */
	void setDetonated(bool b);

	/*
	 * Detonated function
	 * Returns bool 
	 * Informs of detonated status
	 * Used for map displaying, to show a crater or not
	 */
	bool detonated();
	
	/*
	 * Print function
	 * Default to cout
	 */
	void print(ostream &os = cout);

	/*
	 * AdjacentMines function
	 * Returns a string with the number of adjacenet mines
	 */
	string adjacentMines();

	/*
	 * GetTile function
	 * Returns an int 
	 */
	int getTile();

private:
	int adjacentMines_;
	Type type_;
	bool revealed_;
	bool marked_;
	bool detonated_;
	int cover_;
	bool checked_;
	
};


#endif