#include <stdio.h>
int main() {
    int n, pos, ins , i;
    printf("ENTER THE NUMBER OF TERMS OF ARRAY : ");
    scanf("%d", &n);
    int arr[n+1];
    for(i=0;i<n;i++){
        printf("ENTER THE ELEMENTS : ");
        scanf("%d", &arr[i]);
    }
      printf("ENTER THE POSITION FOR INSERTION: ");
    scanf("%d", &pos);
      printf("ENTER THE ELEMENT TO BE INSERTED : ");
    scanf("%d", &ins);
    for(i=n;i>=pos;i--){
        arr[i] = arr[i-1];
    }
    arr[pos-1] = ins;
      printf("ARRAY AFTER INSERTION : ");
    for(i=0;i<=n;i++){
        printf("%d ", arr[i]);
    }
    return 0;
}
