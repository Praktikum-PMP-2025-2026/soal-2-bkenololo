/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman 2025/2026
*   Modul               : Foundation of Algorithm
*   Hari dan Tanggal    : Rabu, 13 Mei 2026
*   Nama (NIM)          : Benedictus Kenneth Setiadi (13224003)
*   Nama File           : soal2.c
*   Deskripsi           : Menghitung jumlah pulau dan luas pulau terbesar secara dinamis
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h> 

// checks if the current cell is within bounds, is a land cell (1), and hasn't been visited
int isSafe(int **M, int row, int col, bool **visited, int rowt, int colt) 
{ 
    return (row >= 0) && (row < rowt) &&     
           (col >= 0) && (col < colt) &&     
           (M[row][col] && !visited[row][col]); 
} 

// Depth First Search to traverse the entire connected island
void DFS(int **M, int row, int col, bool **visited, int *area, int rowt, int colt) 
{ 
    // Arrays to explore 4-directional connected neighbors (up, right, left, down)
    static int rowNbr[] = {-1, 0, 0, 1}; 
    static int colNbr[] = {0, 1, -1, 0}; 

    (*area)++;
    visited[row][col] = true; 

    for (int k = 0; k < 4; ++k) {
        if (isSafe(M, row + rowNbr[k], col + colNbr[k], visited, rowt, colt)) {
            DFS(M, row + rowNbr[k], col + colNbr[k], visited, area, rowt, colt); 
        }
    }
} 

// Counts total isolated islands
int countIslands(int **M, int rowt, int colt) 
{ 
    // Dynamically allocate the 2D boolean tracking array
    bool **visited = (bool **)malloc(rowt * sizeof(bool *));
    for (int i = 0; i < rowt; i++) {
        visited[i] = (bool *)calloc(colt, sizeof(bool)); // calloc initializes elements to false
    }

    int count = 0; 
    for (int i = 0; i < rowt; ++i) {
        for (int j = 0; j < colt; ++j) {
            if (M[i][j] && !visited[i][j]) {
                int area = 0; // Temp dummy variable just to track traversal structure
                DFS(M, i, j, visited, &area, rowt, colt);     
                ++count;                 
            } 
        }
    }

    // Free the allocated memory for visited matrix
    for (int i = 0; i < rowt; i++) free(visited[i]);
    free(visited);

    return count; 
} 

// Finds area of the largest region of 1s
int largestRegion(int **M, int rowt, int colt) {
    bool **visited = (bool **)malloc(rowt * sizeof(bool *));
    for (int i = 0; i < rowt; i++) {
        visited[i] = (bool *)calloc(colt, sizeof(bool));
    }

    int maxArea = 0;
    for (int i = 0; i < rowt; i++) {
        for (int j = 0; j < colt; j++) {
            if (M[i][j] == 1 && !visited[i][j]) {
                int area = 0;
                DFS(M, i, j, visited, &area, rowt, colt);

                if (area > maxArea) {
                    maxArea = area;
                }
            }
        }
    }

    for (int i = 0; i < rowt; i++) free(visited[i]);
    free(visited);

    return maxArea;
}

int main(){
    int R, C;
    if (scanf("%d %d", &R, &C) != 2) return 1;

    // Dynamically allocate 2D array for Map Grid M[R][C]
    int **M = (int **)malloc(R * sizeof(int *));
    for (int i = 0; i < R; i++) {
        M[i] = (int *)malloc(C * sizeof(int));
    }

    // Allocate buffer string with safety room for trailing newline/null characters
    char *str = (char *)malloc((C + 2) * sizeof(char));

    for (int i = 0; i < R; i++) {
        scanf("%s", str);
        for (int j = 0; j < C; j++) {
            M[i][j] = str[j] - '0';
        }
    } 

    printf("ISLANDS %d\n", countIslands(M, R, C)); 
    printf("LARGEST %d\n", largestRegion(M, R, C));

    // Clean up allocated heap blocks
    free(str);
    for (int i = 0; i < R; i++) free(M[i]);
    free(M);

    return 0;
}
