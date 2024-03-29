/*************************************************************************//**
 * @file Prm.h
 *
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 * @brief HEADER - Class for reading and writing Prm (Parameter) Files.
 *
 *****************************************************************************/

#ifndef _PRM_H_
#define _PRM_H_

/******************************************************************************
 *
 * INCLUDE
 *
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

/*************************************************************************//**
* @class Prm
*
* @author Julian Brackins
*
* @brief Prm (Parameter file) class.
*
*****************************************************************************/
class Prm
{
public:
    // CONSTRUCTORS
    Prm(  );
    Prm( std::string filename );

    // DESTRUCTOR
    ~Prm();

    //READ and WRITE to/from the .prm file
    int readPrm( );
    int writePrm();

    //Verify that the prm file was successfully read in.
    bool valid();

    //GETTERS - Get the values of each variable
    std::string getFilename( bool path = true );
    std::string getWtsFile( bool path = true );
    int getEpochs();
    double getLearningRate();
    double getMomentum();
    double getThreshold();
    int getLayers();
    int getNodeCount( int index );
    std::string getCsvFile( bool path = true );
    int getYears();
    int getMonths();
    int getEndMonth();
    int getNumClasses();
    int getLowMed();
    int getMedHigh();

    //SETTERS - Set the values of each variable. Note that
    //All non-string parameters have two different setters,
    //One for ubiquitous std::string types read in from file,
    //Another for the specific data type input
    //File name setter
    int setFilename( std::string input );
    //Weights file setter
    int setWtsFile( std::string input );
    //Epochs Setter
    int setEpochs( std::string input );
    int setEpochs( int input );
    //Learning Rate Setters
    int setLearningRate( std::string input );
    int setLearningRate( double input );
    //Momentum Setters
    int setMomentum( std::string input );
    int setMomentum( double input );
    //Threshold Setters
    int setThreshold( std::string input );
    int setThreshold( double input );
    //Layers Setters
    int setLayers( std::string input );
    int setLayers( int input );
    //NodeCount Setter and 'Pusher'
    int setNodeCount( std::string input );
    int addNodeCount( int input );
    //CSV file setter
    int setCsvFile( std::string input );
    //Years Setters
    int setYears( std::string input );
    int setYears( int input );
    //Months Setters
    int setMonths( std::string input );
    int setMonths( int input );
    //End Month Setters
    int setEndMonth( std::string input );
    int setEndMonth( int input );
    //Number of Classes Seters
    int setNumClasses( std::string input );
    int setNumClasses( int input );
    //Low-Medium Setters
    int setLowMed( std::string input );
    int setLowMed( int input );
    //Medium-High Setters
    int setMedHigh( std::string input );
    int setMedHigh( int input );

    //WRITERS - Write the values of each variable to a file
    int writeFilename( );
    int writeWtsFile( );
    int writeEpochs(  );
    int writeLearningRate(  );
    int writeMomentum(  );
    int writeThreshold(  );
    int writeLayers(  );
    int writeAllNodes();
    int writeNodeCount( int index );
    int writeCsvFile(  );
    int writeYears(  );
    int writeMonths(  );
    int writeEndMonth(  );
    int writeNumClasses(  );
    int writeLowMed(  );
    int writeMedHigh(  );

    //PRINTERS - Print the values of each variable to stdout
    void printFilename();
    void printWtsFile();
    void printEpochs();
    void printLearningRate();
    void printMomentum();
    void printThreshold();
    void printLayers();
    void printAllNodes();
    void printNodeCount( int index );
    void printCsvFile();
    void printYears();
    void printMonths();
    void printEndMonth();
    void printNumClasses();
    void printLowMed();
    void printMedHigh();
    //print the whole damn lot
    void printPrm();
    //print errors
    void printErrorCode( int err );

    //STRIPPERS - Not that kind ;) .... Removes random junk
    std::string stripComment( std::string input );
    std::string stripSpaces( std::string input );

private:
    //.prm filename
    std::string      pFilename;

    //ANN Parameters
    std::string      pWts_file;       // name of ANN weight file
    int              pEpochs;         // number of training epochs
    double           pLearning_rate;  // learning rate
    double           pMomentum;       // momentum
    double           pThreshold;      // threshold for ANN error
    int              pLayers;         // layers of adjustable weights
    std::vector<int> pNode_count;     // how many nodes in each layer

    //Training and Testing Data file
    std::string      pCsv_file;       // training and testing data file name

    //Feature vector info:
    int              pYears;          // years of burned acreage,
    int              pMonths;         // months of PDSI data
    int              pEnd_month;      // end month of current year

    //Output class info
    int              pNum_classes;

    //Fire severity parameter
    int              pLow_med;        // Corresponds to low/medium/high cutoffs
    int              pMed_high;

    bool             pValid;          //Corresponds to if the prm file was read successfully
    FILE             * file_pointer;  //File Pointer
};

#endif
