/*************************************************************************//**
 * @file ANNtrain.cpp
 *
 * @brief SOURCE - Artificial Neural Network - ANNtrain Tester program file.
 *
 * @mainpage Program 1 - TINDER
 *
 * @section course_section CSC 447/547
 *
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 * @date January 29, 2016
 *
 * @par Professor:
 *         Dr. John Weiss
 *
 * @par Course:
 *         CSC 447/546 - 9:00am
 *
 * @par Location:
 *         McLaury - 313
 *
 * @section program_section Program Information
 *
 * @details
 * Program Info
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      (Linux) - make
 *
 * @par Usage:
 @verbatim
 ./ANNtrain <parameterfile>
 @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 *
 ******************************************************************************/

/******************************************************************************
 *
 * INCLUDE
 *
 ******************************************************************************/

#include "../inc/ANNtrain.h"

/******************************************************************************
 *
 * NAMESPACES
 *
 ******************************************************************************/

using namespace std;

/******************************************************************************
 *
 * GLOBALS
 *
 ******************************************************************************/

/**************************************************************************//**
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 * @par Description:
 * This is the starting point to the program.
 *
 * @param[in] argc - the number of arguments from the command prompt.
 * @param[in] argv - a 2d array of characters containing the arguments.
 *
 * @returns 0 - Program Ends Gracefully.
 * @returns -1 - Program Ends because YOU GOOFED UP
 *
 *
 *****************************************************************************/
int main(int argc, char ** argv)
{
    int num_samples = 0;
    int epoch = 0;
    double error_sum = 0;
    double rms = 1.0;
    int num_records;
    int start;
    vector<bool> start_here;
    int years;
    double weights [ 10001 ] = { 0.0 }; //set weight not in weight range
    bool acceptableRMS = false;


    if ( argc != 2 )
    {
        usage( argv );
        return -1;
    }


    srand ( time( 0 ) );
    // open the Neural Net with the given parameter file

    NeuralNet ANN = NeuralNet(argv[1]); // need this
    ANN.connect_layers ( ); // need this

    //open and read the specified records
    records *head_record = new records; // need this

    readCSV( ANN.ANN_params.getCsvFile( ), head_record ); // need this
    records *temp = head_record; // need this
    num_records = getRecordsSize( temp ); // need this
    // input_nodes = ANN.get_layer_nodes ( 0 );

    years = floor (ANN.ANN_params.getMonths ( ) / 12.0 ); // need this
    for (int i = 0; i < num_records - years; i++)
    {
        start_here.push_back(false);
    }

    // open and set weights values (if present)
    // make sure we can read weights file from another cpp
    // check if file exists
    if (!readWeights (ANN.ANN_params.getWtsFile ( ), weights,
                      ANN.getNetSize( ))) // have this
    {
        ANN.set_weights ( weights ); // change to warning
    }

    while ( epoch < ANN.ANN_params.getEpochs ( ) && !acceptableRMS )
    {
        temp = head_record;// need this

        start = getStart ( start_here, ANN.ANN_params.getMonths ( ), num_records );

        start_here [ start ] = true;

        for (int i = 0; i < start; i++ )
            temp = temp->next;

        // set the csv file input to the neural net input layer
        ANN.set_first_layer ( temp ); // need this

        for (int i = 0; i < years; i++ )
            temp = temp->next;
        ANN.set_desired_output ( temp );

        // we want to update the desired output of the ANN here
        // should add to neural net get output for output nodes
        ANN.update_output ( ); // need this
        ANN.update_grads ( ); // update error gradiants
        ANN.update_weights ( ); // update the weights for the neural net

        // calculate the error every year based on the sum of the input expect vs input actual
        error_sum += ANN.get_error ( );

        // sum all error of the inputs together
        num_samples++; // get number of samples used

        if (isTrue(start_here, num_records - years) )
        {
            epoch++;
            for (int i = 0; i < num_records - years; i++)
            {
                start_here[i] = false;
            }

            rms = (1.0 / num_samples) * error_sum;
            rms = sqrt(rms);

            if (epoch % 10 == 0)
                printTraining ( epoch, "RMS", rms );
            num_samples = 0;
            error_sum = 0.0;
            if ( rms <= ANN.ANN_params.getThreshold ( ) )
              acceptableRMS = true;
        }
    }
    // print the Training for the epoch and repeat for every year in the csv file
    ANN.get_weights ( weights, 10000 );
    setWeights(ANN.ANN_params.getWtsFile ( ), weights, ANN.getNetSize( ));

    // after we have all the training done, write the weights file
    // add a get weights function
    //ANN.get_weights ( weights, 10000 );
    //setWeights(ANN.get_weights_file ( ), weights, ANN.getNetSize( ));
    // write weights to file

    freeRecords( head_record );
    //delete head_record;
    //head_record=NULL;

    //printInfo( p );
    return 0;
}


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Print out a training iteration.
 *
 * @param[in] epoch     - Epoch of a given training iteration
 * @param[in] equation  - error equation used for training
 * @param[in] error     - error value
 *
 * @returns nothing
 *
 *****************************************************************************/
void printTraining( int epoch, string equation, double error )
{

    ///Print out a single iteration of the training execution. For each epoch,
    ///The error value is out displayed. A successful neural network should have
    ///a decreasing error value with each iteration.
    cout << "Epoch" << setw(7) << epoch;
    cout << ": " << equation << " error = ";
    cout << setiosflags(ios::fixed) << setprecision(3)  << error << endl;

}


/**************************************************************************//**
 * @author Julian Brackins
 *
 * @par Description:
 * Test the output of our program
 *
 * @returns nothing
 *
 *****************************************************************************/
void testPrintout( )
{
    int e;
    string eq = "RMS";
    double err;

    srand (time(NULL));


    for ( e = 0; e < 1000; e += 10 )
    {
        err = (double)rand() / RAND_MAX;
        err = err * (1.00 - 0.00);
        printTraining( e, eq, err );
    }
}


/**************************************************************************//**
 * @author Samuel Carroll
 *
 * @par Description:
 * tests if a vector of booleans is set to all true
 *
 * @param vector<bool> start_here - vector we are checking
 * @param int vec_size - size of the vector
 *
 * @returns true  -
 * @returns false -
 *
 *****************************************************************************/
bool isTrue ( vector <bool> start_here, int vec_size )
{
    for (int i = 0; i < vec_size; i++)
    {
        if ( !start_here[i] )
            return false;
    }

    return true;
}


/**************************************************************************//**
 * @author Samuel Carroll
 *
 * @par Description:
 * This function will determine a viable starting location for the Neural Net
 *
 * @param vector<bool> start_here - vector with start points used in training
 * @param int months - number of months used as input
 * @param int num_recs - number of years in our dataset
 *
 * @returns start position
 *
 *****************************************************************************/
int getStart ( vector <bool> start_here, int months, int num_recs )
{
    double divideFloat = months / 12.0;
    int years = floor ( divideFloat );
    int start = (rand ( ) % (num_recs - years));

    while (start_here[start])
        start = (rand ( ) % (num_recs - years));

    return start;
}

