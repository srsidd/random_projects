#include <iostream>
#include <stdio.h>
#include <vector>
#include <limits>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <new>
#include <fstream>


using namespace std;

int main()
{
    const auto M = 6;
    const auto N = 4;

    auto array = new double[M][N];

    ifstream file("data.txt");

    for (unsigned int i = 0; i < M; i++)
    {
        //array_2d[i] = new int[5];

        for (unsigned int j = 0; j < N; j++) 
            file >> array[i][j];
    
    }    

    for (unsigned int i = 0; i < M; i++)
    {
        //array_2d[i] = new int[5];

        for (unsigned int j = 0; j < N; j++) 
            cout<<array[i][j]<<" ";
    
    cout<<"\n";
    }   
    file.close();
    getchar();
}
