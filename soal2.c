/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman 2025/2026
*   Modul               : Foundation of Algorithm
*   Hari dan Tanggal    : Rabu, 13 Mei 2026
*   Nama (NIM)          : Benedictus Kenneth Setiadi (13224003)
*   Nama File           : soal2.c
*   Deskripsi           :
*/

#include <stdio.h> 
#include <string.h> 
#include <stdbool.h> 

#define ROW 5
#define COL 5

int isSafe(int M[][COL], int row, int col, bool visited[][COL], int rowt, int colt) 
{ 
    // row number is in range, column number is in range and value is 1 
    // and not yet visited 
    return (row >= 0) && (row < rowt) &&     
        (col >= 0) && (col < colt) &&     
        (M[row][col] && !visited[row][col]); 
} 


void DFS(int M[][COL], int row, int col, bool visited[][COL], int *area, int rowt, int colt) 
{ 
    // These arrays are used to get row and column numbers of 8 neighbours 
    // of a given cell 
    static int rowNbr[] = {-1, 0, 0, 1}; 
    static int colNbr[] = {0, 1, -1, 0}; 
    // int curr_largest = 0;

    // increment area by 1
    (*area)++;

    // Mark this cell as visited 
    visited[row][col] = true; 

    // Recur for all connected neighbours 
    for (int k = 0; k < 4; ++k) 
        if (isSafe(M, row + rowNbr[k], col + colNbr[k], visited, rowt, colt) ){
            // curr_largest += 1;
            DFS(M, row + rowNbr[k], col + colNbr[k], visited, area, rowt, colt); 
        }
    // largest = &curr_largest; 
} 

// int largest(int a, int b){
//     if(a>b){
//         return a;
//     } if(a<b){
//         return b;
//     } else {
//         return a;
//     }
// }

int countIslands(int M[][COL], int rowt, int colt) 
{ 
    // Make a bool array to mark visited cells. 
    // Initially all cells are unvisited 
    bool visited[rowt][colt]; 
    memset(visited, 0, sizeof(visited)); 

    // Initialize count as 0 and traverse through the all cells of 
    // given matrix 
    int count = 0; 
    // int *largest = 0;
    int area = 0;
    for (int i = 0; i < rowt; ++i) 
        for (int j = 0; j < colt; ++j) 
            if (M[i][j] && !visited[i][j]) // If a cell with value 1 is not 
            {                         // visited yet, then new island found 
                DFS(M, i, j, visited, &area, rowt, colt);     // Visit all cells in this island. 
                ++count;                 // and increment island count 
            } 

    return count; 
} 

// Function to find area of the largest region of 1s
int largestRegion(int M[][COL], int rowt, int colt) {
  	
    // Initialize result as 0 and traverse through 
  	// all cells of given matrix
    bool visited[rowt][colt]; 
    int maxArea = 0;
    for (int i = 0; i < rowt; i++) {
        for (int j = 0; j < colt; j++) {
            // If a cell with value 1 is found
            if (M[i][j] == 1) {
                int area = 0;
                DFS(M, i, j, visited, &area, rowt, colt);

                // Maximize the area
                if (area > maxArea) {
                    maxArea = area;
                }
            }
        }
    }
    return maxArea;
}


// int largestIsland(int M[][COL]) 
// { 
//     // Make a bool array to mark visited cells. 
//     // Initially all cells are unvisited 
//     bool visited[ROW][COL]; 
//     memset(visited, 0, sizeof(visited)); 

//     // Initialize count as 0 and traverse through the all cells of 
//     // given matrix 
//     int count = 0; 
//     int *largest = 0;
//     for (int i = 0; i < ROW; ++i) 
//         for (int j = 0; j < COL; ++j) 
//             if (M[i][j] && !visited[i][j]) // If a cell with value 1 is not 
//             {                         // visited yet, then new island found 
//                 DFS(M, i, j, visited, largest);     // Visit all cells in this island. 
//                 ++count;                 // and increment island count 
//             } 

//     int curr_largest = *largest;
//     return curr_largest; 
// } 

    

int main(){
    int R, C;
    scanf("%d %d", &R, &C);
    // printf("%d %d\n", R, C);
    // int M[R][C] = { {1,1,0,0,0}, 
    //     {1,1,0,1,0}, 
    //     {0,0,1,0,1}, 
    //     {0,0,0,1,1} };; 

    // for(int i = 0; i < C)

    // int rows = 3, cols = 3;
    int M[R][C]; // Declaration
    char str[C];

    // int x;
    for (int i = 0; i < R; i++) {
        scanf("%s", str);
        // printf("%c", str[0]);
        for (int j = 0; j < C; j++) {
            int curr = str[j] - '0';
            M[i][j] = curr;// Manual assignment
            // printf("%d", M[i][j]);
        }
    } 

    
    // for(int i = 0; i < R; i++){
    //     for (int j = 0; j < C; j++)
    //     {
            
    //     }
        
    // }
    

    // int grid[4][5] = { {1,1,0,0,0}, {1,1,0,1,0}, {0,0,1,0,1}, {0,0,0,1,1} };


    printf("ISLANDS %d\n", countIslands(M, R, C)); 
    printf("LARGEST %d", largestRegion(M,  R,  C));
    return 0;
}

// 11000 11010 00101 00011
