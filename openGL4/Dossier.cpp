#include "Dossier.h"
using namespace std;
#define WORLDFILE "world.txt"
Dossier::Dossier()
{
}
void Dossier::setupWorld()
{
	ifstream infile;
	int numberOfTriangle;
	infile.open(WORLDFILE);
	//read data


	//read number of triangle
	infile >> numberOfTriangle;

	infile.close();
	return;
}

Dossier::~Dossier()
{
}
