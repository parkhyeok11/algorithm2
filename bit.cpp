#include<iostream>
#include <bitset>
int main() {
	int a=0;
	int temp[17] = {0,};
	int temp2[17] = { 0, };

	std::cin >> a;

	for (int i = 1; i < a + 1; i++) {
		std::cin >> temp[i];
	}

	for (int i = 1; i < a + 1; i++) {
		std::cin >> temp2[i];
		temp[i] = temp[i] | temp2[i];
	}

	for (int i = 1; i < a + 1; i++) {

		std::bitset<5> binaryNumber(temp[i]);
		for (int j = 4; j >-1; j--) {
			if (binaryNumber[j] == 0) std::cout << " ";
			else std::cout << "#";
		}
		std::cout << "\n";
	}

	return 0;
}