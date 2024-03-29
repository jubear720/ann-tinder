/*************************************************************************//**
 * @file Perceptron.h
 *
 * @author Julian Brackins, Samuel Carroll, Alex Nienhueser
 *
 * @brief HEADER - Implementation of a basic perceptron
 *
 *****************************************************************************/

#ifndef _PERCEPTRON_H_
#define _PERCEPTRON_H_

/******************************************************************************
 *
 * INCLUDE
 *
 ******************************************************************************/

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <math.h>

/*************************************************************************//**
* @class Perceptron
*
* @author Samuel Carroll
*
* @brief Perceptron class.
*
*****************************************************************************/
class Perceptron
{
public:
    Perceptron();
    ~Perceptron();
    void add_input ( double* new_input );
    void set_error_grad ( double new_error_grad );
    double get_error_grad ( );
    void set_desired_output ( double new_desired );
    double get_desired_output ( );
    void set_output ( double &new_output );
    double* get_output ( );
    int get_whole_out ( );
    void set_weight (double weight, int index);
    double get_weight (int index);
    void set_theta ( double new_theta );
    double get_theta ( );
    void update_output ( );
    void clear_vectors ( );
    void view_input ( int index );
private:
    std::vector <double*> input;
    std::vector <double> weights;
    double error_grad;
    double desired_output;
    double output;
    double theta;
};

#endif
