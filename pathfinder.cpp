/*
    pathfinder.cpp
        
    Method implementations for the pathfinder class.
    
    assignment: CSCI 262 Project - Pathfinder        

    author: <David Beck>
*/

#include <iostream>
#include <fstream>
#include "pathfinder.h"
#include <cstdlib>


using namespace std;

// constructor - optional, in case you need to initialize anything
pathfinder::pathfinder() {

}


// public run() method - invokes private methods to do everything;
// returns the total elevation change cost of the best optimal path.
int pathfinder::run(string data_file_name, string save_file_name, bool use_recursion) {
    // suggested implementation - modify as desired!
    _use_recursion = use_recursion;
    if (!_read_data(data_file_name)) {
        cout << "Error reading map data from \"" << data_file_name << "\"!" << endl;
        return -1;
    }

    _draw_map();

    int best_cost = _draw_paths();

    _save_image(save_file_name);

    return best_cost;
}

/*******************/
/* PRIVATE METHODS */
/*******************/

// _read_data - read and store width, height, and elevation data from the
// provided data file; return false if something goes wrong
bool pathfinder::_read_data(string data_file_name) {







    // TODO: open input file
    ifstream myfile;
    myfile.open(data_file_name);
    // TODO: read in and store width and height
    string _strwidth, _strheight;
    myfile >> _strwidth;
    myfile >> _width;
    myfile >> _strheight;
    myfile >> _height;
    //_elevations = vector<vector<int>>(_width, vector<int>(_height));
    // TODO: read in and store elevation drata


    for(int i = 0; i < _height; i++){
        vector<int> row;
        for(int j = 0; j < _width; j++){
            int ePoint;
            myfile >> ePoint;
            row.push_back(ePoint);

            }
        _elevations.push_back(row);
        }




    // TODO: close input file
    myfile.close();
    // TODO: return true if everything worked
    return true;
}

// _draw_map - draw the elevation data as grayscale values on our Picture
// object.

void pathfinder::_draw_map() {
    // TODO: determine min/max elevation values in map
    for(int i = 0; i < _height; i++){
        for(int j = 0; j < _width;j++){
            if(_max < _elevations[i][j]){
                _max = _elevations[i][j];
            }

        }
    }
    _min = _max;
    for(int i = 0; i < _height; i++){
        for(int j = 0; j < _width;j++){
            if(_min > _elevations[i][j]){
                _min = _elevations[i][j];
            }

        }
    }

    // TODO: from min, max, determine a scaling factor for data to shift
    //       elevations into 0 - 255 range
    scale = (255.0) / (_max - _min);
    offset = (_min)*(scale);







    // TODO: for each elevation point, determine its grayscale value

    for(int i = 0; i < _height; i++){
        vector<int> rowV;
        for(int j = 0; j < _width; j++){
            int q = (_elevations[i][j]*scale)-offset;
            rowV.push_back(q);


        }
        gS.push_back(rowV);


    }

    // TODO: for each elevation point, set the corresponding Picture point
    _image.set(_height - 1, _width - 1, 0, 0, 0);
    for(int i = 0; i < _height; i ++){
        for(int j = 0; j < _width; j++){
           _image.set(i,j,gS[i][j], gS[i][j], gS[i][j]);

        }


    }



// _draw_paths() - find and draw optimal paths from west to east using either recursion or dynamic programming
// return the best optimal path cost

}

int pathfinder::opCostToEast(int row,int col) {


    if(col >= _width - 1){
        return 0;
    }
    int CostNorthEast = INT_MAX;
    int CostSouthEast = INT_MAX;
    int CostEast;



    CostEast = abs(_elevations[row][col] - _elevations[row][col+1])+ opCostToEast(row,col+1);
    if(row > 0){
        CostNorthEast = abs(_elevations[row][col] - _elevations[row-1][col+1]) + opCostToEast(row - 1, col + 1);
    }
    else if(row < _height - 1){
        CostSouthEast = abs(_elevations[row][col] - _elevations[row+1][col+1]) + opCostToEast(row + 1, col +1);
    }
    if(CostEast <= CostNorthEast && CostEast <= CostSouthEast){
        return CostEast;
    }
    else if(CostSouthEast < CostNorthEast && CostSouthEast < CostEast){
        return CostSouthEast;
    }
    else if (CostNorthEast < CostEast && CostNorthEast < CostSouthEast){
        return CostNorthEast;
    }


}

int pathfinder::_draw_paths() {
    // TODO: based on the _use_recursion field, compute minimum cost for every point on map using either
    //  recursion or dynamic programming. Keep track of next move necessary to attain min cost.
    //  This will require additional data structures!

    int min = opCostToEast(0,0);



    for(int i = 1; i < _height; i++){
        int totalCost = opCostToEast(i,0);
        if(totalCost < min){
            min = totalCost;
        }

    }
    return min;




    // TODO: For part 1, once the recursive solve is done, just return the minimum cost. You don't have to
    //  plot the paths, nor create the dynamic programming solution for part 1.


    // TODO: plot optimal paths from every westmost point, in blue

    // TODO: find and plot best optimal path in yellow

    // TODO: return total cost of best cost

    // TODO: consider breaking this method up using additional helper methods

}

// _save_image - we'll do this one for you :)
void pathfinder::_save_image(string save_file_name) {
    _image.save(save_file_name);
}

