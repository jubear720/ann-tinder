/*************************************************************************//**
* @file NeuralNet.h
*
* @author Julian Brackins, Samuel Carroll, Alex Nienhueser
*
* @brief HEADER - Implementation of a Neural Network
*
*****************************************************************************/

#ifndef _NEURALNET_H_
#define _NEURALNET_H_

/******************************************************************************
*
* INCLUDE
*
******************************************************************************/

#include <vector>
#include <iostream>
#include <string>
#include "Perceptron.h"
#include "Prm.h"
#include "Csv.h"

/*************************************************************************//**
* @class NeuralNet
*
* @author Samuel Carroll
*
* @brief NeuralNet (Neural Network) class.
*
*****************************************************************************/
class NeuralNet
{
   public:
      NeuralNet ( std::string param_file );
      ~NeuralNet ( );
      void add_layer ( int nodes );
      void set_first_layer ( records *input_records );
      void set_desired_output ( records *input_records );
      void connect_layers ( );
      void update_weights ( );
      void update_grads ( );
      void update_error_grad (Perceptron curr_node, bool inside_node,
                              double new_error_grad );
      void set_weights ( double weights [ ] );
      void get_weights ( double weights [ ], int size );
      double get_error ( );
      int get_layer_nodes ( int index );
      std::string get_weights_file ( );
      std::string getCsvFile ( );
      int getNetSize ( );

   private:
      std::vector <std::vector <Perceptron>> percep_net;
      Prm* ANN_params;
};

  #endif
