// Problem: Implement linear search to find key k in an array. Count and display the number of comparisons performed.

// Input:
// - First line: integer n (array size)
// - Second line: n space-separated integers
// - Third line: integer k (key to search)

// Output:
// - Line 1: "Found at index i" OR "Not Found"
// Line 2: "Comparisons = c"

// Example:
// Input:
// 5
// 10 20 30 40 50
// 30

// Output:
// Found at index 2
// Comparisons = 3

// Explanation: Compared with 10, 20, 30 (found at index 2 with 3 comparisons)
#include<stdio.h>

int main(){
    int i , n , s , k = 0  , ind , comp;
    printf("ENTER THE NUMBER OF TERMS YOU WANT :");
    scanf("%d" , &n);
    int arr[n];
    for(i=0;i<n;i++){
    printf("ENTER THE ELEMENT :");
        scanf("%d" , &arr[i]);
}
printf("ENTER THE ELEMENT TO  SEARCH : ");
scanf("%d" , &s);
for(i=0;i<n;i++){
    if(arr[i] == s){
  k=1;
  ind = i;
  comp = i+1;
   break;}
    else{
        k=0;
    }
}
if(k == 1){
    printf("%d found at %d with %d comparisons" , s , ind , comp);
}
else{
    printf("element not found");
}
    return 0;
}