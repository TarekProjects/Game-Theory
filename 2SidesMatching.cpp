// 2SidesMatching.cpp

#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

// Number of Men or Women
// Need to change the N
// regarding the size of the matching

#define N 8 //4

// This function returns true if woman 'w' prefers man 'm1' over man 'm'
bool womanPrefersM1overM(int prefer[2*N][N], int w, int m, int m1)
{
    // Check if w prefers m over her current engagment m1
    for (int i = 0; i < N; i++)
    {
        cout << "Woman: " << prefer[w+N-1][i] - 1 << " prefers m: " << m+1 << " or m1: "<< m1 + 1 << " ?" << endl;
        // If m1 comes before m in the list of w, then w prefers her
        // current engagement. Nothing change.
        if (prefer[w+N-1][i] - 1 == m1) {
            cout << "TRUE " << endl;
            return true;
        }
        // If m comes before m1 in the w's list, then free her current
        // engagement and engage her with m
        if (prefer[w+N-1][i] - 1 == m) {
            cout << "FALSE " << endl;
            return false;
        }
    }
    return false;
}

// Prints stable matching for N men and N women.
// Men are numbered as 0 to N-1.
// Women are numbereed as N to 2N-1.

void stableMarriage(int prefer[2*N][N])
{
    // Stores partner of women. This is our output array that
    // stores paing information.  The value of wPartner[i]
    // indicates the partner assigned to woman N+i.  Note that
    // the woman numbers between N and 2*N-1. The value -1
    // indicates that (N+i)'th woman is free
    int wPartner[N];
    
    // An array to store availability of men.  If mFree[i] is
    // false, then man 'i' is free, otherwise engaged.
    bool mFree[N];
    
    // Initialize all men and women as free
    memset(wPartner, -1, sizeof(wPartner));
    memset(mFree, false, sizeof(mFree));
    int freeCount = N;

    // While there are free men
    while (freeCount > 0)
    {
      
        // Pick the first free man (we could pick any)
        int m; // from 0 to N-1
        for (m = 0; m < N; m++)
            {
                if (mFree[m] == false) break;
            }
        cout << "m: " << m + 1 << endl; // Actual man number

        // One by one go to all women according to m's preferences.
        // Here m is the picked free man
        for (int i = 0; i < N && mFree[m] == false ; i++) //
        {
            int w = prefer[m][i]; //Preference of the man line m, column i

            cout << "w: " << w << endl;
            
            // The woman of preference is free, w and m become
            // partners (Note that the partnership maybe changed
            // later). So we can say they are engaged not married
            if (wPartner[w-1] == -1)
            {
                wPartner[w-1] = m;
                mFree[m] = true;
                freeCount--;
            }
            else  // If w is not free
            {
                // Find current engagement of w
                int m1 = wPartner[w-1];
                cout << "m1: " << m1 + 1 << endl; // Actual man number
                
                // If w prefers m over her current engagement m1,
                // then break the engagement between w and m1 and
                // engage m with w.
                if (womanPrefersM1overM(prefer, w, m, m1) == false)
                {
                    wPartner[w-1] = m;
                    mFree[m] = true;
                    mFree[m1] = false;
                }
            } // End of Else
        } // End of the for loop that goes to all women in the m's list
    } // End of main while loop
    
    
    // Print the solution
    cout << "Woman   Man" << endl;
    for (int i = 0; i < N; i++)
        cout << " " << i+1 << "\t\t" << wPartner[i] + 1 << endl;
}

// Main function
int main()
{
    int prefer[2*N][N] = {
                            {5,7,1,2,6,8,4,3}, //Man 0
                            {2,3,7,5,4,1,8,6}, //Man 1
                            {8,5,1,4,6,2,3,7}, //Man 2
                            {3,2,7,4,1,6,8,5}, //Man 3
                            {7,2,5,1,3,6,8,4}, //Man 4
                            {1,6,7,5,8,4,2,3}, //Man 5
                            {2,5,7,6,3,4,8,1}, //Man 6
                            {3,8,4,5,7,2,6,1}, //Man 7
                            {5,3,7,6,1,2,8,4}, //Woman 0
                            {8,6,3,5,7,2,1,4}, //Woman 1
                            {1,5,6,2,4,8,7,3}, //Woman 2
                            {8,7,3,2,4,1,5,6}, //Woman 3
                            {6,4,7,3,8,1,2,5}, //Woman 4
                            {2,8,5,3,4,6,7,1}, //Woman 5
                            {7,5,2,1,8,6,4,3}, //Woman 6
                            {7,4,1,5,2,3,6,8}, //Woman 7
                        };
    
    stableMarriage(prefer);
    
    return 0;
}
