#include <iostream>
#include <climits>
#include <vector>
using namespace std;



//max sizes of Young table 
#define M 4
#define N 4


class QueueY {
    int tableau[N][M];

public:
    QueueY() {
        fill(*tableau, *tableau + M * N, INT_MAX);
    }


    void insert(const vector<int>& keys) {
        fill(*tableau, *tableau + M * N, INT_MAX);
        for (int key : keys)
        {
            // check for overflow
            if (full()) {
                cout << "Young tableau is full. Skipping key " << key << endl;
            }
            else {
                tableau[M - 1][N - 1] = key;
                // move the key to its correct position in the tableau
                insert(M - 1, N - 1);
            }
        }
    }



    void insert(int i, int j)
    {
        // base case
        if (i == 0 && j == 0) {
            return;
        }

        // handle separately for the first row
        if (i == 0)
        {
            if (tableau[i][j] < tableau[i][j - 1])
            {
                swap(tableau[i][j], tableau[i][j - 1]);
                insert(i, j - 1);
            }
            return;
        }

        // handle separately for the first column
        if (j == 0)
        {
            if (tableau[i][j] < tableau[i - 1][j])
            {
                swap(tableau[i][j], tableau[i - 1][j]);
                insert(i - 1, j);
            }
            return;
        }

        if (tableau[i][j] < tableau[i - 1][j])        // go up
        {
            swap(tableau[i][j], tableau[i - 1][j]);
            insert(i - 1, j);
        }

        if (tableau[i][j] < tableau[i][j - 1])        // go left
        {
            swap(tableau[i][j], tableau[i][j - 1]);
            insert(i, j - 1);
        }
    }


    //precodnition isNot full
    void push(int number) {

        if (full())
        {
            throw std::runtime_error("Exception trying push element of empty queue");
        }

        tableau[M - 1][N - 1] = number;
        // move the key to its correct position in the tableau
        insert(M - 1, N - 1);
    }

 
    void fixTableau(int i, int j)
    {
       
        int bottom = (i + 1 < M) ? tableau[i + 1][j] : INT_MAX;
        int right = (j + 1 < N) ? tableau[i][j + 1] : INT_MAX;

        if (bottom == INT_MAX && right == INT_MAX) {
            return;
        }

        if (bottom < right)      
        {
            swap(tableau[i][j], tableau[i + 1][j]);
            fixTableau( i + 1, j);
        }
        else      
        {
            swap(tableau[i][j], tableau[i][j + 1]);
            fixTableau( i, j + 1);
        }
    }

    //precodnition isNot empty
    void pop()
    {
        if (empty())
        {
            throw std::runtime_error("Exception trying pop element of empty queue");
        }
        // make the first element as infinity
        tableau[0][0] = INT_MAX;

        // fix the Young tableau property
        fixTableau(0, 0);


    }


    int& top() {
       
        return **tableau;
    }
 

    void printTableau() const
    {

        cout << "<---- Young Table ---->" << endl<<endl;

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++) {
                if (tableau[i][j] == INT_MAX)
                {
                    cout <<  " ~ ";
                }
                else {
                    cout << tableau[i][j] << ' ';
                }
               
            }
            cout << endl << endl;
        }
        cout << "<--------     --------->" << endl<<endl;

    }



    bool empty() const{
        return tableau[0][0] == INT_MAX;
    }

    bool full() const{
        return  tableau[M - 1][N - 1] != INT_MAX;
    }

};










int main()
{

    QueueY t;
    
    if (t.empty()) {
        cout << "Queue is empty`" << endl;
    }

    vector<int> keys = { 12, 10, 20, 22, 25, 34, 11,
                       44, 27, 16, 35, 15 };
    t.insert(keys);





    t.printTableau();

    t.push(99);
    t.printTableau();

    t.push(78);
    t.push(19);
    t.push(26);

    if (t.full()) {
        cout << "Queue is full`" << endl;
    }

    t.printTableau();

    t.top() = 0;
    cout << "top element is` " << t.top() << endl<< endl;
   
    t.pop();

    t.printTableau();

    cout <<"top element is` "<< t.top() << endl<<endl;
    t.pop();

    t.printTableau();


    system("pause");
    return 0;
}