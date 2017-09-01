/* This Program was made using a Raspberry Pi 3
 * written by: Unwarymold9171
 */

#include <stdio.h>

int main(void);
int GetInt(void);

int main(){
	int num1, num2, num3;
	int largest, smallest;

	printf("Enter the first number: ");
	num1 = GetInt();
	printf("Enter the second number: ");
	num2 = GetInt();
	printf("Enter the third number: ");
	num3 = GetInt();

	if(num1 > num2){
		if(num1 > num3){
			largest = num1;
			if(num2 > num3){
				smallest = num3;
			} else {
				smallest = num2;
			}
		} else {
			largest = num3;
			smallest = num2;
		}
	} else if(num2 > num3){
		largest = num2;
		if(num1 > num3){
			smallest = num3;
		} else {
			smallest = num1;
		}
	} else {
		largest = num3;
		if(num1 > num2){
			smallest = num2;
		} else {
			smallest = num1;
		}
	}

	printf("The largest number is: %d\n", largest);
	printf("The smallest number is: %d\n", smallest);
}

int GetInt(){
	int input;
	scanf("%d", &input);
	return input;
}
