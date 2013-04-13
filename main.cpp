//
//  main.cpp
//  Asearch
//
//  Created by Cong on 13-4-13.
//  Copyright (c) 2013年 liuchyin. All rights reserved.
//

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

struct item{
    item(int d, int w, int** matrix, int x, int y, item* parent) :
        d(d), w(w), matrix(matrix), x(x), y(y), parent(parent){}
    int d;
    int w;
    int** matrix;
    int x;
    int y;
    item* parent;
    ~item(){
        for(int i = 0; i != 3; ++i)
            delete matrix[i];
    }
};

class A{
private:
    item *root;
    vector<item*> open;
    vector<item*> close;
    //最小堆用大于号
    class cmp{
    public:
        bool operator()(item* item1, item* item2){
            return item1->d + item1->w > item2->d + item2->w;
        }
    };
    
public:
    A(int matrix[][3]){
        int** newMatrix = new int*[3];
        for(int i = 0; i != 3; ++i)
            newMatrix[i] = new int[3];
        for(int i = 0; i != 3; ++i){
            for(int j = 0; j != 3; ++j)
                newMatrix[i][j] = matrix[i][j];
        }
        root = new item(1, 0, newMatrix, 2, 1, NULL);
    }
    
    
    item* start(){
        expand(root);
        while(!open.empty()){
            make_heap(open.begin(), open.end(), cmp());
            item* status = open.front();
            if(getW(status->matrix) == 0){
                return status;
            }
            expand(status);
            
            swap(open.front(), open.back());
            open.pop_back();
            close.push_back(status);
        }
        return  NULL;
    }
    
    void expand(item* status){

        int x = status->x;
        int y = status->y;
        int last = status->matrix[x][y];
        int d = status->d;
        int** matrix = status->matrix;
        
        if(x + 1 < 3 && matrix[x + 1][y] != last){
            int** newMatrix = copy(status->matrix);
            swap(newMatrix[x][y], newMatrix[x + 1][y]);
            open.push_back(new item(d + 1, getW(newMatrix), newMatrix, x + 1, y, status));
        }
        
        if(x - 1 >= 0 && matrix[x - 1][y] != last){
            int** newMatrix = copy(status->matrix);
            swap(newMatrix[x][y], newMatrix[x - 1][y]);
            open.push_back(new item(d + 1, getW(newMatrix), newMatrix, x - 1, y, status));
        }
        
        if(y + 1 < 3 && matrix[x][y + 1] != last){
            int** newMatrix = copy(status->matrix);
            swap(newMatrix[x][y], newMatrix[x][y + 1]);
            open.push_back(new item(d + 1, getW(newMatrix), newMatrix, x, y + 1, status));
        }
        
        if(y - 1 >= 0 && matrix[x][y - 1] != last){
            int** newMatrix = copy(status->matrix);
            swap(newMatrix[x][y], newMatrix[x][y - 1]);
            open.push_back(new item(d + 1, getW(newMatrix), newMatrix, x, y - 1, status));
        }
        
    }
    
    int getW(int** newMatrix){
        int goal[][3] = {
            {1, 2, 3},
            {8, 0, 4},
            {7, 6, 5}};
        int count = 0;
        for(int i = 0; i != 3; ++i){
            for(int j = 0; j != 3; ++j){
                if(newMatrix[i][j] != goal[i][j])
                    count++;
            }
        }
        return count;
    }
    
    int** copy(int** matrix){
        int** newMatrix = new int*[3];
        for(int i = 0; i != 3; ++i)
            newMatrix[i] = new int[3];
        for(int i = 0; i != 3; ++i){
            for(int j = 0; j != 3; ++j)
                newMatrix[i][j] = matrix[i][j];
        }
        return newMatrix;
    }
    
    ~A(){
        for (int i = 0; i != open.size(); ++i) {
            delete open[i];
        }
        for(int j = 0; j != close.size(); ++j){
            delete close[j];
        }
    }
};


void print(item * status){
    item *ptr = status;
    while(ptr){
        for(int i = 0; i != 3; ++i){
            for(int j = 0; j != 3; ++j){
                cout<<ptr->matrix[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        ptr = ptr->parent;
    }
}


int main(int argc, const char * argv[])
{
    int matrix[][3] = {
        {2, 8, 3},
        {1, 6, 4},
        {7, 0, 5}};
    
    A a(matrix);
    print(a.start());
    return 0;
}

