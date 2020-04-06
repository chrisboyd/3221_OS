#include <math.h>
#include <stdio.h>
long long convert(int n);
int main() {
    int n = 6;
	char a[]  = { 'A', 'B', 'C', 'D', 'E', 'F' };
	for (int i = 0; i < 10; i++){
		printf("%c, ", a[(i+2)%6]);
	}
    /*
	printf("Enter a decimal number: ");
    scanf("%d", &n);
    printf("%d in decimal = %lld in binary", n, convert(n));
	*/
    return 0;
}

long long convert(int n) {
    long long bin = 0;
    int rem, i = 1, step = 1;
    while (n != 0) {
        rem = n % 2;
        printf("Step %d: %d/2, Remainder = %d, Quotient = %d\n", step++, n, rem, n / 2);
        n /= 2;
        bin += rem * i;
        i *= 10;
    }
    return bin;
}