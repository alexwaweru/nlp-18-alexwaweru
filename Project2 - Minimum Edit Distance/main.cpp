#include <bits/stdc++.h> 

int min(int a, int b, int c);
int min_edit_distance(std::string str1, std::string str2, int m, int n);

int main(int argc, char **argv) 
{ 
    std::string s1 = argv[1]; 
    std::string s2 = argv[2]; 
  
    std::cout << min_edit_distance( s1 , s2 , s1.length(), s2.length()); 
  
    return 0; 
} 

int min_of_three(int a, int b, int c) 
{ 
   return std::min(std::min(a, b), c); 
} 
  
int min_edit_distance(std::string s1 , std::string s2 , int x ,int y) 
{ 
    if(x == 0){
        return y;
    } 
    if(y == 0){
        return x;  
    }
    if (s1[x-1] == s2[y-1]){
        return min_edit_distance(s1, s2, x-1, y-1);
    } 
    return 1 + min ( min_edit_distance(s1,  s2, x, y-1),   
                     min_edit_distance(s1,  s2, x-1, y),   
                     min_edit_distance(s1,  s2, x-1, y-1)  
                   ); 
} 