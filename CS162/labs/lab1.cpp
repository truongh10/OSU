//#include "stdafx.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

struct mult_div_values {
   int mult;
   float div;
};
//Create dynamic 2D array
mult_div_values** arr(int m, int n){
   mult_div_values **table = new mult_div_values*[m];
   for (int i=0; i<m; i++){
      table[i] = new mult_div_values[n];
   }
   return table;
}

//Set multiplications values
void set_mult_values(mult_div_values **table, int m, int n) {
   for(int i=1; i<=m; i++) {
      for(int j=1; j<=n; j++) {
         table[i-1][j-1].mult=i*j;
      }
   }
}

//Set division values
void set_div_values(mult_div_values** table, int m, int n){
   for(int i=1; i<=m; i++) {
      for(int j=1; j<=n; j++) {
         table[i-1][j-1].div=(double)i/(double)j;
      }
   }
}

//Print mult table
void print_mult_table(mult_div_values** table, int m, int n){
   cout << "Multiplication Table" << endl;
   for(int i=0; i<m; i++){
      for(int j=0; j<n; j++) {
         cout << table[i][j].mult << " ";
      }
      cout << endl;
   }
}

//Print div table
void print_div_table(mult_div_values** table, int m, int n){
   cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
   cout << "Division table" << endl;
   for(int i=0; i<m; i++){
      for(int j=0; j<n; j++) {
         cout << table[i][j].div << " ";
      }
      cout << endl;
   }
}

//Free memory
void delete_table(mult_div_values** table, int m, int n){
   for(int i=0; i<m; i++){
      delete [] table [i];
   }
}
int main(int argc, char* argv[]) {
   
   int rows = atoi(argv[1]);
   int cols = atoi(argv[2]);

   mult_div_values** table;
   table = arr(rows,cols);
   set_mult_values(table,rows,cols);
   set_div_values(table,rows,cols);
   print_mult_table(table,rows,cols);
   print_div_table(table,rows,cols);
   delete_table(table,rows,cols);

   return 0;
}
