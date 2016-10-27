#include "Tile.h"

Tile::Tile()
{
	adjacentMines_ = 0;
	revealed_ = false;
	marked_ = false;
	detonated_ = false;
	type_ = GROUND;
	cover_ = 0;
	checked_ = false;
}

Tile::Tile(Type type)
{
	adjacentMines_=0;
	revealed_=false;
	marked_=false;
	detonated_=false;
	type_=type;
	cover_=rand()%3;
	checked_=false;
}

Tile::Tile(Type type, bool revealed, bool marked, int cover)
{
	adjacentMines_=0;
	revealed_=revealed;
	marked_=marked;
	detonated_=false;
	type_=type;
	cover_=cover;
	checked_=false;
}

Tile::Tile(const Tile &other)
{
	adjacentMines_=other.adjacentMines_;
	revealed_=other.revealed_;
	marked_=other.marked_;
	detonated_=other.detonated_;
	type_=other.type_;
	cover_=other.cover_;
	checked_=other.checked_;
}

Tile::~Tile()
{
	adjacentMines_=0;
	revealed_=false;
	marked_=false;
	detonated_=false;
	type_=GROUND;
	cover_=0;
	checked_=false;
}

void Tile::removeMine()
{
	type_ = GROUND;
}

void Tile::placeMine()
{
	type_ = MINE;
}

void Tile::setType(Type t)
{
	type_ = t;
}

Tile::Type Tile::getType()
{
	return type_;
}

int Tile::getTile()
{
	return type_;
}

int Tile::getAdjacentMines()
{
	return adjacentMines_;
}

void Tile::reveal()
{
	revealed_=true;
}

void Tile::setRevealed(bool r)
{
	revealed_=r;
}

bool Tile::getRevealed()
{
	return revealed_;
}

void Tile::setMarked(bool m)
{
	marked_=m;
}

bool Tile::getMarked()
{
	return marked_;
}

void Tile::mark()
{
	marked_ = true;
}

Tile& Tile::operator++()
{
	adjacentMines_++;
	return *this;
}

Tile Tile::operator++(int i)
{
	Tile temp(*this);
	operator++();
	return temp;
}

Tile& Tile::operator--()
{
	adjacentMines_--;
	return *this;
}

Tile Tile::operator--(int i)
{
	Tile temp(*this);
	operator--();
	return temp;
}

Tile * Tile::operator=(const Tile &rhs) const
{
	return new Tile(rhs);
}

ostream& operator<<(ostream &os, const Tile &rhs)
{
	if(rhs.type_ == Tile::MINE)
	{
		os << "[x]";
	} 
	else 
	{
		os << "[" << rhs.adjacentMines_ << "]";
	}

	return os;
}

int Tile::getCover()
{
	return cover_;
}

bool Tile::checked()
{
	return checked_;
}

void Tile::check()
{
	checked_ = true;
}

void Tile::detonate()
{
	detonated_ = true;
}

void Tile::setDetonated(bool b)
{
	detonated_=b;
}

bool Tile::detonated()
{
	return detonated_;
}

string Tile::adjacentMines()
{
	stringstream temp;
	temp << adjacentMines_;
	return temp.str();
}

void Tile::print(ostream &os)
{
	os << type_ << endl;
	os << adjacentMines_ << endl;
}
