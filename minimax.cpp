#include <iostream>
#include <string>
#include <vector>
#include "main.h"
#include <omp.h>
using namespace std;



// @param bool state :: MAXIMIZING=1, MINIMIZING=0
double minimax(Node& root, Node& best, int depth, bool state){

    // cout << "==========" << " DEPTH LEVEL " << depth << " ==========" << endl;
    bool f= true;
      double s =0;

    if(depth >= MAX_DEPTH || 0 == root->next.size()){
        
        static_evals++;
     s = static_eval(root);
              
        return s;
        
    }

    // MAXIMIZING
    else if(state){
 double val= LOWEST_SCORE;
 double dbl= val;
         vector<Node>::iterator it;
          #pragma omp parallel  for
        for(  it=root->next.begin(); it!=root->next.end(); it++){
   
             val = max (val, minimax(*it, best, depth+1, 0));
                  #pragma omp critical
            if(val>dbl  && depth==0){
                 cout<<"current thread at minmax best assign is : "<< omp_get_thread_num()<<endl;
                    cout <<"score:  "<<val<<endl;
                    
                dbl=val;
         best = *it;}
        }
       
         return val;

    }

    // MINIMIZING
    else{
 double val= HIGHEST_SCORE;
 double dbl= val;
        vector<Node>::iterator it; 
            #pragma omp parallel  for
        for(it=root->next.begin(); it!=root->next.end(); it++){
             val = min(val, minimax(*it, best, depth+1, 1));
                  #pragma omp critical
                if(val<dbl && depth==0){
                      cout<<"current thread at minmax best assign is : "<< omp_get_thread_num()<<endl;
                    cout <<"score:  "<<val<<endl;
                    
                dbl=val;
         best = *it;}
        }
                     return val;
  
        }

    
}
