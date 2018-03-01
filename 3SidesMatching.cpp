// 3SidesMatching.cpp

#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

// Number of Men or Women
// Need to change the N
// regarding the size of the matching

#define N 3

// This function returns true if woman 'w' prefers man 'm1' over man 'm'
bool womanPrefersM1overM(int prefer[2*N][N], int w, int m, int m1)
{
    // Check if w prefers m over her current engagment m1
    for (int i = 0; i < N; i++)
    {
        // If m1 comes before m in the list of w, then w prefers her
        // current engagement. Nothing change.
        if (prefer[w+N-1][i] - 1 == m1) {
            return true;
        }
        // If m comes before m1 in the w's list, then free her current
        // engagement and engage her with m
        if (prefer[w+N-1][i] - 1 == m) {
            return false;
        }
    }
    return false;
}

struct partner {
    int p[N];
};

typedef struct partner p;
p p_list;

// Prints stable matching for N men and N women.
// Men are numbered as 0 to N-1.
// Women are numbereed as N to 2N-1.

//partner
void stableMarriage(int prefer[2*N][N], string first, string second)
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
        
        // One by one go to all women according to m's preferences.
        // Here m is the picked free man
        for (int i = 0; i < N && mFree[m] == false ; i++) //
        {
            int w = prefer[m][i]; //Preference of the man line m, column i
            
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
    cout << second + "  " + first << endl;
    for (int i = 0; i < N; i++) {
        cout << " " << i+1 << "\t\t" << wPartner[i] + 1 << endl;
        p_list.p[i] = wPartner[i] + 1;
    }
}

int FindIndex(int a[N], int size, int value )
{
    int index = 0;
    
    while (index < size && a[index] != value) ++index;
    return (index == size ? -1 : index);
}

void finalMatching(int prefer[2*N][N], int preferWomenKids[2*N][N], int preferMenKids[2*N][N]) {
    
    // Men ordered for women preferences
    stableMarriage(prefer, "man", "woman");
    int mPartner[N];
    for (int i = 0; i < N; i++) {
        mPartner[i] = p_list.p[i];
    }
    
    // Women ordered
    int wPartner[N] = {1,2,3};
    
    // Kids ordered for men preferences
    stableMarriage(preferMenKids, "man", "kids");
    int k_mPartner[N];
    for (int i = 0; i < N; i++) {
        k_mPartner[i] = p_list.p[i];
    }
    // Kids ordered
    int kPartner[N] = {1,2,3};
    
    // Kids ordered for women preferences
    stableMarriage(preferWomenKids, "woman", "kids");
    int k_wPartner[N];
    for (int i = 0; i < N; i++) {
        k_wPartner[i] = p_list.p[i];
    }
    cout << "woman  man  kids" << endl;
    for (int i = 0; i < N; i++) {
        // Find value kids for a given Woman
        int kids = kPartner[FindIndex(k_mPartner, N, i+1)];
        cout << "  " << wPartner[i] << "     " << mPartner[i] << "     " << kids << endl;
        
    }
        
    for (int i = 0; i < N; i++) {
        // Find value woman for a given kids
        int kids_woman = k_wPartner[i];
    
        // Find value woman prefered by the man for a given kids
        int man_woman = wPartner[FindIndex(mPartner, N, k_mPartner[i])];
        
        if (man_woman == kids_woman) {
            cout << "STABLE" << endl;
        } else {
            cout << "UNSTABLE" << endl;
        }
    }    
}

// Main function
int main()
{
    // Two sided matching Man / Woman
    int prefer[2*N][N] = {
        {2, 3, 1}, //Man 0
        {3, 1, 2}, //Man 1
        {2, 3, 1}, //Man 2
        {2, 1, 3}, //Woman 0
        {3, 1, 2}, //Woman 1
        {1, 3, 2}, //Woman 2
    };
    
    // Two sided matching Woman / Kids
    int preferWomenKids[2*N][N] = {
        {2, 3, 1}, //Woman 0
        {1, 3, 2}, //Woman 1
        {1, 2, 3}, //Woman 2
        {1, 2, 3}, //Kids 0
        {2, 3, 1}, //Kids 1
        {3, 2, 1}, //Kids 2
    };
    
    // Two sided matching Man / Kids
    int preferMenKids[2*N][N] = {
        {2, 3, 1}, //Man 0
        {1, 3, 2}, //Man 1
        {1, 2, 3}, //Man 2
        {3, 1, 2}, //Kids 0
        {2, 1, 3}, //Kids 1
        {3, 2, 1}, //Kids 2
    };
    
    finalMatching(prefer, preferWomenKids, preferMenKids);
    
    cout << " " << endl;
}
