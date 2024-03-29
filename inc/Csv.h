/*************************************************************************//**
 * @file Csv.h
 *
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 *
 * @brief HEADER - Methods for reading in Csv File information
 *
 *****************************************************************************/

#ifndef _CSV_H_
#define _CSV_H_

/******************************************************************************
 *
 * INCLUDE
 *
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <list>

/******************************************************************************
 *
 * STRUCTS
 *
 ******************************************************************************/

/**************************************************************************//**
 * @brief Data structure for csv information.
 *
 * <DESCRIPTION GOES HERE>
 *
 *****************************************************************************/

struct records
{
    double dates;
    double iAcres;
    double burnedAcres;
    double months[12];
    records *next;
};

/******************************************************************************
 *
 * PROTOTYPES
 *
 ******************************************************************************/

int getRecordsSize( records *data );
records *readCSV(std::string filename, records *data);
records *readCSVEntry( std::string filename, int predictYear, int prevYears, records *data );
void freeRecords(records *data);
void split_line( std::string& line, std::string delim, std::list<std::string>& values );
void normalize( records *data );

#endif
