#include <iostream>
#include <string>
#include <vector>
#include "main.h"
#include <omp.h>
using namespace std;
int static_evals = 0;


// @param bool state :: MAXIMIZING=1, MINIMIZING=0

double minimax_alpha_beta(Node& root, Node& best, int depth, bool state, double alpha, double beta){

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

         vector<Node>::iterator it;
         #pragma omp parallel   #pragma omp parallel  for default(shared) reduction(+:beta) 
        for(  it=root->next.begin(); it!=root->next.end(); it++){
    //         int nthreads, tid;
    // {
    //     tid = omp_get_thread_num();
    // cout<< "inside minmax current thread"<< tid<<endl;
    //     if (tid == 0){
    //         nthreads = omp_get_num_threads();
    //      cout<<"number of threads" << nthreads<<endl;
    //     }
    // }

            //mutiple threads will execute this line below, so 

            double val = minimax_alpha_beta(*it, best, depth+1, 0, alpha, beta);
            // cout<<"depth  :"<<depth<<endl;
             #pragma omp critical
            if(val > alpha){
                if(0 == depth){
                      
                    cout<<"current thread at minmax best assign is : "<< omp_get_thread_num()<<endl;
                    cout <<"score:  "<<val<<endl;
                                  
                     

                    best = *it;}
       #pragma omp atomic read
                alpha = val;
                
            }
            if(alpha >= beta)
                {continue;}
        }
        return alpha;
    }

    // MINIMIZING
    else{

        vector<Node>::iterator it;
            #pragma omp parallel  for default(shared) reduction(+:beta) 
        for(it=root->next.begin(); it!=root->next.end(); it++){

            double val = minimax_alpha_beta(*it, best, depth+1, 1, alpha, beta);
        
            if(val < beta){
            
                if(0 == depth){
                       cout<<"current thread at minmax best assign is : "<< omp_get_thread_num()<<endl;
                       cout <<"score:  "<<val<<endl;
                    #pragma omp atomic read
                    best = *it;}
                    #pragma omp atomic read
                beta = val;
                 
            }
            if(alpha >= beta)
                {continue;}
        }
        return beta;
    }
}
