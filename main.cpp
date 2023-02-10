#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <omp.h>
#include "main.h"

using namespace std;
vector<string> prev_moves;

void print_materials(map<char, int>& m){
    map<char, int>::iterator it;
    for(it = m.begin(); it != m.end(); it++)
        cout << it->first << "  " << it->second << endl;
}

// ========== Initializes the materials for the game ==========
void init_materials(map<char, int>& m){
    // Black's Pieces
    m.insert(pair<char, int>('p', 8));
    m.insert(pair<char, int>('r', 2));
    m.insert(pair<char, int>('n', 2));
    m.insert(pair<char, int>('b', 2));
    m.insert(pair<char, int>('q', 1));
    m.insert(pair<char, int>('k', 1));

    // White's Pieces
    m.insert(pair<char, int>('P', 8));
    m.insert(pair<char, int>('R', 2));
    m.insert(pair<char, int>('N', 2));
    m.insert(pair<char, int>('B', 2));
    m.insert(pair<char, int>('Q', 1));
    m.insert(pair<char, int>('K', 1));
}


int main(){
    // INITIALIZES NODE VARIABLES
int nthreads, tid;
    {
        tid = omp_get_thread_num();
    cout<< "welcome to GFG from thread "<< tid;
        if (tid == 0){
            nthreads = omp_get_num_threads();
         cout<<"number of threads" << nthreads<<endl;
        }
    }








    Node root = new tNode;
    init_materials(root->materials);
    root->cur_side = 0; // 0 denotes human/player side

    print_board(root);

    string user_input;
    Node best;
    while(true){

        // HUMAN SIDE FUNCTIONALITY
        cin >> user_input;
        if(user_input == "q" || user_input == "quit"){
            break;
        }
        exec_player_move(root, user_input);
  
        print_board(root);

        if(root->materials['k'] == 0){
            cout << "*******************************************************" << endl;
            cout << "******************* HUMAN SIDE WINS *******************" << endl;
            cout << "*******************************************************" << endl;
            break;
        }

        // COMPUTER SIDE FUNCTIONALITY
        next_move(root, 0);
 
double start; 
double end; 
start = omp_get_wtime(); 
 
        minimax_alpha_beta(root, best, 0, 0, LOWEST_SCORE, HIGHEST_SCORE);
        end = omp_get_wtime(); 
        cout<<"Execution Time of Parallel Minimax Alphabeta is "<<end-start<<endl;
   
        cout<<"BOARD"<<endl;
    
        print_board(best);
        vector<string> prevs= root->prev_moves_white;
    for(auto &m: prevs){
        cout<<m<<endl;
    }

      
        static_evals = 0;

        int a, b;
        for(a=0; a<12; a++){
            for(b=0; b<12; b++){
                root->board[a][b] = best->board[a][b];
            }
        }
        root->materials = best->materials;
        root->w_king_pos = best->w_king_pos;
        root->b_king_pos = best->b_king_pos;

        tree_delete(root);
        prev_moves.clear();

        if(root->materials['K'] == 0){
            cout << "*******************************************************" << endl;
            cout << "****************** COMPUTER SIDE WINS *****************" << endl;
            cout << "*******************************************************" << endl;
            break;
        }
    }
    return 0;
}
