#ifndef SETDATA_H
#define SETDATA_H
#include <iostream>

enum bodyPart
{
	thorax,
	hand,
	foot,
	spine,
	knee,
};
struct patientData
{
	std::string name;
	std::string birthDate;
	double      weight;
	int         id;
};

#endif /* SETDATA_H */