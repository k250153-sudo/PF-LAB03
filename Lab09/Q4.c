#include <stdio.h>
void byval(int x) {
    x = x+5;
}
void byref(int *x) {
    *x=*x+5;
}
int main() {
    int x=80;
    printf("Before updateValue:%d\n",x);
    byval(x);
    printf("After updateValue:%d (no change)\n",x);
    printf("Before updateReference:%d\n",x);
    byref(&x);
    printf("After updateReference:%d (Updated successfully)",x);

}