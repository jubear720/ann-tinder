#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <list>
#include "../inc/CSVHeader.h"

using namespace std;

records *readCSV(string filename, int predictYear, int prevYears);
void split_line(string& line, string delim, list<string>& values);
void normalize(records *data);



records *readCSV(string filename, int predictYear, int prevYears)
{
	 ifstream file ( "../csv/"+filename ); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
    string value; 
    list<string> values;

	//Skip first two lines
	getline ( file, value );
	getline ( file, value );
	
	int j = 0;
    while ( file.good() )
    {
		
        getline ( file, value, ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
			
			if (value.find('\n') != string::npos) 
			{
			    split_line(value, "\n", values);
			} 
			else
			{
			    values.push_back(value);
			}
    }

	int indexX = 0;
 
	list<string>::const_iterator it = values.begin();
    records *data = new records;
 	records *temp = data;
	records *prev = temp;
	
	for(indexX = 0; predictYear > strtod(values.front().c_str(), NULL) && !values.empty(); indexX++)
	{
		if(predictYear-(strtod(values.front().c_str(), NULL)) <= prevYears)
		{
			temp->dates = strtod(values.front().c_str(), NULL);
			values.pop_front();
			temp->burnedAcres = strtod(values.front().c_str(), NULL);
			values.pop_front();
				
			for(int indexY = 0; indexY < 12; indexY++)
			{
				temp->months[indexY] = strtod(values.front().c_str(), NULL);
				values.pop_front();
			}
			prev = temp;
			temp->next = new records;
			temp = temp->next;	
		}
		else
		{
			for(int indexZ = 0; indexZ < 14; indexZ++)
				values.pop_front();
		}
	}
	prev->next = NULL;
	
	normalize(data);

	file.close();
	//delete data;
	return data;
}

void split_line(string& line, string delim, list<string>& values)
{
    size_t pos = 0;
    while ((pos = line.find(delim, (pos + 1))) != string::npos) {
        string p = line.substr(0, pos);
        values.push_back(p);
        line = line.substr(pos + 1);
    }

    if (!line.empty()) {
        values.push_back(line);
    }
}

void normalize(records *data)
{
	records *temp = data;
	double minBurnedAcres = temp->burnedAcres;
	double minMonths = temp->months[0];
	double maxBurnedAcres = temp->burnedAcres;
	double maxMonths = temp->months[0];

	while(temp != NULL)
	{
		if(minBurnedAcres > temp->burnedAcres)
			minBurnedAcres = temp->burnedAcres;
		if(maxBurnedAcres < temp->burnedAcres)
			maxBurnedAcres = temp->burnedAcres;

		for(int indexX = 0; indexX < 12; indexX++)
		{
			if(minMonths > temp->months[indexX])
				minMonths = temp->months[indexX];
			if(maxMonths < temp->months[indexX])
				maxMonths = temp->months[indexX];
		}
		temp=temp->next;
	}
	temp = data;

	while(temp != NULL)
	{
		temp->burnedAcres=(temp->burnedAcres-minBurnedAcres)/(maxBurnedAcres-minBurnedAcres);

		for(int indexX = 0; indexX < 12; indexX++)
		{
			temp->months[indexX]=(temp->months[indexX]-minMonths)/(maxMonths-minMonths);
		}
		temp=temp->next;
	}
	

}