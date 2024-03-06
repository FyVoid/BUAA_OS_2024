#include <stdio.h>

int isPalindrome(int n) {
	if (n / 10 == 0) {
		return 1;
	}

	int buffer[16];
	int count = 0;
	
	while (n != 0) {
		int num = n % 10;
		n /= 10;
		buffer[count++] = num;
	}

	for (int i = 0; i < count / 2; i++) {
		if (buffer[count - i - 1] != buffer[i]) {
			return 0;
		}
	}

	return 1;
}

int main() {
	int n;
	scanf("%d", &n);

	if (isPalindrome(n)) {
		printf("Y\n");
	} else {
		printf("N\n");
	}
	return 0;
}
